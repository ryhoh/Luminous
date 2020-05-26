#include "String5x7Buffer.h"

String5x7Buffer::String5x7Buffer(short screen_n, const char *text) : MatrixBuffer(screen_n) {
  // copying text
  this->len = 0;
  for (int i = 0; text[i] != '\0'; ++i) ++(this->len);
  ++(this->len);  // count for NULL code

  this->text = (char *)malloc(sizeof(char) * len);
  if (this->text == NULL) {
    matrix_utils::pError(2);
  }

  this->text[0] = '\0';
  strlcat(this->text, text, this->len);

  // replace \n \r with \0  (this affects as truncating)
  for (uint16_t i = 0; i < this->len; ++i) {
    if (this->text[i] == '\n' || this->text[i] == '\r') {
      this->text[i] = '\0';
      break;
    }
  }

  // count true length
  this->len = 0;
  for (int i = 0; this->text[i] != '\0'; ++i) ++(this->len);
  ++(this->len);  // count for NULL code
}

String5x7Buffer::~String5x7Buffer() {
  free(this->text);
  this->text = NULL;
}

uint8_t String5x7Buffer::toFont(char chr_num, int row_num) {
  // return 0xFF for illegal params
  if (chr_num < 0x20 || 0x7e < chr_num) return 0xFF;
  if (row_num < 0 || 6 < row_num) return 0xFF;

  // access as "_ASCII_FONTS['a' - OFFSET]"
  #ifdef ARDUINO  // using EEPROM
  return pgm_read_byte(&_ASCII_FONTS[chr_num - _ASCII_OFFSET][row_num]);
  #else
  return _ASCII_FONTS[chr_num - _ASCII_OFFSET][row_num];
  #endif
}

void String5x7Buffer::insertOneColumnAtRightEnd(bool invert) {
  ++(this->shifted_line_n);
  if (this->text[this->cur_text] == '\0') {  // no more character
    for (int row_i = 0; row_i < 8; ++row_i)
      this->twoDimArray->setBitAt(row_i, this->screen_n - 1, 0, invert);
    return;
  }

  // has character
  if (this->cur_in_chr == 5) {  // spacing between characters
    for (int row_i = 0; row_i < 8; ++row_i)
      this->twoDimArray->setBitAt(row_i, this->screen_n - 1, 0, invert);

    // shift to next character
    this->cur_in_chr = 0;
    ++(this->cur_text);
  } else {
    // screen height is 8 pixel but font height is 7 pixel
    this->twoDimArray->setBitAt(0, this->screen_n - 1, 0, invert);

    for (int row_i = 1; row_i < 8; ++row_i) {
      bool padding_bit = (this->toFont(this->text[this->cur_text], row_i - 1) >> (4 - this->cur_in_chr)) & 0b1;
      if (invert) padding_bit ^= 0b1;
      this->twoDimArray->setBitAt(row_i, this->screen_n - 1, 0, padding_bit);
    }

    // shift to next bit
    ++(this->cur_in_chr);
  }
}

void String5x7Buffer::reset() {
  this->cur_in_chr = 0;
  this->cur_text = 0;
  this->shifted_line_n = 0;
}

int String5x7Buffer::distToBehind() {
  return 0 - this->shifted_line_n;
}

int String5x7Buffer::distToLeftSet() {
  return 8 * this->screen_n - this->shifted_line_n;
}

// this->len - 1 : excepting '\0'
int String5x7Buffer::distToRightSet() {
  return ((this->len - 1) * 6) - this->shifted_line_n;
}

int String5x7Buffer::distToAfter() {
  return (8 * this->screen_n + (this->len - 1) * 6) - this->shifted_line_n;
}

int String5x7Buffer::distToCenter() {
  return (this->distToLeftSet() + this->distToRightSet()) / 2;
}
