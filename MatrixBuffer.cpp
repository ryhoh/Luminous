#include "MatrixBuffer.h"

MatrixBuffer::MatrixBuffer(short matrix_size, short screen_n) {
  if (matrix_size < 1 || screen_n < 1) matrix_utils::pError(1);

  this->matrix_size = matrix_size;
  this->screen_n = screen_n;
  this->data = matrix_utils::alloc2dimArray(matrix_size, screen_n);
};

MatrixBuffer::~MatrixBuffer() {
  matrix_utils::free2dimArray(this->data, this->matrix_size);
}

void MatrixBuffer::flip() {
  for (short i = 0; i < this->matrix_size; ++i) {
    for (short j = 0; j < this->screen_n; ++j) {
      this->data[i][j] ^= 0b11111111;
    }
  }
}

MatrixBuffer *MatrixBuffer::clone() {
  MatrixBuffer *res = new MatrixBuffer(this->matrix_size, this->screen_n);
  
  for (short i = 0; i < this->matrix_size; ++i) {
    for (short j = 0; j < this->screen_n; ++j) {
      res->data[i][j] = this->data[i][j];
    }
  }

  return res;
}

// 左に1マスずらす．右端の埋めは，one_paddingがtrueなら1
void MatrixBuffer::leftScroll(bool one_padding) {
  for (int screen_i = 0; screen_i < this->screen_n; ++screen_i) {
    for (int row_i = 0; row_i < this->matrix_size; ++row_i) {
      if (screen_i > 0) {  // 最上位ビットをとなりのscreenの最下位ビットへコピー
        bool move_bit = (this->data[row_i][screen_i] >> 7) & 0b1;
        if (move_bit) {
          this->data[row_i][screen_i - 1] |= 0b1;
        } else {
          this->data[row_i][screen_i - 1] &= 0b11111110;
        }
      }

      this->data[row_i][screen_i] <<= 1;  // 左にずらす
    }
  }

  // 右端に新しいデータを追加
  for (int row_i = 0; row_i < this->matrix_size; ++row_i) {
    if (one_padding) {
      this->data[row_i][this->screen_n - 1] |= 0b1;
    } else {
      this->data[row_i][this->screen_n - 1] &= 0b11111110;
    }
  }
}

/* accessor */
short MatrixBuffer::getMatrix_size() {
  return this->matrix_size;
}

short MatrixBuffer::getScreen_n() {
  return this->screen_n;
}

uint8_t **MatrixBuffer::getData() {
  return this->data;
}
