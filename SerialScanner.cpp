#include "SerialScanner.h"

SerialScanner::SerialScanner() {
  Serial.begin(9600);
}

int SerialScanner::read() {
  if (Serial.available() > 0) {
    strncpy(this->status, "RECEIVED", 9);
    
    int i = 0;
    for (i = 0; Serial.available() > 0; ++i)
      this->text[i] = Serial.read();
    this->text[i-1] = '\0';  // replace '\n' to '\0'

    return 1;
  } else {
    strncpy(this->status, "NOTHING", 8);
    return 0;
  }
//  Serial.println(this->status);
}
