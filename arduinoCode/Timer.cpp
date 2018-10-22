/*
 * This file is part of Arduino-Guitar-Trainer.
 * 
 * Created by Enrico Ceccolini on 09/10/2018.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "Timer.h"
#include "Arduino.h"

volatile bool timerFlag;

ISR(TIMER1_COMPA_vect){
  timerFlag = true;
}

Timer::Timer(){
  timerFlag = false;  
}

void Timer::setupFreq(int freq){
  
  // disabling interrupt
  cli();

  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; //initialize counter value to 0
  
  /* 
   * set compare match register
   * 
   * OCR1A = (16*2^20) / (100*PRESCALER) - 1 (must be < 65536)
   *
   * assuming a prescaler = 1024 => OCR1A = (16*2^10)/freq 
   */
  OCR1A = 16*1024/freq; 
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 for 8 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // enabling interrupt
  sei();
  
}

/* 
 *  period in ms 
 *  
 *   TCCR1A and TCCR1B are the two 8-bit control registers. 
 *   These set up the clock prescale ratio, set the mode for the counter/timer and set the output control for the PWM pins.
 *   TCNT1 is the 16 bit (for timer1) counter value itself.
*/
void Timer::setupPeriod(int period){
  
  // disabling interrupt
  cli();  // noInterrupts()

  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  
  /* 
   * set compare match register
   * 
   * OCR1A = (16*2^20) / (100*PRESCALER) - 1 (must be < 65536)
   *
   * assuming a prescaler = 1024 => OCR1A = (16*2^10)* period/1000 (being in ms) 
   */
  OCR1A = 16.384*period; 
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 for 8 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // enabling interrupt
  sei(); // interrupts()
  
}

void Timer::waitForNextTick(){
  /* wait for timer signal */
  while (!timerFlag){}
  timerFlag = false;
  
}
