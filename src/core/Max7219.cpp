#include <core/Max7219.h>
#include <Interface/DeviceAPI.h>


void Max7219_8x8::init() {
  DeviceAPI::call_pinMode(this->LAT, OUTPUT);
  DeviceAPI::call_pinMode(this->CLK, OUTPUT);
  DeviceAPI::call_pinMode(this->DAT, OUTPUT);

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
  DeviceAPI::call_sleep(1000);
}

void Max7219_8x8::test() {
  // ディスプレイテストモード（全点灯）
  this->sendToDevice(0x0f, 0x01);
  DeviceAPI::call_sleep(1000);

  // テストモード終了
  this->sendToDevice(0x0f, 0x00);
  DeviceAPI::call_sleep(500);

  // リセット
  for (int matrix_i = 0; matrix_i < this->screen_n; ++matrix_i) {
    for (int addr_i = 1; addr_i < 9; ++addr_i) {
      this->sendToDevice(addr_i, 0x00);
    }
  }
}

// params: レジスタアドレス, データ
void Max7219_8x8::sendToDevice(uint8_t addr, uint8_t data) {
  DeviceAPI::call_digitalWrite(this->LAT, LOW);
  this->shiftToRegister(addr, data);
  DeviceAPI::call_digitalWrite(this->LAT, HIGH);
  DeviceAPI::call_digitalWrite(this->LAT, LOW);
}

/* -- Common functions ---------------------------- */
// params: レジスタアドレス, データ
void Max7219_8x8::shiftToRegister(uint8_t addr, uint8_t data) {
  DeviceAPI::call_shiftOut(this->DAT, this->CLK, MSBFIRST, addr);
  DeviceAPI::call_shiftOut(this->DAT, this->CLK, MSBFIRST, data);
}

// 2次元配列の形で与えれば表示する
void Max7219_8x8::print(MatrixBuffer *matrixBuffer) {
  for (int row_i = 0; row_i < 8; ++row_i) {
    DeviceAPI::call_digitalWrite(this->LAT, LOW);
    for (int screen_i = 0; screen_i < this->screen_n; ++screen_i) {
      this->shiftToRegister(row_i+1, matrixBuffer->getTwoDimArray()->getAt(row_i, screen_i));
    }
    DeviceAPI::call_digitalWrite(this->LAT, HIGH);
    DeviceAPI::call_digitalWrite(this->LAT, LOW);
  }
}


#ifdef SIMULATOR  // ---------------------------------------
std::string Max7219_8x8_Simlator::generateScreen() {
  return this->virtualDevice.toString();
}

std::string Max7219_8x8_Simlator::VirtualDevice::toString() {
  std::string res = "";

  for (const std::deque<uint8_t> &deq: this->reg) {
    for (auto itr = deq.crbegin(); itr != deq.crend(); ++itr) {
      const uint8_t data = *itr;
      for (int i = 7; i > -1; --i) {
        if ((data >> i) & 0b1) res += "o";
        else res += ".";
      }
    }
    res += "\n";
  }

  return res;
}

void Max7219_8x8_Simlator::updateBuffer(MatrixBuffer *matrixBuffer) {
  for (int row_i = 0; row_i < 8; ++row_i)
    for (int screen_i = 0; screen_i < this->getScreen_n(); ++screen_i)
      this->shiftToRegister(row_i+1, matrixBuffer->getTwoDimArray()->getAt(row_i, screen_i));
}

void Max7219_8x8_Simlator::shiftToRegister(uint8_t addr, uint8_t data) {
  if (addr == 0) throw std::invalid_argument("invalid register address: \"0\"");
  --addr;  // to 0-base index

  // add row if there's not enough rows
  while (this->virtualDevice.reg.size() < addr + 1) {
    this->virtualDevice.reg.push_back(std::deque<uint8_t>());
  }

  // shifting
  std::deque<uint8_t> &deq = this->virtualDevice.reg.at(addr);
  deq.push_front(data);

  if (deq.size() > this->getScreen_n()) deq.pop_back();
}

void Max7219_8x8_Simlator::print(MatrixBuffer *matrixBuffer) {
  Max7219_8x8::print(matrixBuffer);

  this->updateBuffer(matrixBuffer);
  std::system("clear");
  std::cout << this->generateScreen();
}

#endif  /* SIMULATOR */
