#include "../include/LEDMatrix.h"

#ifdef ARDUINO  // ---------------------------------------
void Max7219_8x8::init() {
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
  delay(1000);
}

void Max7219_8x8::test() {
  // ディスプレイテストモード（全点灯）
  this->sendToDevice(0x0f, 0x01);
  delay(1000);

  // テストモード終了
  this->sendToDevice(0x0f, 0x00);
  delay(500);

  // リセット
  for (int matrix_i = 0; matrix_i < this->screen_n; ++matrix_i) {
    for (int addr_i = 1; addr_i < 9; ++addr_i) {
      this->sendToDevice(addr_i, 0x00);
    }
  }
}

// params: レジスタアドレス, データ
void Max7219_8x8::sendToDevice(uint8_t addr, uint8_t data) {
  digitalWrite(this->LAT, LOW);
  this->shiftToRegister(addr, data);
  digitalWrite(this->LAT, HIGH);
  digitalWrite(this->LAT, LOW);
}
#endif


#ifdef SIMULATOR  // ---------------------------------------
void Max7219_8x8::VirtualDevice::print_screen() {
  std::system("clear");

  std::for_each(this->reg.cbegin(), this->reg.cend(), [](const std::deque<uint8_t>& deq) {
    std::for_each(deq.crbegin(), deq.crend(), [](const std::uint8_t& data) {
      for (int i = 7; i >-1; --i) {
        if ((data >> i) & 0b1) std::cout << "o";
        else std::cout << " ";
      }
    });
    std::cout << std::endl;
  });
  std::cout << std::endl;
}
#endif

/* -- Common functions ---------------------------- */
// params: レジスタアドレス, データ
void Max7219_8x8::shiftToRegister(uint8_t addr, uint8_t data) {
  #ifdef ARDUINO
    shiftOut(this->DAT, this->CLK, MSBFIRST, addr);
    shiftOut(this->DAT, this->CLK, MSBFIRST, data);
  #elif defined SIMULATOR
    if (addr == 0) throw std::invalid_argument("invalid register address: \"0\"");
    --addr;  // to 0-base index

    // add row if there's not enough rows
    while (this->virtualDevice.reg.size() < addr + 1) {
      this->virtualDevice.reg.push_back(std::deque<uint8_t>());
    }

    // shifting
    std::deque<uint8_t> &deq = this->virtualDevice.reg.at(addr);
    deq.push_front(data);

    if (deq.size() > this->screen_n) deq.pop_back();
  #endif

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

  #ifdef SIMULATOR
  this->virtualDevice.print_screen();
  #endif
}
