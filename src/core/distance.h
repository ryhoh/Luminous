#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include "String5x7Buffer.h"

namespace dist {

  /* String5x7Buffer */

  // Behind state:      |-------|ABC
  // dist screen_right and text_left
  int toBehind(String5x7Buffer *string5x7Buffer) {
    return 0 - string5x7Buffer->getShifted_line_n();
  }

  // LeftSet state:     |ABC----|
  // dist screen_left  and text_left
  int toLeftSet(String5x7Buffer *string5x7Buffer) {
    return 8 * string5x7Buffer->getScreen_n() - string5x7Buffer->getShifted_line_n();
  }

  // RightSet state:    |----ABC|
  // dist screen_right and text_right
  int toRightSet(String5x7Buffer *string5x7Buffer) {
    return ((string5x7Buffer->getLen() - 1) * 6) - string5x7Buffer->getShifted_line_n();
  }

  // After state:    ABC|-------|
  // dist screen_left  and text_right
  int toAfter(String5x7Buffer *string5x7Buffer) {
    return (8 * string5x7Buffer->getScreen_n() + (string5x7Buffer->getLen() - 1) * 6) - string5x7Buffer->getShifted_line_n();
  }

  // Center state:      |--ABC--|
  // dist to point (distToLeftSet + distToRightSet = 0)
  int toCenter(String5x7Buffer *string5x7Buffer) {
    return (toLeftSet(string5x7Buffer) + toRightSet(string5x7Buffer)) / 2;
  }

}

#endif  /* _DISTANCE_H_ */
