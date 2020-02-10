#ifndef MATRIXBUFFER_H
#define MATRIXBUFFER_H

#include "MatrixUtils.h"

struct MatrixBuffer {
  short matrix_size;
  short screen_n;
  unsigned char **data;  // data[matrix_size][screen_n]

  MatrixBuffer(short matrix_size, short screen_n) {
    if (matrix_size < 1 || screen_n < 1) matrix_utils::pError(1);

    this->matrix_size = matrix_size;
    this->screen_n = screen_n;
    this->data = matrix_utils::alloc2dimArray(matrix_size, screen_n);
  };

  MatrixBuffer(const MatrixBuffer &MatrixBuffer) = delete;  // 同じポインタを持つ複数オブジェクトの作成を禁止

  ~MatrixBuffer() {
    matrix_utils::free2dimArray(this->data, this->matrix_size);
  }

  MatrixBuffer *clone();
  void flip();
};

#endif
