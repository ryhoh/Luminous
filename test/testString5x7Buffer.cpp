#include <gtest/gtest.h>
#include <String5x7Buffer.h>

TEST(String5x7BufferTest, construct){
  char text[] = "Hi";
  String5x7Buffer *sb = new String5x7Buffer(1, text);
  EXPECT_EQ(0, sb->distToBehind());
  EXPECT_EQ(8, sb->distToLeftSet());
  EXPECT_EQ(12, sb->distToRightSet());
  EXPECT_EQ(20, sb->distToAfter());
  delete sb;
}

TEST(String5x7BufferTest, leftScroll) {
  char text[] = "Hi";
  String5x7Buffer *sb = new String5x7Buffer(1, text);

  EXPECT_EQ(0x00, sb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0x00, sb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0x00, sb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0x00, sb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0x00, sb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0x00, sb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0x00, sb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0x00, sb->getTwoDimArray()->getAt(0, 7));

  sb->leftScroll(false);

  EXPECT_EQ(0b00000000, sb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b00000001, sb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b00000001, sb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b00000001, sb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b00000001, sb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b00000001, sb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b00000001, sb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b00000001, sb->getTwoDimArray()->getAt(0, 7));

  for (int i = 0; i < 4; ++i)
    sb->leftScroll(false);

  EXPECT_EQ(0b00000000, sb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b00011111, sb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 7));

  for (int i = 0; i < 3; ++i)
    sb->leftScroll(false);

  EXPECT_EQ(0b00000000, sb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b10001000, sb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b10001000, sb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b10001000, sb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b11111001, sb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b10001000, sb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b10001000, sb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b10001001, sb->getTwoDimArray()->getAt(0, 7));

  for (int i = 0; i < 2; ++i)
    sb->leftScroll(false);

  EXPECT_EQ(0b00000000, sb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b00100000, sb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b00100010, sb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b00100000, sb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b11100110, sb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b00100010, sb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b00100010, sb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b00100111, sb->getTwoDimArray()->getAt(0, 7));

  delete sb;
}

TEST(String5x7BufferTest, reset) {
  char text[] = "Hi";
  String5x7Buffer *sb = new String5x7Buffer(1, text);

  for (int i = 0; i < 5; ++i)
    sb->leftScroll(false);

  EXPECT_EQ(0b00000000, sb->getTwoDimArray()->getAt(0, 0));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 1));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 2));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 3));
  EXPECT_EQ(0b00011111, sb->getTwoDimArray()->getAt(0, 4));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 5));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 6));
  EXPECT_EQ(0b00010001, sb->getTwoDimArray()->getAt(0, 7));

  EXPECT_EQ(-5, sb->distToBehind());
  EXPECT_EQ(3, sb->distToLeftSet());
  EXPECT_EQ(7, sb->distToRightSet());
  EXPECT_EQ(15, sb->distToAfter());

  sb->reset();

  EXPECT_EQ(0, sb->distToBehind());
  EXPECT_EQ(8, sb->distToLeftSet());
  EXPECT_EQ(12, sb->distToRightSet());
  EXPECT_EQ(20, sb->distToAfter());

  delete sb;
}
