#ifndef SINEWAVE_GENERATOR_CONFIGURATION_H_
#define SINEWAVE_GENERATOR_CONFIGURATION_H_

class Configuration {
  public:
    // Configures MSP430G2553 registers.
    static void Init();
  private:
    static void ConfigureClocks();
    static void ConfigurePorts();
    static void ConfigureTimer();
};

#endif /* SINEWAVE_GENERATOR_CONFIGURATION_H_ */
