#ifndef _MATRIXBUFFER_H_
#define _MATRIXBUFFER_H_

#include "MatrixUtils.h"

#ifdef SIMULATOR
using std::uint8_t;
#endif

class MatrixBuffer {
private:
  short matrix_size = 8;
  short screen_n;
  matrix_utils::TwoDimArray *twoDimArray;

  virtual void insertOneColumnAtRightEnd(bool invert);

public:
  MatrixBuffer(short screen_n);
  MatrixBuffer(const MatrixBuffer &MatrixBuffer) = delete;  // 同じ配列のポインタを持つ複数オブジェクトの作成を禁止
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
