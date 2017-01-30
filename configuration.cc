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
  // Configure timer for 360Hz.
  TA1CCR0 = 8;  // Generate an interrupt every 0.2778ms.
  TA1CCTL0 = CCIE;
  TA1CTL = TASSEL_1 + ID_0 + MC_1;
}
