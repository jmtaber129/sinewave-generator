#include "configuration.h"

#include <msp430g2553.h>

#define PB BIT3

void Configuration::Init() {
  ConfigureClocks();
  ConfigurePorts();
  ConfigureTimer();

  __bis_SR_register(GIE);
}

void Configuration::ConfigureClocks() {
  // Note: If you modify clock speeds or sources, you need to change the timer
  // configuration methods, too.
  WDTCTL = WDTPW + WDTHOLD;  // Stop WDT.
  DCOCTL = CALDCO_16MHZ;     // Set DCO.
  BCSCTL1 = CALBC1_16MHZ;
}

void Configuration::ConfigurePorts() {
  P2DIR |= 0xFF;  // All P2.x outputs.
  P2OUT &= 0x00;  // All P2.x reset.
  P1DIR = BIT7 + BIT6 + BIT5 + BIT4;  // DAC inputs.
  P1DIR |= DEBUG_LED;
  P1OUT = PB;   // Pullup for PB.
  P1REN |= PB;  // Resistor enable for PB.
  //P1IE |= PB;   // Enable interrupts for PB.
  //P1IES |= PB;  // Hi-to-Low edge for PB (active low).
  P1IFG &= ~0xFF;
  // TODO(jmtaber129): Add additional settings for input PB.
}

void Configuration::ConfigureTimer() {
  // Configure timer for approx. 132231Hz.  Assuming 200 samples per sinewave
  // period, this allows a 220Hz wave by incrementing samples every 3 timer
  // interrupts, and a 330Hz wave by incrementing every 2 interrupts.
  TA1CCR0 = DESIRED_COUNT_220HZ;  // Generate an interrupt every 7.56us.
  TA1CCTL0 = CCIE;
  TA1CTL = TASSEL_2 + ID_0 + MC_1;
}
