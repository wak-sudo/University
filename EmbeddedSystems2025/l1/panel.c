// Wojciech Kieloch 2024, wbudowane

#include <avr/io.h>
#include <util/delay.h>

int main()
{
  const short speedMS = 100;
  unsigned char ledPanelVal = 0b10000000;
  UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD |= 0b11111111;
  PORTD = ledPanelVal;
  while(1)
  {
    for(char i = 0; i<7; i++)
    {
      _delay_ms(speedMS);
      PORTD >>= 1; 
    }

    for(char i = 0; i<7; i++)
    {
      _delay_ms(speedMS);
      PORTD <<= 1; 
    }
  }
}