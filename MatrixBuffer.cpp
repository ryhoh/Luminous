#include "MatrixBuffer.h"

MatrixBuffer::MatrixBuffer(short matrix_size, short screen_n) {
  if (matrix_size < 1 || screen_n < 1) matrix_utils::pError(1);

  this->matrix_size = matrix_size;
  this->screen_n = screen_n;
  this->data = matrix_utils::alloc2dimArray(matrix_size, screen_n);
};

MatrixBuffer::~MatrixBuffer() {
  matrix_utils::free2dimArray(this->data, this->matrix_size);
}

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
