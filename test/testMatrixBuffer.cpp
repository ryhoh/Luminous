#include <gtest/gtest.h>
#include <core/MatrixBuffer.h>

TEST(MatrixBufferTest, construct){
  MatrixBuffer *mb = new MatrixBuffer(1);
  EXPECT_EQ(8, mb->getMatrix_size());
  EXPECT_EQ(1, mb->getScreen_n());
  delete mb;
}

TEST(MatrixBufferTest, flip){
  MatrixBuffer *mb = new MatrixBuffer(1);

  mb->getTwoDimArray()->setAt(0, 0, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 1, 0b01001001);
  mb->getTwoDimArray()->setAt(0, 2, 0b10010010);
  mb->getTwoDimArray()->setAt(0, 3, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 4, 0b01001001);
  mb->getTwoDimArray()->setAt(0, 5, 0b10010010);
  mb->getTwoDimArray()->setAt(0, 6, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 7, 0b01001001);

  mb->flip();

  EXPECT_EQ(0b11011011, mb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b10110110, mb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b01101101, mb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b11011011, mb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b10110110, mb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b01101101, mb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b11011011, mb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b10110110, mb->getTwoDimArray()->getAt(0, 7));

  mb->flip();

  EXPECT_EQ(0b00100100, mb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b01001001, mb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b10010010, mb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b00100100, mb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b01001001, mb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b10010010, mb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b00100100, mb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b01001001, mb->getTwoDimArray()->getAt(0, 7));

  delete mb;
}

TEST(MatrixBufferTest, fill){
  MatrixBuffer *mb = new MatrixBuffer(1);

  mb->getTwoDimArray()->setAt(0, 0, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 1, 0b01001001);
  mb->getTwoDimArray()->setAt(0, 2, 0b10010010);
  mb->getTwoDimArray()->setAt(0, 3, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 4, 0b01001001);
  mb->getTwoDimArray()->setAt(0, 5, 0b10010010);
  mb->getTwoDimArray()->setAt(0, 6, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 7, 0b01001001);

  mb->fill(0);

  EXPECT_EQ(0x00, mb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0x00, mb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0x00, mb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0x00, mb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0x00, mb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0x00, mb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0x00, mb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0x00, mb->getTwoDimArray()->getAt(0, 7));

  mb->fill(1);

  EXPECT_EQ(0xFF, mb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0xFF, mb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0xFF, mb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0xFF, mb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0xFF, mb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0xFF, mb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0xFF, mb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0xFF, mb->getTwoDimArray()->getAt(0, 7));

  delete mb;
}

TEST(MatrixBufferTest, leftScroll){
  MatrixBuffer *mb = new MatrixBuffer(1);

  mb->getTwoDimArray()->setAt(0, 0, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 1, 0b01001001);
  mb->getTwoDimArray()->setAt(0, 2, 0b10010010);
  mb->getTwoDimArray()->setAt(0, 3, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 4, 0b01001001);
  mb->getTwoDimArray()->setAt(0, 5, 0b10010010);
  mb->getTwoDimArray()->setAt(0, 6, 0b00100100);
  mb->getTwoDimArray()->setAt(0, 7, 0b01001001);

  mb->leftScroll(false);

  EXPECT_EQ(0b01001000, mb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b10010010, mb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b00100100, mb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b01001000, mb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b10010010, mb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b00100100, mb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b01001000, mb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b10010010, mb->getTwoDimArray()->getAt(0, 7));

  mb->leftScroll(false);

  EXPECT_EQ(0b10010000, mb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b00100100, mb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b01001000, mb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b10010000, mb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b00100100, mb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b01001000, mb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b10010000, mb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b00100100, mb->getTwoDimArray()->getAt(0, 7));

  delete mb;
}
