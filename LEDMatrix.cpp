#include "LEDMatrix.h"

void Max7219_8x8::init() {
  delay(1000);
  SPI.begin();
  pinMode(this->SS, OUTPUT);
  digitalWrite(this->SS, HIGH);

  /*初期設定*/
  //シャットダウン→オペレート
    //レジスタアドレス  オペレート
  this->sendToDevice(0x0c, 0x01);
 
  //スキャンリミット設定→8桁
    //レジスタアドレス  8桁全部を使用
  this->sendToDevice(0x0b, 0x07);
  
  //デコードモード→No decodeモード
    //レジスタアドレス  デコードしない
  this->sendToDevice(0x09, 0x00);
 
  //残留表示を消去
  for (int i = 1; i <= 8; i++) {
    //レジスタアドレス0x01～0x08を指定
    //文字blankを送信
    this->sendToDevice(i, 0x0f);
  }
   
  //輝度設定
    //レジスタアドレス  低輝度で
  this->sendToDevice(0x0a, 0x00);
  delay(2000);
}

void Max7219_8x8::test() {
  /*動作テスト*/
  
  //ディスプレイテストモード
    //レジスタアドレス  テストモード（全点灯）
  this->sendToDevice(0x0f, 0x01);
  delay(2000);

    //レジスタアドレス  テストモード終了
  this->sendToDevice(0x0f, 0x00);
  delay(1000);

  // リセット
  for(int j = 0; j < this->matrix_n; j++){
    for(int i = 1; i <= 8; i++){
      this->sendToDevice(i, 0x00);
    }
  }
}

// 2次元配列の形で与えれば表示する
void Max7219_8x8::print(const int pattern[][4]) {
  int i, d;                

  for(d = 0; d < 8; d++){
    for(i = 0; i < this->matrix_n; i++){
      this->sendToDevice(d+1, pattern[d][i]);
    }
  }
}

// params: レジスタアドレス, データ
void Max7219_8x8::sendToDevice(int addr, int data) {
  digitalWrite(this->SS, LOW);
  SPI.transfer(addr);
  SPI.transfer(data);
  digitalWrite(this->SS, HIGH);
}
