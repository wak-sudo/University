// Wojciech Kieloch 2024, wbudowane

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

const unsigned short dotTimeMS = 400;

// Meaning:
// 0 -> dot
// 1 -> dash
const char *mapToMorse[] = {
    "11111\n", // 0
    "01111\n", // 1
    "00111\n", // 2
    "00011\n", // 3
    "00001\n", // 4
    "00000\n", // 5
    "10000\n", // 6
    "11000\n", // 7
    "11100\n", // 8
    "11110\n", // 9

    "01\n",   // A
    "1000\n", // B
    "1010\n", // C
    "100\n",  // D
    "0\n",    // E
    "0010\n", // F
    "110\n",  // G
    "0000\n", // H
    "00\n",   // I
    "0111\n", // J
    "101\n",  // K
    "0100\n", // L
    "11\n",   // M
    "10\n",   // N
    "111\n",  // O
    "0110\n", // P
    "1101\n", // Q
    "010\n",  // R
    "000\n",  // S
    "1\n",    // T
    "001\n",  // U
    "0001\n", // V
    "011\n",  // W
    "1001\n", // X
    "1011\n", // Y
    "1100\n", // Z
};

char charIsValid(unsigned char c)
{
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' || c <= 'Z') || c == ' ';
}

const char *getMorseRepre(unsigned char c)
{
  if (c >= '0' && c <= '9')
    return mapToMorse[c - '0'];
  if (c >= 'a' && c <= 'z')
    return mapToMorse[c - 'a' + 10];
  if (c >= 'A' && c <= 'Z')
    return mapToMorse[c - 'A' + 10];
  return mapToMorse[0];
}

void translateLetter(unsigned char c, char isFirstInvoke)
{
  if(!charIsValid(c))
    return;

  if (c == ' ' && !isFirstInvoke)
  {
    // light off for 7 units, as there is a new word
    _delay_ms(7*dotTimeMS);
    return;
  }

  if (!isFirstInvoke)
    _delay_ms(3*dotTimeMS);
    // light off for 3 units, as there is a new character

  const char *morseRep = getMorseRepre(c);
  for (unsigned char i = 0; morseRep[i] != '\n'; i++)
  {
    if (morseRep[i] == '0')
    {
      // light on for 1 unit
      LED_PORT |= _BV(LED);
      _delay_ms(1*dotTimeMS);
      LED_PORT &= ~_BV(LED);
    }
    else
    {
      // light on for 3 units
      LED_PORT |= _BV(LED);
      _delay_ms(3*dotTimeMS);
      LED_PORT &= ~_BV(LED);
    }
    // light off for 1 unit, intra character
    _delay_ms(1*dotTimeMS);
  }
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

FILE uart_file;

int main()
{
  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  char isFirstLetter = 1;
  LED_DDR |= _BV(LED);

  printf("Initialized!\r\n");

  while (1)
  {
    char a = 0;
    scanf("%c", &a);
    printf("%c", a);
    translateLetter(a, isFirstLetter);
    isFirstLetter = 0;
  }
}