#include <msp430g2553.h>

#include "configuration.h"
#include "sine-lut-generator.h"

int current_timer_count = 0;
volatile int desired_timer_count = DESIRED_COUNT_220HZ;
//volatile int desired_timer_count = 30000;

int main(void) {
  Configuration::Init();

  return 0;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A (void) {
  if (++current_timer_count < desired_timer_count) {
    return;
  }
  current_timer_count = 0;

  int tmp = SineLutGenerator::Next();

  P1OUT ^= DEBUG_LED;

  return;
}
