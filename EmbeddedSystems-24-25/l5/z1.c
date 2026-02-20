// Wojciech Kieloch 2024, wbudowane

#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

// PD2 ~ INT0
#define BUTTON_INPUT PD2
#define BUTTON_PIN PIND
#define BUTTON_PORT PORTD

#define LED PD7
#define LED_DDR DDRD
#define LED_PORT PORTD

uint16_t bufferSize = 1000;
char buffer[1000]; // initalized to 0s
uint16_t bufferPtr = 0;

void initTimers()
{
  TCCR1A = _BV(WGM12);            // CTC
  TCCR1B = _BV(CS11) | _BV(CS10); // 64 prescaler
  // calculated from the formula on page 100
  OCR1A = 124;
  TIMSK1 |= _BV(OCIE1A); // int. on
}

ISR(TIMER1_COMPA_vect) // when Timer 1 time passes
{
  bufferPtr += 1;
  if (bufferPtr >= bufferSize)
    bufferPtr = 0;

  if (buffer[bufferPtr] == 1)
  {
    LED_PORT |= _BV(LED);
    _delay_ms(5);
    LED_PORT &= ~_BV(LED);
    buffer[bufferPtr] = 0;
  }

  TCNT1 = 0;
}

ISR(INT0_vect) // button pressed
{
  buffer[bufferPtr] = 1;
}

int main()
{
  LED_DDR |= _BV(LED);
  BUTTON_PORT |= _BV(BUTTON_INPUT); // pull-up

  initTimers();
  EIMSK |= _BV(INT0);

  sei();

  set_sleep_mode(SLEEP_MODE_IDLE);

  while (1)
  {
    sleep_mode();
  }
}