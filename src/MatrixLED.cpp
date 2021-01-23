#include "MatrixLED.h"

/* --------- */
/* MatrixLED */
/* --------- */

MatrixLED::MatrixLED(uint8_t width, uint8_t height)
{
  if (8 < width || 8 < height) {
    width = height = 0;
    return;
  }

  this->width  = width;
  this->height = height;
  memset(this->buffer, 0, 8);
}

void MatrixLED::flip()
{
  for (uint8_t i = 0; i < this->height; ++i)
    *(this->buffer + i) ^= 0xFF;
}

void MatrixLED::fill(bool value)
{
  memset(this->buffer, 0xFF * value, 8);
}

uint8_t MatrixLED::leftShift(uint8_t padding)
{
  uint8_t out = 0;  // 7行目, 6行目, ... 0行目とビットを詰める padding も同じ並び
  for (uint8_t bit_i = 0; bit_i < this->height; ++bit_i)
  {
    bool top_bit = (*(this->buffer + bit_i) >> 7) & 0b1;
    if (top_bit)
      out |= 0x01 << bit_i;
    else
      out &= ~(0b01 << bit_i);

    *(this->buffer + bit_i) <<= 1;
    bool bottom_bit = (padding >> bit_i) & 0b1;
    if (bottom_bit)
      *(this->buffer + bit_i) |= 0x01;
    else
      *(this->buffer + bit_i) &= 0xFE;
  }
  return out;
}


// /* -------------- */
// /* MatrixLEDArray */
// /* -------------- */

// MatrixLEDArray::MatrixLEDArray(MatrixLED *matrixLEDs, size_t length)
// {
//   this->matrixLEDs = matrixLEDs;
//   this->length = length;
// }

// void MatrixLEDArray::flip()
// {
//   for (size_t i = 0; i < this->length; ++i) {
//     (this->matrixLEDs + i)->flip();
//   }
// }

// void MatrixLEDArray::fill(bool value)
// {
//   for (size_t i = 0; i < this->length; ++i) {
//     (this->matrixLEDs + i)->fill(value);
//   }
// }

// // not tested!
// uint8_t MatrixLEDArray::leftShift(uint8_t padding)
// {
//   uint8_t last_padding = padding;
//   for (size_t ledArray_i = 0; ledArray_i < this->length; ++ledArray_i) {
//     for (size_t i = 0; i < this->length; ++i) {
//       last_padding = (this->matrixLEDs + i)->leftShift(last_padding);
//     }
//   }

//   return last_padding;
// }


// /* ------------------ */
// /* MultipleMatrixLEDs */
// /* ------------------ */

// MultipleMatrixLEDArray *initMultipleMatrixLEDArray(MultipleMatrixLEDArray *multipleMatrixLEDArray, MatrixLEDArray *matrixLEDArray, MatrixLED **matrixLEDs, size_t col_length, size_t row_length, uint8_t width, uint8_t height)
// {
//   multipleMatrixLEDArray->matrixLEDArray = matrixLEDArray;
//   for (size_t row_i = 0; row_i < row_length; ++row_i) {
//     if (initMatrixLEDArray(multipleMatrixLEDArray->matrixLEDArray + row_i, *(matrixLEDs + row_i), col_length, width, height) == NULL)
//       return NULL;
//   }

//   return multipleMatrixLEDArray;
// }
