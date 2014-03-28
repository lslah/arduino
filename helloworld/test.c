#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int _time_in_cs = 0;

void setup()
{ 
  cli();//stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 156;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
}

void toggle_register_bit(volatile uint8_t *reg, uint8_t bit)
{
  (*reg) ^= _BV(bit);
}

int time_in_ms(void)
{
  return _time_in_cs*10;
}

void sleep_us(int us) {
  int i = 0;
  for (i = 0; i < us; i++)
    _delay_us(1);
}
 
int main(void)
{
  DDRB |= _BV(DDB5);
  DDRB |= _BV(DDB0);

  setup();

  int led1_time = time_in_ms();
  int led2_time = time_in_ms();
  PORTB |= _BV(PORTB5);
  PORTB &= ~_BV(PORTB0);
  int pace = time_in_ms();
  unsigned int degree = 0;
  unsigned int us;
  while (1) {
    us = (degree*11)+500;
    toggle_register_bit(&PORTB, PORTB0);
    sleep_us(us);
    toggle_register_bit(&PORTB, PORTB0);

    degree += 44;
    if (degree >= 360) {
      degree -= 360;
    }

    _delay_ms(100);
    //if (time_in_ms() - led1_time >= 123) {
    //  toggle_register_bit(&PORTB, PORTB5);
    //  led1_time = time_in_ms();
    //}
    //if (time_in_ms() - led2_time >= 100) {
    //  toggle_register_bit(&PORTB, PORTB0);
    //  led2_time = time_in_ms();
    //}
  }

  return 0;
}

ISR(TIMER1_COMPA_vect) {
  _time_in_cs += 1;
}
