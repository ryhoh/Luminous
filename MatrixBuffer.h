#ifndef MATRIXBUFFER_H
#define MATRIXBUFFER_H

#include "MatrixUtils.h"

class MatrixBuffer {
protected:
  short matrix_size;
  short screen_n;
  uint8_t **data;  // data[matrix_size][screen_n]

  virtual void insertOneColumnAtRightEnd(bool invert);

public:
  MatrixBuffer(short matrix_size, short screen_n);
  MatrixBuffer(const MatrixBuffer &MatrixBuffer) = delete;  // 同じポインタを持つ複数オブジェクトの作成を禁止
  virtual ~MatrixBuffer();

  virtual MatrixBuffer *clone();
  virtual void flip();
  virtual void leftScroll(bool invert);

  short getMatrix_size();
  short getScreen_n();
  uint8_t **getData();
};

#endif
