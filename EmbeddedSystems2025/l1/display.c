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

char numberToLed[] ={
  0b11101011, // 0
  0b10001000, // 1
  0b11000111, // 2
  0b11001110, // 3
  0b10101100, // 4
  0b01101110, // 5
  0b01101111, // 6
  0b11001000, // 7
  0b11101111, // 8
  0b11101100, // 9
};

int main()
{
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD |= 0b00000000;
  char i = 0;
  while(1)
  {
    DDRD = numberToLed[i];
    _delay_ms(1000);
    i = (i + 1) % 10;
  }
}