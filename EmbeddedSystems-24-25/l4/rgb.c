// Wojciech Kieloch 2024, Wbudowane

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <util/delay.h>

#include <math.h>

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

void timers_init()
{
  TCCR1A = _BV(WGM10); // Fast PWM, 8-bit
  TCCR1B = _BV(WGM12);

  TCCR1A |= _BV(COM1A1) | _BV(COM1B1); // non-inverted PWM
  TCCR1B = _BV(CS10);                  // no prescalling

  OCR1AH = 0; // set comparator
  OCR1AL = 0;

  OCR1BH = 0;
  OCR1BL = 0;

  DDRB |= _BV(PB1); // turn on OC1A
  DDRB |= _BV(PB2); // turn on OC1B

  TCCR2A = _BV(WGM21) | _BV(WGM20); // Fast PWM
  TCCR2A |= _BV(COM2A1);            // non-inverted PWM
  TCCR2B |= _BV(CS20);              // no prescalling
  OCR2A = 0;                        // set comparator
  DDRB |= _BV(PB3);                 // turn on OC2A
}

struct Color
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct Color HsvToRgb(unsigned short hue)
{
  // saturation and value are constants equal 1.
  const float hPrim = (float)hue / 60;
  const float helper = (1 - abs(fmod(hPrim, 2) - 1));
  const float scaledHelper = round(helper * 255);

  struct Color color;
  const unsigned char region = floor(hPrim);
  switch (region)
  {
  case 0:
    color.r = 255;
    color.g = scaledHelper;
    color.b = 0;
    break;

  case 1:
    color.r = scaledHelper;
    color.g = 255;
    color.b = 0;
    break;

  case 2:
    color.r = 0;
    color.g = 255;
    color.b = scaledHelper;
    break;

  case 3:
    color.r = 0;
    color.g = scaledHelper;
    color.b = 255;
    break;

  case 4:
    color.r = scaledHelper;
    color.g = 0;
    color.b = 255;
    break;

  case 5:
    color.r = 255;
    color.g = 0;
    color.b = scaledHelper;
    break;

  default:
    break;
  }

  return color;
}

struct Color randColor()
{
  return HsvToRgb(rand() % 360);
}

void setColorPins(unsigned char r, unsigned char g, unsigned char b)
{
  OCR1AL = g;
  OCR1BL = r;
  OCR2A = b;
}

int main()
{
  srand(time(NULL));
  // zainicjalizuj ADC
  timers_init();
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  const float PI = 3.14159274101257324219;
  const unsigned char stepsCount = 20;
  const float delta = PI / stepsCount;
  while (1)
  {
    struct Color curColor = randColor();
    for (unsigned char i = 0; i != stepsCount + 1; i++)
    {
      const float step = delta * i;
      const unsigned char r = round(curColor.r * sin(step));
      const unsigned char b = round(curColor.g * sin(step));
      const unsigned char g = round(curColor.b * sin(step));
      setColorPins(r, g, b);
      _delay_ms(200);
    }
  }
}
