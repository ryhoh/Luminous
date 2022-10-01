#include "MatrixLED.h"

MatrixLED *initMatrixLED(
  MatrixLED *matrixLED,
  uint8_t width,
  uint8_t height
) {
  MACR_CLIP(width,  0, 8)
  MACR_CLIP(height, 0, 8)
  matrixLED->width  = width;
  matrixLED->height = height;
  memset(matrixLED->buffer, 0, 8);
  return matrixLED;
}

void flipMatrixLED(
  MatrixLED *matrixLED
) {
  for (uint8_t i = 0; i < matrixLED->height; ++i)
    *(matrixLED->buffer + i) ^= 0xFF;
}

void fillMatrixLED(
  MatrixLED *matrixLED,
  bool value
) {
  memset(matrixLED->buffer, 0xFF * value, 8);
}

uint8_t leftShiftMatrixLED(
  MatrixLED *matrixLED,
  uint8_t padding
) {
  uint8_t out = 0;  // 7行目, 6行目, ... 0行目とビットを詰める padding も同じ並び
  for (uint8_t bit_i = 0; bit_i < matrixLED->height; ++bit_i)
  {
    bool top_bit = (*(matrixLED->buffer + bit_i) >> 7) & 0b1;
    if (top_bit)
      out |= 0x01 << bit_i;
    else
      out &= ~(0b01 << bit_i);

    *(matrixLED->buffer + bit_i) <<= 1;
    bool bottom_bit = (padding >> bit_i) & 0b1;
    if (bottom_bit)
      *(matrixLED->buffer + bit_i) |= 0x01;
    else
      *(matrixLED->buffer + bit_i) &= 0xFE;
  }
  return out;
}

MatrixLEDArray *initMatrixLEDArray(
  MatrixLEDArray *matrixLEDArray,
  MatrixLED *matrixLEDs,
  size_t length,
  int8_t width,
  uint8_t height
) {
  matrixLEDArray->matrixLEDs = matrixLEDs;
  matrixLEDArray->length = length;
  for (size_t i = 0; i < length; ++i) {
    initMatrixLED(matrixLEDArray->matrixLEDs + i, width, height);
  }

  return matrixLEDArray;
}

void flipMatrixLEDArray(
  MatrixLEDArray *matrixLEDArray
) {
  for (size_t i = 0; i < matrixLEDArray->length; ++i) {
    flipMatrixLED(matrixLEDArray->matrixLEDs + i);
  }
}

void fillMatrixLEDArray(
  MatrixLEDArray *matrixLEDArray,
  bool value
) {
  for (size_t i = 0; i < matrixLEDArray->length; ++i) {
    fillMatrixLED(matrixLEDArray->matrixLEDs + i, value);
  }
}

// not tested!
uint8_t leftShiftMatrixLEDArray(
  MatrixLEDArray *matrixLEDArray,
  uint8_t padding
) {
  uint8_t last_padding = padding;
  for (size_t ledArray_i = 0; ledArray_i < matrixLEDArray->length; ++ledArray_i) {
    for (size_t i = 0; i < matrixLEDArray->length; ++i) {
      last_padding = leftShiftMatrixLED(matrixLEDArray->matrixLEDs + i, last_padding);
    }
  }

  return last_padding;
}
