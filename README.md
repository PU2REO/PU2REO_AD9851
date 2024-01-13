# PU2REO_AD9851
Arduino Library for the AD9851 - CMOS 180 MHz DDS/DAC Synthesizer

The AD9851 is a highly integrated device that uses advanced DDS technology, coupled with an internal high speed, high performance D/A converter, and comparator, to form a digitally programmable frequency synthesizer and clock generator function. When referenced to an accurate clock source, the AD9851 generates a stable frequency and phase-programmable digitized analog output sine wave. This sine wave can be used directly as a frequency source, or internally converted to a square wave for agile-clock generator applications. The AD9851’s innovative high speed DDS core accepts a 32-bit frequency tuning word, which results in an output tuning resolution of approximately 0.04Hz with a 180MHz system clock. The AD9851 contains a unique 6xREFCLK Multiplier circuit that eliminates the need for a high speed reference oscillator. The 6xREFCLK Multiplier has minimal impact on SFDR and phase noise characteristics. The AD9851 provides five bits of programmable phase modulation resolution to enable phase shifting of its output in increments of 11.25°.

# Public Methods
```cpp
  PU2REO_AD9851::PU2REO_AD9851(int W_CLK, int FQ_UD, int DATA, int RESET);
  void      	Init(void);
  void 			SetFrequency(double freq, uint8_t phase);
```

# What sets this library apart from the others?
* Calculation of Frequency Control Word is refined to maximize precision
* No manual bit-bang used when transferring from Aruino no AD9851

