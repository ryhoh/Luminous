#include "LEDMatrix.h"

void Max7219_8x8::init() {
  delay(1000);
  pinMode(this->LAT, OUTPUT);
  pinMode(this->CLK, OUTPUT);
  pinMode(this->DAT, OUTPUT);

  // シャットダウン -> オペレート
  this->sendToDevice(0x0c, 0x01);
 
  // スキャンリミット設定 -> 8桁
  this->sendToDevice(0x0b, 0x07);
  
  // デコードモード -> No decodeモード
  this->sendToDevice(0x09, 0x00);
 
  // 残留表示を消去
  for (int addr_i = 1; addr_i < 9; ++addr_i) {
    // 文字blankを送信
    this->sendToDevice(addr_i, 0x0f);
  }
   
  // 輝度設定 -> 低輝度で
  this->sendToDevice(0x0a, 0x00);
  delay(2000);
}

void Max7219_8x8::test() {
  // ディスプレイテストモード（全点灯）
  this->sendToDevice(0x0f, 0x01);
  delay(2000);

  // テストモード終了
  this->sendToDevice(0x0f, 0x00);
  delay(1000);

  // リセット
  for (int matrix_i = 0; matrix_i < this->screen_n; ++matrix_i) {
    for (int addr_i = 1; addr_i < 9; ++addr_i) {
      this->sendToDevice(addr_i, 0x00);
    }
  }
}

// 2次元配列の形で与えれば表示する
void Max7219_8x8::print(MatrixBuffer *matrixBuffer) {
  for (int row_i = 0; row_i < 8; ++row_i) {
    digitalWrite(this->LAT, LOW);
    for (int screen_i = 0; screen_i < this->screen_n; ++screen_i) {
      this->shiftToRegister(row_i+1, matrixBuffer->getTwoDimArray()->getAt(row_i, screen_i));
    }
    digitalWrite(this->LAT, HIGH);
    digitalWrite(this->LAT, LOW);
  }
}

// params: レジスタアドレス, データ
void Max7219_8x8::shiftToRegister(uint8_t addr, uint8_t data) {
  shiftOut(this->DAT, this->CLK, MSBFIRST, addr);
  shiftOut(this->DAT, this->CLK, MSBFIRST, data);
}

// params: レジスタアドレス, データ
void Max7219_8x8::sendToDevice(uint8_t addr, uint8_t data) {
  digitalWrite(this->LAT, LOW);
  this->shiftToRegister(addr, data);
  digitalWrite(this->LAT, HIGH);
  digitalWrite(this->LAT, LOW);
}
