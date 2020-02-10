#include "MatrixBuffer.h"

void MatrixBuffer::flip() {
  for (short i = 0; i < this->matrix_size; ++i) {
    for (short j = 0; j < this->screen_n; ++j) {
      this->data[i][j] ^= 0b11111111;
    }
  }
}

MatrixBuffer *MatrixBuffer::clone() {
  MatrixBuffer *res = new MatrixBuffer(this->matrix_size, this->screen_n);
  
  for (short i = 0; i < this->matrix_size; ++i) {
    for (short j = 0; j < this->screen_n; ++j) {
      res->data[i][j] = this->data[i][j];
    }
  }

  return res;
}
