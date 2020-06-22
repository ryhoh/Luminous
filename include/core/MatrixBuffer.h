#ifndef _MATRIXBUFFER_H_
#define _MATRIXBUFFER_H_

#include "../util/MatrixUtils.h"
#include "../util/Typing.h"

class MatrixBuffer {
private:
  uint16_t matrix_size = 8;
  uint16_t screen_n;
  matrix_utils::TwoDimArray *twoDimArray;

  virtual void insertOneColumnAtRightEnd(bool invert);

public:
  MatrixBuffer(uint16_t screen_n);
  MatrixBuffer(const MatrixBuffer &MatrixBuffer) = delete;  // 同じ配列のポインタを持つ複数オブジェクトの作成を禁止
  virtual ~MatrixBuffer();

  virtual MatrixBuffer *clone();
  virtual void flip();
  virtual void fill(bool fill_bit);
  virtual void leftScroll(bool invert);

  uint16_t getMatrix_size();
  uint16_t getScreen_n();
  matrix_utils::TwoDimArray *getTwoDimArray();
};

#endif  /* _MATRIXBUFFER_H_ */
