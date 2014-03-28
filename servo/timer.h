#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

void initialize_timer(void);
uint64_t time_in_ms(void);

#endif  // TIMER_H
