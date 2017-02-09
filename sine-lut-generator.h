#ifndef SINEWAVE_GENERATOR_SINE_LUT_GENERATOR_H_
#define SINEWAVE_GENERATOR_SINE_LUT_GENERATOR_H_

class SineLutGenerator {
  public:
    // Returns the next entry in the LUT.
    static int Next();
  private:
    static const int kLutSize = 200;
    static const int kSineLut[kLutSize];
    static int index;
};

#endif /* SINEWAVE_GENERATOR_SINE_LUT_GENERATOR_H_ */
