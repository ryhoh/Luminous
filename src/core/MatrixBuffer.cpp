#include "../../include/core/MatrixBuffer.h"

MatrixBuffer::MatrixBuffer(uint16_t screen_n) {
  if (screen_n < 1) matrix_utils::pError(1);

  this->screen_n = screen_n;
  this->twoDimArray = new matrix_utils::TwoDimArray(matrix_size, screen_n);
};

MatrixBuffer::~MatrixBuffer() {
  delete this->twoDimArray;
}

void MatrixBuffer::flip() {
  for (uint16_t i = 0; i < this->matrix_size; ++i)
    for (uint16_t j = 0; j < this->screen_n; ++j)
      this->twoDimArray->setAt(i, j, this->twoDimArray->getAt(i, j) ^ 0xFF);
}

void MatrixBuffer::fill(bool fill_bit) {
  uint8_t ch = fill_bit ? 0xFF : 0x00;
  for (uint16_t i = 0; i < this->matrix_size; ++i)
    for (uint16_t j = 0; j < this->screen_n; ++j)
      this->twoDimArray->setAt(i, j, ch);
}

MatrixBuffer *MatrixBuffer::clone() {
  MatrixBuffer *res = new MatrixBuffer(this->screen_n);

  for (uint16_t i = 0; i < this->matrix_size; ++i)
    for (uint16_t j = 0; j < this->screen_n; ++j)
      res->twoDimArray->setAt(i, j, this->twoDimArray->getAt(i, j));

  return res;
}

// 右端に新しいデータを追加
void MatrixBuffer::insertOneColumnAtRightEnd(bool invert) {
  for (uint16_t row_i = 0; row_i < this->matrix_size; ++row_i)
    this->twoDimArray->setBitAt(row_i, this->screen_n - 1, 0, invert);
}

// 左に1マスずらす．右端の埋めは，invertがtrueなら1
void MatrixBuffer::leftScroll(bool invert) {
  for (uint16_t screen_i = 0; screen_i < this->screen_n; ++screen_i) {
    for (uint16_t row_i = 0; row_i < this->matrix_size; ++row_i) {
      if (screen_i > 0) {  // 最上位ビットをとなりのscreenの最下位ビットへコピー
        bool move_bit = (this->twoDimArray->getAt(row_i, screen_i) >> 7) & 0b1;
        this->twoDimArray->setBitAt(row_i, screen_i - 1, 0, move_bit);
      }

      // 左にずらす
      this->twoDimArray->setAt(row_i, screen_i, this->twoDimArray->getAt(row_i, screen_i) << 1);
    }
  }

  this->insertOneColumnAtRightEnd(invert);
}

/* accessor */
uint16_t MatrixBuffer::getMatrix_size() {
  return this->matrix_size;
}

uint16_t MatrixBuffer::getScreen_n() {
  return this->screen_n;
}
matrix_utils::TwoDimArray *MatrixBuffer::getTwoDimArray() {
  return this->twoDimArray;
}
