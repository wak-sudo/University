// Wojciech Kieloch 2024, wbudowane

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
#define BARGRAPH_DDR DDRD
#define BARGRAPH_PORTS PORTD
#define BUTTONS_PORT PORTC
#define BUTTONS_PIN PINC
#define BTN_PREV PC0
#define BTN_RST PC1
#define BTN_NEXT PC2

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

void setupPins()
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  BARGRAPH_DDR = 0b11111111;
  BARGRAPH_PORTS = 0;
  BUTTONS_PORT |= _BV(BTN_NEXT);
  BUTTONS_PORT |= _BV(BTN_PREV);
  BUTTONS_PORT |= _BV(BTN_RST);
}

unsigned char readButtonVolt(unsigned char pinNo)
{
  if (BUTTONS_PIN & _BV(pinNo))
  {
    // Voltage is present (Pin is HIGH)
    return 1;
  }
  else
  {
    // No voltage (Pin is LOW)
    return 0;
  }
}

unsigned char btnPressed(unsigned char pinNo)
{
  const short debounceTime = 20;
  if (readButtonVolt(pinNo) != 0)
    return 0;
  while (readButtonVolt(pinNo) == 0) // button is pressed
    _delay_ms(debounceTime);
  return 1;
}

inline unsigned char BinaryToGray(unsigned char num)
{
  return num ^ (num >> 1); // The operator >> is shift right. The operator ^ is exclusive or.
}

int main()
{
  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  setupPins();

 // printf("Initialized!\r\n");

  unsigned char ledDisplay = 0;

  while (1)
  {
    if (btnPressed(BTN_NEXT))
    {
      ledDisplay++;
     // printf("BTN_NEXT!\n");
    }
    if (btnPressed(BTN_PREV))
    {
      ledDisplay--;
     // printf("BTN_PREV!\n");
    }
    if (btnPressed(BTN_RST))
    {
      ledDisplay = 0;
     // printf("BTN_RST!\n");
    }

    BARGRAPH_PORTS = BinaryToGray(ledDisplay);
  }
}