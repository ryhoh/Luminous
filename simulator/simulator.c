#include <stdio.h>
#include <stdint.h>
#include "DotMatrixLED.h"

const uint8_t matrix_length = 4;
const uint8_t height = 8;
const uint8_t width = 8;
const char on[]  = "●";
const char off[] = "○";

int main(int argc, char **argv) {
  const char *target = (argv[1] == NULL) ? "Hello" : argv[1];
  
  MatrixLED matrixLEDs[matrix_length];
  for (uint8_t i = 0; i < matrix_length; ++i) {
    initMatrixLED(&matrixLEDs[i], height, width);
  }

  writeJISsToMatrixLEDs(matrixLEDs, matrix_length, target, 0);

  for (uint8_t row_i = 0; row_i < height; ++row_i) {
    for (uint8_t matrix_i = 0; matrix_i < matrix_length; ++matrix_i) {
      uint8_t row = *((matrixLEDs + matrix_i)->buffer + row_i);
      for (uint8_t bit_i = 0; bit_i < 8; ++bit_i)
        printf("%s", (row >> (7 - bit_i) & 0b1) ? on : off);
    }
    printf("\n");
  }
}