#ifndef _PARSER_H_
#define _PARSER_H_

#include "../core/String5x7Buffer.h"

namespace parser {
  String5x7Buffer *asciiParse(const string cmd, uint8_t screen_n);
  void subProcess(String5x7Buffer *string5x7Buffer, const string cmd);
}

#endif  /* _PARSER_H_ */
