#include "Middle\MatrixLED.h"

MatrixLED *initMatrixLED(MatrixLED *matrixLED, uint8_t width, uint8_t height)
{
  if (8 < width || 8 < height)
    return NULL;

  matrixLED->width  = width;
  matrixLED->height = height;
  memset(matrixLED->buffer, 0, 8);
  return matrixLED;
}

void flipMatrixLED(MatrixLED *matrixLED)
{
  for (uint8_t i = 0; i < matrixLED->height; ++i)
    *(matrixLED->buffer + i) ^= 0xFF;
}

void fillMatrixLED(MatrixLED *matrixLED, bool value)
{
  memset(matrixLED->buffer, 0xFF * value, 8);
}

uint8_t leftShiftMatrixLED(MatrixLED *matrixLED, uint8_t padding)
{
  uint8_t out;  // 7行目, 6行目, ... 0行目とビットを詰める padding も同じ並び
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
