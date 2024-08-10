// 使用Kaiser窗设计一个低通滤波器
#include <complex.h>
#include <liquid/liquid.h>
#include <stdio.h>

#define FILE_PATH_LOAD                                                         \
  "/mnt/d/Backup/Documents/GitHub/DSP-LIQUID-RESULT-CHECK/Liquid-dsp-data/"    \
  "Demo1_SINC_WAVE_AWGN_15db.dat"

#define FILE_PATH_SAVE                                                         \
  "/mnt/d/Backup/Documents/GitHub/DSP-LIQUID-RESULT-CHECK/Liquid-dsp-data/"    \
  "Demo1_SINC_WAVE_AWGN_15db_FILTERED.dat"

int main(int argc, char *argv[]) {

  // Design a LPF filter with Kaiser Window;
  float fc = 0.01f; // cut-off frequency
  float ft = 0.1f;  // filter transition
  float As = 65.0f; // stop-band attenuation[dB]
  float mu = 0.0f;  // fractional timing offset;

  // WARNING:estimate_req_filter_len会根据相关参数计算滤波器长度
  unsigned int filterOrder = estimate_req_filter_len(ft, As);
  float filterCoeff[filterOrder];

  // Filter H[n]
  liquid_firdes_kaiser(filterOrder, fc, As, mu, filterCoeff);

  // Create filter object
  firfilt_crcf lpfFilter = firfilt_crcf_create(filterCoeff, filterOrder);

  // liquid_float_complex
  float complex *x = malloc(sizeof(float complex) * 3000); // input signal
  float complex *y = malloc(sizeof(float complex) * 3000); // output signal

  // Load Data
  double *dataIn = malloc(sizeof(double) * 6000);
  FILE *fpIn = fopen(FILE_PATH_LOAD, "rb");
  fread(dataIn, sizeof(double), 6000, fpIn);

  for (int i = 0; i < 3000; i++) {
    x[i] = dataIn[2 * i] + dataIn[2 * i + 1] * I;
    // firfilt_crcf_push(lpfFilter, x[i]);
    // firfilt_crcf_execute(lpfFilter, y + i);
  }
  // firfilt_crcf_write(lpfFilter, x, 3000);
  firfilt_crcf_execute_block(lpfFilter, x, 3000, y);

  // Save Output Result
  float *dataOut = malloc(sizeof(float) * 6000);
  for (int i = 0; i < 3000; i++) {
    dataOut[2 * i] = crealf(y[i]);
    dataOut[2 * i + 1] = cimagf(y[i]);
    // printf("%f\n", dataOut[2 * i]);
    // printf("%f\n", dataOut[2 * i + 1]);
  }

  FILE *fpOut = fopen(FILE_PATH_SAVE, "wb+");
  fwrite(dataOut, sizeof(float), 3000, fpOut);

  fclose(fpIn);
  // fclose(fpOut);
  free(dataIn);
  free(dataOut);
  return EXIT_SUCCESS;
}
