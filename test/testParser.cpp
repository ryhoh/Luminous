#include <gtest/gtest.h>

#include <command/parser.h>

TEST(ParserTest, scroll){
  // Parser *parser = new Parser(1);  // screen_n
  String5x7Buffer *sb = parser::asciiParse("center Hi;", 1);  // screen_n

  EXPECT_EQ(-10, sb->distToBehind());
  EXPECT_EQ(-2, sb->distToLeftSet());
  EXPECT_EQ(2, sb->distToRightSet());
  EXPECT_EQ(10, sb->distToAfter());
  EXPECT_EQ(0, sb->distToCenter());

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

  // 文字幅 12px, 5回左シフト済
  EXPECT_EQ(-5, sb->distToBehind());
  EXPECT_EQ(3, sb->distToLeftSet());
  EXPECT_EQ(7, sb->distToRightSet());
  EXPECT_EQ(15, sb->distToAfter());
  EXPECT_EQ(5, sb->distToCenter());

  sb->reset();

  EXPECT_EQ(0, sb->distToBehind());
  EXPECT_EQ(8, sb->distToLeftSet());
  EXPECT_EQ(12, sb->distToRightSet());
  EXPECT_EQ(20, sb->distToAfter());
  EXPECT_EQ(10, sb->distToCenter());

  delete sb;
}
