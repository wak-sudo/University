// Wojciech Kieloch 2024, wbudowane

#include <avr/io.h>
#include <util/delay.h>

// Looking from the front:
// PDO -> top right
// PD1 -> top
// PD2 -> top left
// PD3 -> dp
// PD4 -> bottom right
// PD5 -> middle
// PD6 -> bottom
// PD7 -> bottom left

char numberToLed[] = {
    0b11010111, // 0
    0b00010001, // 1
    0b11100011, // 2
    0b01110011, // 3
    0b00110101, // 4
    0b01110110, // 5
    0b11110110, // 6
    0b00010011, // 7
    0b11110111, // 8
    0b00110111, // 9
};

int main()
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD = 0b11111111;
  DDRC = 0b00000011;
  const char delayMS = 1;
  char numeberDisplay = 0;

  while (1)
  {
    for (short msPassed = 0; msPassed < 1000; msPassed += 2 * delayMS)
    {
      DDRD = numberToLed[numeberDisplay / 10];
      PORTC = 0b00000001;
      _delay_ms(delayMS);
      DDRD = numberToLed[numeberDisplay % 10];
      PORTC = 0b00000010;
      _delay_ms(delayMS);
    }
    numeberDisplay = (numeberDisplay + 1) % 60;
  }
}
