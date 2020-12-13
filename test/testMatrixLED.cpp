#include <gtest/gtest.h>
#include <iostream>

extern "C" {
  #include <MatrixLED.h>
}

TEST(MatrixLEDTest, init) {
  MatrixLED matLED;
  if (initMatrixLED(&matLED, 8, 8) == NULL) {
    std::cerr << "MatrixLED initialize failed" << std::endl;
  }
  EXPECT_EQ(8, matLED.width);
  EXPECT_EQ(8, matLED.height);
}

TEST(MatrixLEDTest, flip) {
  MatrixLED matLED;
  if (initMatrixLED(&matLED, 8, 8) == NULL) {
    std::cerr << "MatrixLED initialize failed" << std::endl;
  }

  matLED.buffer[0] = 0b00100100;
  matLED.buffer[1] = 0b01001001;
  matLED.buffer[2] = 0b10010010;
  matLED.buffer[3] = 0b00100100;
  matLED.buffer[4] = 0b01001001;
  matLED.buffer[5] = 0b10010010;
  matLED.buffer[6] = 0b00100100;
  matLED.buffer[7] = 0b01001001;

  flipMatrixLED(&matLED);

  EXPECT_EQ(0b11011011, matLED.buffer[0]);
  EXPECT_EQ(0b10110110, matLED.buffer[1]);
  EXPECT_EQ(0b01101101, matLED.buffer[2]);
  EXPECT_EQ(0b11011011, matLED.buffer[3]);
  EXPECT_EQ(0b10110110, matLED.buffer[4]);
  EXPECT_EQ(0b01101101, matLED.buffer[5]);
  EXPECT_EQ(0b11011011, matLED.buffer[6]);
  EXPECT_EQ(0b10110110, matLED.buffer[7]);

  flipMatrixLED(&matLED);

  EXPECT_EQ(0b00100100, matLED.buffer[0]);
  EXPECT_EQ(0b01001001, matLED.buffer[1]);
  EXPECT_EQ(0b10010010, matLED.buffer[2]);
  EXPECT_EQ(0b00100100, matLED.buffer[3]);
  EXPECT_EQ(0b01001001, matLED.buffer[4]);
  EXPECT_EQ(0b10010010, matLED.buffer[5]);
  EXPECT_EQ(0b00100100, matLED.buffer[6]);
  EXPECT_EQ(0b01001001, matLED.buffer[7]);
}

TEST(MatrixLEDTest, fill) {
  MatrixLED matLED;
  if (initMatrixLED(&matLED, 8, 8) == NULL) {
    std::cerr << "MatrixLED initialize failed" << std::endl;
  }

  matLED.buffer[0] = 0b00100100;
  matLED.buffer[1] = 0b01001001;
  matLED.buffer[2] = 0b10010010;
  matLED.buffer[3] = 0b00100100;
  matLED.buffer[4] = 0b01001001;
  matLED.buffer[5] = 0b10010010;
  matLED.buffer[6] = 0b00100100;
  matLED.buffer[7] = 0b01001001;

  fillMatrixLED(&matLED, false);

  EXPECT_EQ(0x00, matLED.buffer[0]);
  EXPECT_EQ(0x00, matLED.buffer[1]);
  EXPECT_EQ(0x00, matLED.buffer[2]);
  EXPECT_EQ(0x00, matLED.buffer[3]);
  EXPECT_EQ(0x00, matLED.buffer[4]);
  EXPECT_EQ(0x00, matLED.buffer[5]);
  EXPECT_EQ(0x00, matLED.buffer[6]);
  EXPECT_EQ(0x00, matLED.buffer[7]);

  fillMatrixLED(&matLED, true);

  EXPECT_EQ(0xFF, matLED.buffer[0]);
  EXPECT_EQ(0xFF, matLED.buffer[1]);
  EXPECT_EQ(0xFF, matLED.buffer[2]);
  EXPECT_EQ(0xFF, matLED.buffer[3]);
  EXPECT_EQ(0xFF, matLED.buffer[4]);
  EXPECT_EQ(0xFF, matLED.buffer[5]);
  EXPECT_EQ(0xFF, matLED.buffer[6]);
  EXPECT_EQ(0xFF, matLED.buffer[7]);
}

TEST(MatrixLEDTest, leftShift) {
  MatrixLED matLED;
  if (initMatrixLED(&matLED, 8, 8) == NULL) {
    std::cerr << "MatrixLED initialize failed" << std::endl;
  }

  uint8_t carry_bits;

  // 0 padding
  matLED.buffer[0] = 0b00100100;
  matLED.buffer[1] = 0b01001001;
  matLED.buffer[2] = 0b10010010;
  matLED.buffer[3] = 0b00100100;
  matLED.buffer[4] = 0b01001001;
  matLED.buffer[5] = 0b10010010;
  matLED.buffer[6] = 0b00100100;
  matLED.buffer[7] = 0b01001001;

  carry_bits = leftShiftMatrixLED(&matLED, 0x00);

  EXPECT_EQ(0b01001000, matLED.buffer[0]);
  EXPECT_EQ(0b10010010, matLED.buffer[1]);
  EXPECT_EQ(0b00100100, matLED.buffer[2]);
  EXPECT_EQ(0b01001000, matLED.buffer[3]);
  EXPECT_EQ(0b10010010, matLED.buffer[4]);
  EXPECT_EQ(0b00100100, matLED.buffer[5]);
  EXPECT_EQ(0b01001000, matLED.buffer[6]);
  EXPECT_EQ(0b10010010, matLED.buffer[7]);
  EXPECT_EQ(0b00100100, carry_bits);

  carry_bits = leftShiftMatrixLED(&matLED, 0x00);

  EXPECT_EQ(0b10010000, matLED.buffer[0]);
  EXPECT_EQ(0b00100100, matLED.buffer[1]);
  EXPECT_EQ(0b01001000, matLED.buffer[2]);
  EXPECT_EQ(0b10010000, matLED.buffer[3]);
  EXPECT_EQ(0b00100100, matLED.buffer[4]);
  EXPECT_EQ(0b01001000, matLED.buffer[5]);
  EXPECT_EQ(0b10010000, matLED.buffer[6]);
  EXPECT_EQ(0b00100100, matLED.buffer[7]);
  EXPECT_EQ(0b10010010, carry_bits);

  // 1 padding
  matLED.buffer[0] = 0b00100100;
  matLED.buffer[1] = 0b01001001;
  matLED.buffer[2] = 0b10010010;
  matLED.buffer[3] = 0b00100100;
  matLED.buffer[4] = 0b01001001;
  matLED.buffer[5] = 0b10010010;
  matLED.buffer[6] = 0b00100100;
  matLED.buffer[7] = 0b01001001;

  carry_bits = leftShiftMatrixLED(&matLED, 0xFF);

  EXPECT_EQ(0b01001001, matLED.buffer[0]);
  EXPECT_EQ(0b10010011, matLED.buffer[1]);
  EXPECT_EQ(0b00100101, matLED.buffer[2]);
  EXPECT_EQ(0b01001001, matLED.buffer[3]);
  EXPECT_EQ(0b10010011, matLED.buffer[4]);
  EXPECT_EQ(0b00100101, matLED.buffer[5]);
  EXPECT_EQ(0b01001001, matLED.buffer[6]);
  EXPECT_EQ(0b10010011, matLED.buffer[7]);
  EXPECT_EQ(0b00100100, carry_bits);

  carry_bits = leftShiftMatrixLED(&matLED, 0xFF);

  EXPECT_EQ(0b10010011, matLED.buffer[0]);
  EXPECT_EQ(0b00100111, matLED.buffer[1]);
  EXPECT_EQ(0b01001011, matLED.buffer[2]);
  EXPECT_EQ(0b10010011, matLED.buffer[3]);
  EXPECT_EQ(0b00100111, matLED.buffer[4]);
  EXPECT_EQ(0b01001011, matLED.buffer[5]);
  EXPECT_EQ(0b10010011, matLED.buffer[6]);
  EXPECT_EQ(0b00100111, matLED.buffer[7]);
  EXPECT_EQ(0b10010010, carry_bits);
}
