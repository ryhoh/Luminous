#ifndef _SIMLATORDRIVER_H_
#define _SIMLATORDRIVER_H_

#include "DotMatrixLED.h"

#define MATRIX_HEIGHT 8
#define MATRIX_WIDTH 8
const char on[]  = "●";
const char off[] = "○";

void printMatrixLEDs(
  const MatrixLED *matrixLEDs,
  uint8_t matrix_length,
  uint8_t row_i
) {
  for (uint8_t matrix_i = 0; matrix_i < matrix_length; ++matrix_i) {
    uint8_t row = *((matrixLEDs + matrix_i)->buffer + row_i);
    for (uint8_t bit_i = 0; bit_i < 8; ++bit_i)
      printf("%s", (row >> (7 - bit_i) & 0b1) ? on : off);
  }
  printf("\n");
}

#endif  /* _SIMLATORDRIVER_H_ */