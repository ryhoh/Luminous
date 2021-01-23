#include <AsciiMatrix.h>

void writeAsciiToMatrixLED(MatrixLED &matrixLED, char c, int8_t offset_from_left)
{
  const uint8_t offset_from_top = (7 < matrixLED.height) ? matrixLED.height - 7 : 0;
  const uint8_t height_limit = (matrixLED.height < 7) ? matrixLED.height : 7;
  const int8_t left_end = 3 - offset_from_left;  // 文字を左端に移動させてオフセット

  for (uint8_t row_i = 0; row_i < height_limit; ++row_i) {
    const uint8_t row = getASCIIRow(c, row_i);
    if (left_end < 0)
      *(matrixLED.buffer + offset_from_top + row_i) |= row >> -left_end;
    else
      *(matrixLED.buffer + offset_from_top + row_i) |= row << left_end;
  }
}

void writeAsciisToMatrixLEDs(MatrixLED *matrixLEDs, uint8_t ledlen, const char *string, uint8_t offset_from_left)
{
  if (matrixLEDs == nullptr || string == nullptr)
    return;
  
  uint8_t left_cur = offset_from_left;
  uint8_t matrix_cur = 0;
  const char *p = string;
  while (*p != '\0') {
    writeAsciiToMatrixLED(*(matrixLEDs + matrix_cur), *p, left_cur);
    left_cur += 6;  // 文字幅 5 + スキマ幅 1

    if (matrixLEDs->width <= left_cur) {
      // move to next matrix...
      left_cur %= (matrixLEDs + matrix_cur++)->width;

      if (ledlen <= matrix_cur)  // matrixLED ran out
        return;

      // write rest of previous char
      writeAsciiToMatrixLED(*(matrixLEDs + matrix_cur), *p, left_cur - 6);
    }

    ++p;
  }
}

// void writeAsciisToMatrixLEDArray(MatrixLEDArray *matrixLEDArray, const char *string, uint8_t offset_from_left)
// {
//   writeAsciisToMatrixLEDs(matrixLEDArray->matrixLEDs, matrixLEDArray->length, string, offset_from_left);
// }
