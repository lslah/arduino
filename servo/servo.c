// Move a servo 180 degrees forth and back.

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "timer.h"

void toggle_register_bit(volatile uint8_t *reg, uint8_t bit)
{
  (*reg) ^= _BV(bit);
}

void set_register_bit(volatile uint8_t *reg, uint8_t bit)
{
  (*reg) |= _BV(bit);
}

void unset_register_bit(volatile uint8_t *reg, uint8_t bit)
{
  (*reg) &= ~_BV(bit);
}

void sleep_us(unsigned int us) {
  unsigned int i = 0;
  for (i = 0; i < us; i++)
    _delay_us(1);
}

void servo_move_to(unsigned int degree)
{
  unsigned int us = (degree * 5) + 1000;
  toggle_register_bit(&PORTB, PORTB0);
  sleep_us(us);
  toggle_register_bit(&PORTB, PORTB0);
  _delay_ms(20);
}
 
int main(void)
{
  DDRB |= _BV(DDB5);
  DDRB |= _BV(DDB0);

  initialize_timer();

  unsigned int degree = 0;
  while (1) {
    set_register_bit(&PORTB, PORTB5);
    for (degree = 0; degree < 180; degree++) {
      servo_move_to(degree);
    }

    unset_register_bit(&PORTB, PORTB5);
    for (degree = 179; degree > 0; degree--) {
      servo_move_to(degree);
    }
  }

  return 0;
}
