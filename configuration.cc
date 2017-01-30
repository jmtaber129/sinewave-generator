#include "configuration.h"

#include <msp430g2553.h>

// TODO(jmtaber129): Change the register values to the values needed for this
// application.

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
  P1IFG = 0;
  P1OUT &= 0x00;
  // TODO(jmtaber129): Add additional settings for input PB.
}

void Configuration::ConfigureTimer() {
  // Configure timer for approx. 132231Hz.  Assuming 200 samples per sinewave
  // period, this allows a 220Hz wave by incrementing samples every 3 timer
  // interrupts, and a 330Hz wave by incrementing every 2 interrupts.
  TA1CCR0 = 121;  // Generate an interrupt every 7.56us.
  TA1CCTL0 = CCIE;
  TA1CTL = TASSEL_2 + ID_0 + MC_1;
}
