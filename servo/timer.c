#include "timer.h"

// Little unconventional, but cs means centi seconds.
volatile uint64_t _time_in_cs = 0;

// Initialize timer1 such that it interrupts every 10us = 1cs.
void initialize_timer()
{ 
  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 625;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);  // Prescaler 256
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

uint64_t time_in_ms(void)
{
  return _time_in_cs*10;
}

ISR(TIMER1_COMPA_vect) {
  _time_in_cs += 1;
}
