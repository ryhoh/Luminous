#include "JISMatrix.h"

size_t writeJISToMatrixLED(MatrixLED &matrixLED, const char *c, int8_t offset_from_left)
{
  const uint8_t offset_from_top = 1;
  const uint8_t height_limit = (matrixLED.height < 7) ? matrixLED.height : 7;
  const int8_t left_end = -offset_from_left;  // 文字を左端に移動させてオフセット

  size_t read_char_size = 0;
  uint8_t row = 0;
  for (uint8_t row_i = 0; row_i < height_limit; ++row_i) {
    read_char_size = getJISRow(c, &row, row_i);
    if (left_end < 0)
      *(matrixLED.buffer + offset_from_top + row_i) |= row >> -left_end;
    else
      *(matrixLED.buffer + offset_from_top + row_i) |= row << left_end;
  }

  return read_char_size;
}

void writeJISsToMatrixLEDs(MatrixLED *matrixLEDs, uint8_t ledlen, const char *string, int8_t offset_from_left)
{
  if (matrixLEDs == nullptr || string == nullptr)
    return;
  
  uint8_t left_cur = offset_from_left;
  uint8_t matrix_cur = 0;
  const char *p = string;
  while (*p != '\0') {
    size_t read_char_n = writeJISToMatrixLED(*(matrixLEDs + matrix_cur), p, left_cur);
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

      if (ledlen <= matrix_cur)  // matrixLED ran out
        return;

      // write rest of previous char
      writeJISToMatrixLED(*(matrixLEDs + matrix_cur), p, left_cur - char_width);
    }

    p += read_char_n;
  }
}

// void writeJISsToMatrixLEDArray(MatrixLEDArray *matrixLEDArray, const char *string, int8_t offset_from_left)
// {
//   writeJISsToMatrixLEDs(matrixLEDArray->matrixLEDs, matrixLEDArray->length, string, offset_from_left);
// }

const uint8_t *_binarySearchForJISMatrix(uint32_t target)
{
  uint32_t imin = 0;
  uint32_t imax = _UTF_CODES_LEN - 1;
  while (imin <= imax) {
    // linear search for small area
    if (imax - imin < 50) {
      for (uint16_t entry_i = imin; entry_i < imax + 1; ++entry_i) {
        #ifdef ARDUINO
        if (pgm_read_dword(_UTF8_CODES + entry_i) == target)
        #else
        if (*(_UTF8_CODES + entry_i) == target)
        #endif
          return *(_UTF8_MATRIX + entry_i);
      }
      // not found
      return nullptr;
    }

    const uint32_t imid = imin + (imax - imin) / 2;
    #ifdef ARDUINO
    const uint32_t looking_code = (uint32_t)pgm_read_dword(_UTF8_CODES + imid);
    #else
    const uint32_t looking_code = *(_UTF8_CODES + imid);
    #endif

    if (looking_code > target)
      imax = imid - 1;
    else if (looking_code < target)
      imin = imid + 1;
    else
      return *(_UTF8_MATRIX + imid);
  }
  return nullptr;
}
