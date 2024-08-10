// FIR结构的抽样器
#include "complex.h"
#include "liquid/liquid.h"
#include "stdio.h"
#include "string.h"

#define FILE_PATH_LOAD                                                         \
  "/mnt/d/Backup/Documents/GitHub/DSP-LIQUID-RESULT-CHECK/Liquid-dsp-data/"    \
  "Demo2_SINC_WAVE.dat"

#define FILE_PATH_LOAD                                                         \
  "/mnt/d/Backup/Documents/GitHub/DSP-LIQUID-RESULT-CHECK/Liquid-dsp-data/"    \
  "Demo2_SINC_WAVE_DECI2.dat"

int main(int argc, char *argv[]) {

  // Filter Parameter
  unsigned int decimFactor = 2; // decimation factor
  unsigned int delay = 8;       // filter delay
  float stopbandAttenuation = 65.0f;
  unsigned int datalen =

      return EXIT_SUCCESS;
}
