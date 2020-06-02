#include <gtest/gtest.h>
#include <string>

#include <core/String5x7Buffer.h>
#include <core/Max7219.h>


TEST(Max7219_8x8Test, withString5x7Buffer){
  Max7219_8x8_Simlator *dev = new Max7219_8x8_Simlator(8);
  // dev->screen_n = 8;
  char text[] = "Hello wooooorld!";
  String5x7Buffer *string5x7Buffer = new String5x7Buffer(8, text);

  dev->updateBuffer(string5x7Buffer);
  std::string expected = "\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n";
  EXPECT_EQ(expected, dev->generateScreen());

  while (string5x7Buffer->distToLeftSet() > 0)
    string5x7Buffer->leftScroll(false);
  dev->updateBuffer(string5x7Buffer);
  expected = "\
................................................................\n\
o...o........oo....oo...........................................\n\
o...o.........o.....o...........................................\n\
o...o..ooo....o.....o....ooo........o...o..ooo...ooo...ooo...ooo\n\
ooooo.o...o...o.....o...o...o.......o...o.o...o.o...o.o...o.o...\n\
o...o.ooooo...o.....o...o...o.......o.o.o.o...o.o...o.o...o.o...\n\
o...o.o.......o.....o...o...o.......o.o.o.o...o.o...o.o...o.o...\n\
o...o..oooo...o.....o....ooo.........o.o...ooo...ooo...ooo...ooo\n";
  EXPECT_EQ(expected, dev->generateScreen());

  while (string5x7Buffer->distToRightSet() > 0)
    string5x7Buffer->leftScroll(false);
  dev->updateBuffer(string5x7Buffer);
  expected = "\
................................................................\n\
...............................................oo.......o...o...\n\
................................................o.......o...o...\n\
....o...o..ooo...ooo...ooo...ooo...ooo..o.oo....o.......o...o...\n\
....o...o.o...o.o...o.o...o.o...o.o...o.oo..o...o.....ooo...o...\n\
....o.o.o.o...o.o...o.o...o.o...o.o...o.o.......o....o..o...o...\n\
....o.o.o.o...o.o...o.o...o.o...o.o...o.o.......o....o..o.......\n\
.....o.o...ooo...ooo...ooo...ooo...ooo..o.......o.....ooo...o...\n";
  EXPECT_EQ(expected, dev->generateScreen());

  while (string5x7Buffer->distToAfter() > 0)
    string5x7Buffer->leftScroll(false);
  dev->updateBuffer(string5x7Buffer);
  expected = "\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n\
................................................................\n";
  EXPECT_EQ(expected, dev->generateScreen());

  delete string5x7Buffer;
  delete dev;
}
