#ifndef MATRIXBUFFER_H
#define MATRIXBUFFER_H

#include "MatrixUtils.h"

struct MatrixBuffer {
  short matrix_size;
  short screen_n;
  unsigned char **data;  // data[matrix_size][screen_n]

  MatrixBuffer(short matrix_size, short screen_n);
  MatrixBuffer(const MatrixBuffer &MatrixBuffer) = delete;  // 同じポインタを持つ複数オブジェクトの作成を禁止
  ~MatrixBuffer();

  MatrixBuffer *clone();
  void flip();
};

#endif
