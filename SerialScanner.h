#ifndef SERIALSCANNER_H
#define SERIALSCANNER_H

#include <Arduino.h>

class SerialScanner {
public:
  char status[16];
  char text[256];
  
  SerialScanner();
  int read();
};

#endif
