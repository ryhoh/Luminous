#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include "DotMatrixLED.h"

const String WIFI_SSID = "your_ssid";
const String WIFI_PASSWORD = "your_password";

Max7219 max7219;
MatrixLED matrixLEDs[8];

void setup() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  configTzTime("JST-9", "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

  initMax7219(&max7219, 5, 4, 13, 3);
  testRunMax7219(&max7219);
  for (uint8_t i = 0; i < 8; ++i) {
    initMatrixLED(&matrixLEDs[i], 8, 8);
  }

  writeAsciiToMatrixLED(matrixLEDs + 2, ':', 2);
  writeAsciiToMatrixLED(matrixLEDs + 5, ':', 2);
}

void loop() {
  static time_t t;
  static struct tm *tm;
  static uint8_t hour[2], minute[2], second[2];

  t = time(NULL);
  tm = localtime(&t);

  hour[0]   = tm->tm_hour / 10;
  hour[1]   = tm->tm_hour % 10;
  minute[0] = tm->tm_min / 10;
  minute[1] = tm->tm_min % 10;
  second[0] = tm->tm_sec / 10;
  second[1] = tm->tm_sec % 10;

  fillMatrixLED(matrixLEDs + 0, false);
  fillMatrixLED(matrixLEDs + 1, false);
  fillMatrixLED(matrixLEDs + 3, false);
  fillMatrixLED(matrixLEDs + 4, false);
  fillMatrixLED(matrixLEDs + 6, false);
  fillMatrixLED(matrixLEDs + 7, false);
  writeAsciiToMatrixLED(matrixLEDs + 0, '0' + hour[0]  , 2);
  writeAsciiToMatrixLED(matrixLEDs + 1, '0' + hour[1]  , 2);
  writeAsciiToMatrixLED(matrixLEDs + 3, '0' + minute[0], 2);
  writeAsciiToMatrixLED(matrixLEDs + 4, '0' + minute[1], 2);
  writeAsciiToMatrixLED(matrixLEDs + 6, '0' + second[0], 2);
  writeAsciiToMatrixLED(matrixLEDs + 7, '0' + second[1], 2);
  flushMatrixLEDsByMax7219(&max7219, matrixLEDs, 8);

  delay(1000);
}
