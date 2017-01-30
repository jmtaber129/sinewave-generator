#include <msp430g2553.h>

#include "configuration.h"
#include "sine-lut-generator.h"

#define MAP_BIT(num, in_bit, out_bit) (((num & in_bit) != 0) ? out_bit : 0)

int current_timer_count = 0;
//volatile int desired_timer_count = DESIRED_COUNT_220HZ;
volatile int desired_timer_count = 44;

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

  int next = SineLutGenerator::Next();

  P1OUT = MAP_BIT(next, BIT9, BIT4) +
          MAP_BIT(next, BIT8, BIT5) +
          MAP_BIT(next, BIT1, BIT6) +
          MAP_BIT(next, BIT0, BIT7);

  P1OUT |= DEBUG_LED & ((next & BIT9) != 0);

  P2OUT = MAP_BIT(next, BIT7, BIT0) +
          MAP_BIT(next, BIT6, BIT1) +
          MAP_BIT(next, BIT5, BIT2) +
          MAP_BIT(next, BIT4, BIT3) +
          MAP_BIT(next, BIT3, BIT4) +
          MAP_BIT(next, BIT2, BIT5);

  //P1OUT ^= DEBUG_LED;

  return;
}
