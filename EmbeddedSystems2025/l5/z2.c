// Wojciech Kieloch 2024, wbudowane

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

// PD2 ~ INT0
#define BUTTON_INPUT PD2
#define BUTTON_PIN PIND
#define BUTTON_PORT PORTD

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

volatile float lastRes = 0;

ISR(ADC_vect)
{
  const uint16_t adcVal = ADC; // (0..1023)
  const float vREF = 5;
  const float vADC = vREF * adcVal / 1024;

  // Ampers measuring
  // from voltage divider:
  // z1 = z2 * ((V_in / V_out) - 1)

  const float vIn = 5;
  const float otherResistor = 2200;
  const float resistance = otherResistor * ((vIn / vADC) - 1);
  lastRes = resistance;
}

void initADC()
{
  ADMUX = _BV(REFS0);                            // referencja AVcc, wejście ADC0
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRB |= _BV(ADTS1);                          // Auto trigger on External Interrupt Request 0.
  ADCSRA |= _BV(ADATE);                          // ADC Auto Trigger Enable
  ADCSRA |= _BV(ADIE);                           // ADC Interrupt Enable
  ADCSRA |= _BV(ADEN);                           // włącz ADC
  ADCSRA |= _BV(ADSC);                           // Start the first conversion (required)
}

int main()
{
  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  BUTTON_PORT |= _BV(BUTTON_INPUT); // pull-up

  initADC();
  // on INT0 conversion will start,
  // when finished ISR(ADC_vect) will be invoked.

  EIMSK |= _BV(INT0);

  sei();

  while (1)
  {
    printf("%f\n", lastRes);
    _delay_ms(1000);
  }
}