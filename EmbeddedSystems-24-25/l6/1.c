// Wojciech Kieloch 2024 Wbudowane

#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 9600                              // Baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // Obliczenie wartości UBRR

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
  // RXCIEn: RX Complete Interrupt Enable n
  // UDRIEn: USART Data Register Empty Interrupt Enable n
  UCSR0B |= _BV(RXCIE0);
}

volatile uint8_t received_char = 0;

ISR(USART_UDRE_vect)
{
    UDR0 = received_char;
    UCSR0B &= ~_BV(UDRIE0);
}

ISR(USART_RX_vect)
{
  received_char = UDR0;
  UCSR0B |= _BV(UDRIE0);
}

int main(void)
{
  uart_init();

  sei();

  set_sleep_mode(SLEEP_MODE_IDLE);

  while (1)
  {
    sleep_mode();
  }

  return 0;
}
