#ifndef MATRIX_DATA_H
#define MATRIX_DATA_H

#include "MatrixUtils.h"

struct MatrixData {
  short matrix_size;
  short screen_n;
  unsigned char **data;  // data[matrix_size][screen_n]

  MatrixData(short matrix_size, short screen_n) {
    if (matrix_size < 1 || screen_n < 1) matrix_utils::pError(1);

    this->matrix_size = matrix_size;
    this->screen_n = screen_n;
    this->data = matrix_utils::alloc2dimArray(matrix_size, screen_n);
  };

  MatrixData(const MatrixData &matrixData) = delete;  // 同じポインタを持つ複数オブジェクトの作成を禁止

  ~MatrixData() {
    matrix_utils::free2dimArray(this->data, this->matrix_size);
  }

  MatrixData *clone();
  void flip();
};

#endif
