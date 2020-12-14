#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include "DotMatrixLED.h"

const String WIFI_SSID = "your_ssid";
const String WIFI_PASSWORD = "your_password";

Max7219 max7219;
MatrixLED matrixLEDs[8];

void setup() {
  pinMode(4, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    delay(500);
  }
  configTzTime("JST-9", "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

  initMax7219(&max7219, 5, 4, 13, 3);
  testRunMax7219(&max7219);
  for (uint8_t i = 0; i < 8; ++i) {
    initMatrixLED(&matrixLEDs[i], 8, 8);
  }

  writeJISsToMatrixLEDs(matrixLEDs, 3, "現在 ", 0);
  flushMatrixLEDsByMax7219(&max7219, matrixLEDs, 8);
}

void loop() {
  static time_t t;
  static struct tm *tm;
  static char now_s[] = "12:34:56";

  t = time(NULL);
  tm = localtime(&t);
  now_s[0] = '0' + tm->tm_hour / 10;
  now_s[1] = '0' + tm->tm_hour % 10;
  now_s[3] = '0' + tm->tm_min / 10;
  now_s[4] = '0' + tm->tm_min % 10;
  now_s[6] = '0' + tm->tm_sec / 10;
  now_s[7] = '0' + tm->tm_sec % 10;

  fillMatrixLED(matrixLEDs + 3, false);
  fillMatrixLED(matrixLEDs + 4, false);
  fillMatrixLED(matrixLEDs + 5, false);
  fillMatrixLED(matrixLEDs + 6, false);
  fillMatrixLED(matrixLEDs + 7, false);
  writeJISsToMatrixLEDs(matrixLEDs + 2, 6, now_s, 1);
  flushMatrixLEDsByMax7219(&max7219, matrixLEDs, 8);

  delay(1000);
}
