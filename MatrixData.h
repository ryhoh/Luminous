#ifndef MATRIX_DATA_H
#define MATRIX_DATA_H

#include "MatrixUtils.h"

struct MatrixData {
  short matrix_size;
  short matrix_n;
  unsigned char **data;  // data[matrix_size][matrix_n]

  MatrixData(short matrix_size, short matrix_n) {
    if (matrix_size < 1 || matrix_n < 1) matrix_utils::pError(1);

    this->matrix_size = matrix_size;
    this->matrix_n = matrix_n;
    this->data = matrix_utils::alloc2dimArray(matrix_size, matrix_n);
  };

  ~MatrixData() {
    matrix_utils::free2dimArray(this->data, this->matrix_size);
  }

  MatrixData clone();
  void flip();
};

#endif
