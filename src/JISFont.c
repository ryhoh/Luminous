#include "JISFont.h"

size_t writeJISToMatrixLED(
  MatrixLED *matrixLED,
  const char *c,
  int8_t offset_from_left
) {
  const uint8_t offset_from_top = 1;
  const uint8_t height_limit = (matrixLED->height < 7) ? matrixLED->height : 7;
  const int8_t left_end = -offset_from_left;  // 文字を左端に移動させてオフセット

  size_t read_char_size = 0;
  uint8_t row = 0;
  for (uint8_t row_i = 0; row_i < height_limit; ++row_i) {
    read_char_size = getJISRow(c, &row, row_i);
    if (left_end < 0)
      *(matrixLED->buffer + offset_from_top + row_i) |= row >> -left_end;
    else
      *(matrixLED->buffer + offset_from_top + row_i) |= row << left_end;
  }

  return read_char_size;
}

size_t writeJISsToMatrixLEDs(
  MatrixLED *matrixLEDs,
  uint8_t ledlen,
  const char *string,
  int8_t offset_from_left
) {
  if (string == NULL)
    return 0;
  
  uint8_t left_cur = offset_from_left;
  uint8_t matrix_cur = 0;

  // Skipping Empty Matrix (for big `offset_from_left`)
  for (uint8_t matrix_i = 0; matrix_i < ledlen; ++matrix_i) {
    if (matrixLEDs[matrix_i].width <= left_cur) {
      left_cur -= matrixLEDs[matrix_i].width;
      ++matrix_cur;
    } else break;
  }
  if (ledlen <= matrix_cur)  // matrixLED ran out
    return ledlen;
  
  const char *p = string;
  while (*p != '\0') {
    size_t read_char_n = writeJISToMatrixLED(matrixLEDs + matrix_cur, p, left_cur);
    if (read_char_n == 0) {
      // not found (got "n/a char")
      read_char_n = 1;
    }
    
    // (文字幅 5 + スキマ幅 1) または (文字幅 7 + スキマ幅 1)
    const uint8_t char_width = (read_char_n == 1) ? 6 : 8;
    left_cur += char_width;

    if (matrixLEDs->width <= left_cur) {
      // move to next matrix...
      left_cur %= (matrixLEDs + matrix_cur++)->width;
      ++matrix_cur;

      if (ledlen <= matrix_cur)  // matrixLED ran out
        return ledlen;

      // write rest of previous char
      writeJISToMatrixLED(matrixLEDs + matrix_cur, p, left_cur - char_width);
    }

    p += read_char_n;
  }

  if (left_cur < 0)
    return 0;
  return matrix_cur + 1;  // used matrix + initial matrix
}

void writeJISsToMatrixLEDArray(
  MatrixLEDArray *matrixLEDArray,
  const char *string,
  int8_t offset_from_left
) {
  writeJISsToMatrixLEDs(matrixLEDArray->matrixLEDs, matrixLEDArray->length, string, offset_from_left);
}
