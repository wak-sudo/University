// Wojciech Kieloch 2024, Wbudowane

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

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

FILE uart_file;

// inicjalizacja ADC
void adc_init()
{
  ADMUX = _BV(REFS0);                            // referencja AVcc, wejście ADC0
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN);                           // włącz ADC
}

void timers_init()
{
  TCCR0A = _BV(WGM01) | _BV(WGM00);    // fast pwm
  TCCR0A |= _BV(COM0A0) | _BV(COM0A1); // Inverted PWM
  TCCR0B = _BV(CS00);                  // no prescalling
  OCR0A = 0;                           // set comparator
  DDRD |= _BV(PD6);                    // turn on OC0A
}

uint16_t getADC()
{
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF)))
    ;                  // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)

  //const uint16_t adcVal = ADC; // (0..1023)
  //const float vref = 5;
  //const float volts = vref * adcVal / 1024;

  return ADC;
}

int main()
{
  // zainicjalizuj ADC
  adc_init();
  timers_init();
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  while (1)
  {
    int32_t adcRaw = (int)(getADC()/4) + 95;
    if(adcRaw > 255) adcRaw = 255;

    printf("ADCraw: %d\n", adcRaw);
    OCR0A = adcRaw;
  }
}
