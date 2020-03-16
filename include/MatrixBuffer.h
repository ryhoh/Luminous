#ifndef MATRIXBUFFER_H
#define MATRIXBUFFER_H

#include "MatrixUtils.h"

class MatrixBuffer {
protected:
  short matrix_size = 8;
  short screen_n;
  matrix_utils::TwoDimArray *twoDimArray;

  virtual void insertOneColumnAtRightEnd(bool invert);

public:
  MatrixBuffer(short screen_n);
  MatrixBuffer(const MatrixBuffer &MatrixBuffer) = delete;  // 同じポインタを持つ複数オブジェクトの作成を禁止
  virtual ~MatrixBuffer();

  virtual MatrixBuffer *clone();
  virtual void flip();
  virtual void fill(bool fill_bit);
  virtual void leftScroll(bool invert);

  short getMatrix_size();
  short getScreen_n();
  matrix_utils::TwoDimArray *getTwoDimArray();
};

#endif
