// Wbudowane 2024, Wojciech Kieloch, zad.3 l13

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <math.h>

#define BAUD 9600                              // Baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // Obliczenie wartości UBRR

uint16_t adcRes = 0;

void adcInit()
{
  ADMUX |= _BV(REFS0) | _BV(REFS1);              // adc0 input, ref 1.1V
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  //ADCSRA |= _BV(ADIE);
  ADCSRA |= _BV(ADEN);
}

uint16_t getADC()
{
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF)))
    ;                  // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)

  return ADC;
}


// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)))
    ;
  return UDR0;
}

float adcToVoltage(uint16_t adc)
{
  return ((float)adc * 1.1) / 1024;
}

float voltToTemp(float volt)
{
  // T = T_0 * B / ( B + T_0 * LOG(R/R_0) )
  const float termAmperage = 0.13; // mili amperów
  const float initTermistorResi = 4700;
  const float initTermTemp = 25;
  const float bValue = 2727; // assumed
  const float curResistance = volt / termAmperage;
  const float resRatio = log(curResistance / initTermistorResi);
  const float numerator = initTermTemp * bValue;
  const float denominator = bValue + initTermTemp * resRatio;
  return numerator / denominator;
}

FILE uart_file;

int main()
{
  uart_init();
  adcInit();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_WRITE);
  stdin = stdout = stderr = &uart_file;

  while (1)
  {
    adcRes = getADC();
    const float curVoltage = adcToVoltage(adcRes);
    const float curTemp = voltToTemp(curVoltage);
    printf("ADC: %d Volt: %f Temp: %f\n", adcRes, curVoltage, curTemp);
  }
}
