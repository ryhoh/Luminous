#include <stdio.h>
#include <stdint.h>

#include "DotMatrixLED.h"
#include "SimulatorDriver.h"

const uint8_t matrix_length = 4;

int main(int argc, char **argv) {
  const char *target = (argv[1] == NULL) ? "Hello" : argv[1];
  
  MatrixLED matrixLEDs[matrix_length];
  for (uint8_t i = 0; i < matrix_length; ++i) {
    initMatrixLED(&matrixLEDs[i], MATRIX_HEIGHT, MATRIX_WIDTH);
  }

  writeJISsToMatrixLEDs(matrixLEDs, matrix_length, target, 0);

  for (uint8_t row_i = 0; row_i < MATRIX_HEIGHT; ++row_i) {
    printMatrixLEDs(matrixLEDs, matrix_length, row_i);
  }
}
