#ifndef SINEWAVE_GENERATOR_CONFIGURATION_H_
#define SINEWAVE_GENERATOR_CONFIGURATION_H_

#define PB_INPUT BIT3
#define DEBUG_LED BIT0
#define DESIRED_COUNT_330HZ 2
#define DESIRED_COUNT_220HZ 3

class Configuration {
  public:
    // Configures MSP430G2553 registers.
    static void Init();
  private:
    static void ConfigureClocks();

    // The port configuration is as follows (per launchpad layout):
    // P1.0 - P1.2: Unused   |
    // P1.3: S2 (pushbutton) |
    // P1.4: Bit 1 (MSB)     |  P1.7: Bit 10 (LSB)
    // P1.5: Bit 2           |  P1.6: Bit 9
    // P2.0: Bit 3           |  P2.5: Bit 8
    // P2.1: Bit 4           |  P2.4: Bit 7
    // P2.2: Bit 5           |  P2.3: Bit 6
    static void ConfigurePorts();

    static void ConfigureTimer();
};

#endif /* SINEWAVE_GENERATOR_CONFIGURATION_H_ */
