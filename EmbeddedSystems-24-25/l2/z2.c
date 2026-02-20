// Wojciech Kieloch 2024, wbudowane

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
#define BUTTON_INPUT PD5
#define BUTTON_PIN PIND
#define BUTTON_PORT PORTD

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

char morseToChar[256];

inline unsigned char codeCons(unsigned char codeLen, unsigned char code)
{
  return (codeLen << 5) | code;
}

// Meaning:
// 0 -> dot
// 1 -> dash
void fillMorseToChar()
{
  morseToChar[codeCons(5, 0b00011111)] = '0';
  morseToChar[codeCons(5, 0b00001111)] = '1';
  morseToChar[codeCons(5, 0b00000111)] = '2';
  morseToChar[codeCons(5, 0b00000011)] = '3';
  morseToChar[codeCons(5, 0b00000001)] = '4';
  morseToChar[codeCons(5, 0b00000000)] = '5';
  morseToChar[codeCons(5, 0b00010000)] = '6';
  morseToChar[codeCons(5, 0b00011000)] = '7';
  morseToChar[codeCons(5, 0b00011100)] = '8';
  morseToChar[codeCons(5, 0b00011110)] = '9';

  morseToChar[codeCons(2, 0b00000001)] = 'A';
  morseToChar[codeCons(4, 0b00001000)] = 'B';
  morseToChar[codeCons(4, 0b00001010)] = 'C';
  morseToChar[codeCons(3, 0b00000100)] = 'D';
  morseToChar[codeCons(1, 0b00000000)] = 'E';
  morseToChar[codeCons(4, 0b00000010)] = 'F';
  morseToChar[codeCons(3, 0b00000110)] = 'G';
  morseToChar[codeCons(4, 0b00000000)] = 'H';
  morseToChar[codeCons(2, 0b00000000)] = 'I';
  morseToChar[codeCons(4, 0b00000111)] = 'J';
  morseToChar[codeCons(3, 0b00000101)] = 'K';
  morseToChar[codeCons(4, 0b00000100)] = 'L';
  morseToChar[codeCons(2, 0b00000011)] = 'M';
  morseToChar[codeCons(2, 0b00000010)] = 'N';
  morseToChar[codeCons(3, 0b00000111)] = 'O';
  morseToChar[codeCons(4, 0b00000110)] = 'P';
  morseToChar[codeCons(4, 0b00001101)] = 'Q';
  morseToChar[codeCons(3, 0b00000010)] = 'R';
  morseToChar[codeCons(3, 0b00000000)] = 'S';
  morseToChar[codeCons(1, 0b00000001)] = 'T';
  morseToChar[codeCons(3, 0b00000001)] = 'U';
  morseToChar[codeCons(4, 0b00000001)] = 'V';
  morseToChar[codeCons(3, 0b00000011)] = 'W';
  morseToChar[codeCons(4, 0b00001001)] = 'X';
  morseToChar[codeCons(4, 0b00001011)] = 'Y';
  morseToChar[codeCons(4, 0b00001100)] = 'Z';
}

int readButtonVolt()
{
  if (BUTTON_PIN & _BV(BUTTON_INPUT))
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

unsigned int btnPressTime()
{
  const unsigned char pressPeriodMS = 8;
  if (readButtonVolt() == 0) // button is pressed
  {
    unsigned char prevStates = 0;
    unsigned int iter = 0;
    while (prevStates == 0)
    {
      for (char i = 0; i < pressPeriodMS; i++) // anitbouncing
      {
        prevStates = (prevStates << 1) | readButtonVolt();
        _delay_ms(1);
      }
      iter++;
    }
    return iter * pressPeriodMS;
  }
  return 0;
}

void listen()
{
  const short dotUnitMS = 500;
  const char loopTimeMS = 10;
  unsigned int timeSinceReleased = 0;
  char symBin = 0;
  char signalsCount = 0;
  // char iter = 0;
  while (1)
  {
    const unsigned int pressDelta = btnPressTime();
    if (pressDelta != 0)
    {
      timeSinceReleased = 0;
      symBin <<= 1;
      signalsCount++;
      if (pressDelta >= 3 * dotUnitMS)
      {
        symBin |= 1;
        // printf("Dash\n");
      }
      // else
      // printf("Dot\n");
    }
    else
    {
      timeSinceReleased += loopTimeMS;
      if (timeSinceReleased >= 3 * dotUnitMS)
      {
        if (signalsCount != 0)
        {
          const char symbol = morseToChar[codeCons(signalsCount, symBin)];
          symBin = 0;
          signalsCount = 0;

          LED_PORT |= _BV(LED);
          _delay_ms(30);
          LED_PORT &= ~_BV(LED);

          printf("%c", symbol);
        }
        else if (timeSinceReleased >= 7 * dotUnitMS) // a space
        {
          timeSinceReleased = 0;

          LED_PORT |= _BV(LED);
          _delay_ms(30);
          LED_PORT &= ~_BV(LED);

          printf(" ");
        }
      }
    }

    _delay_ms(loopTimeMS);

    /*iter++;
    if (iter == 100)
    {
      LED_PORT |= _BV(LED);
      _delay_ms(50);
      LED_PORT &= ~_BV(LED);
      iter = 0;
    }*/
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
  LED_DDR |= _BV(LED);

  fillMorseToChar();

  // Enable the internal pull-up resistor.
  BUTTON_PORT |= _BV(BUTTON_INPUT);

  printf("Initialized!\r\n");

  listen();
}