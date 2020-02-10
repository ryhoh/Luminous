#include "MatrixData.h"

void MatrixData::flip() {
  for (short i = 0; i < this->matrix_size; ++i) {
    for (short j = 0; j < this->screen_n; ++j) {
      this->data[i][j] ^= 0b11111111;
    }
  }
}

MatrixData *MatrixData::clone() {
  MatrixData *res = new MatrixData(this->matrix_size, this->screen_n);
  
  for (short i = 0; i < this->matrix_size; ++i) {
    for (short j = 0; j < this->screen_n; ++j) {
      res->data[i][j] = this->data[i][j];
    }
  }

  return res;
}
