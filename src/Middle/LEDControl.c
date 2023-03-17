/**
 * @file LEDControl.c
 * @author ryhoh
 * @brief LEDデバイスの制御を行う関数群
 * 
 */

/* インクルード -----------------------------------------------*/
#include "LEDControllers.h"

/* 関数定義 ---------------------------------------------------*/
void f_LED_MAX7219_init(Max7219_t *pst_max7219)
{
  /* 使用可否 */
  uint8_t u8_isready = pst_max7219->u8_isready;

  if (u8_isready == m_FALSE) {
    /* セットアップステップごとの処理 */
    switch (pst_max7219->u8_setupStep) {
      case m_LEDCONTROL_MAX7219_SETUP_STEP0:
        const uint8_t u8_sendData[m_LEDCONTROL_MAX7219_SETUP_STEP0_DATA_NUM] = {
          m_LEDCONTROL_MAX7219_SCANLIMIT, m_LEDCONTROL_MAX7219_SCANLIMIT_8,  /* スキャンリミット設定 -> 8桁 */
          m_LEDCONTROL_MAX7219_DECODEMODE, m_LEDCONTROL_MAX7219_DECODEMODE_NODECODE,  /* デコードモード -> No decodeモード */
          m_LEDCONTROL_MAX7219_BRIGHTNESS, m_LEDCONTROL_MAX7219_BRIGHTNESS_MIN, /* ブライトネス設定 */
          m_LEDCONTROL_MAX7219_DRIVEMODE, m_LEDCONTROL_MAX7219_DRIVEMODE_OPERATE   /* 駆動モード -> オペレート */
        };

        /* すべてのピンをOUTPUTに設定 */
        call_pinMode(pst_max7219->u8_dat, m_OUTPUT);
        call_pinMode(pst_max7219->u8_lat, m_OUTPUT);
        call_pinMode(pst_max7219->u8_clk, m_OUTPUT);

        /* SPI通信 */
        call_shiftOuts(
          &u8_sendData,
          m_LEDCONTROL_MAX7219_SETUP_STEP0_DATA_NUM,
          pst_max7219->u8_dat,
          pst_max7219->u8_clk,
          pst_max7219->u8_lat
        );

        break;
      case m_LEDCONTROL_MAX7219_SETUP_STEP1:
        // 残留表示を消去
        const uint8_t u8_sendData[m_LEDCONTROL_MAX7219_SETUP1_DATA_NUM] = {
          m_LEDCONTROL_MAX7219_PANEL1, m_LEDCONTROL_MAX7219_BLANK_DATA,  /* blankを送信 */
          m_LEDCONTROL_MAX7219_PANEL2, m_LEDCONTROL_MAX7219_BLANK_DATA,  /* blankを送信 */
          m_LEDCONTROL_MAX7219_PANEL3, m_LEDCONTROL_MAX7219_BLANK_DATA,  /* blankを送信 */
          m_LEDCONTROL_MAX7219_PANEL4, m_LEDCONTROL_MAX7219_BLANK_DATA,  /* blankを送信 */
          m_LEDCONTROL_MAX7219_PANEL5, m_LEDCONTROL_MAX7219_BLANK_DATA,  /* blankを送信 */
          m_LEDCONTROL_MAX7219_PANEL6, m_LEDCONTROL_MAX7219_BLANK_DATA,  /* blankを送信 */
          m_LEDCONTROL_MAX7219_PANEL7, m_LEDCONTROL_MAX7219_BLANK_DATA,  /* blankを送信 */
          m_LEDCONTROL_MAX7219_PANEL8, m_LEDCONTROL_MAX7219_BLANK_DATA   /* blankを送信 */
        };

        /* SPI通信 */
        call_shiftOuts(
          &u8_sendData,
          m_LEDCONTROL_MAX7219_SETUP1_DATA_NUM,
          pst_max7219->u8_dat,
          pst_max7219->u8_clk,
          pst_max7219->u8_lat
        );

        break;
      case m_LEDCONTROL_MAX7219_SETUP_STEP5:
        /* @@暫定 4周期=64ms後に使用可能とする */
        u8_isready = m_TRUE;
        break;
      default:
        break;
    }

    /* セットアップステップの更新 */
    M_CLIPINC(pst_max7219->u8_setupStep, UINT32_MAX);
  }

  /* 使用可否の更新 */
  pst_max7219->u8_isready = u8_isready;
}

// void testRunMax7219(Max7219 *max7219)
// {
//   // ディスプレイテストモード（全点灯）
//   sendToMax7219(max7219, 0x0f, 0x01);
//   call_sleep(1000);

//   // テストモード終了
//   sendToMax7219(max7219, 0x0f, 0x00);
//   call_sleep(500);

//   // リセット
//   for (uint8_t addr_i = 1; addr_i < 9; ++addr_i) {
//     sendToMax7219(max7219, addr_i, 0x00);
//   }
// }

void flushMatrixLEDByMax7219(Max7219 *max7219, MatrixLED *matrixLED)
{
  call_digitalWrite(max7219->lat, LOW);
  for (uint8_t row_i = 0; row_i < 8; ++row_i) {
    shiftOutToMax7219(max7219, row_i + 1, *(matrixLED->buffer + row_i));
  }
  call_digitalWrite(max7219->lat, HIGH);
  call_digitalWrite(max7219->lat, LOW);
}

void flushMatrixLEDsByMax7219(Max7219 *max7219, MatrixLED *matrixLEDs, uint8_t length)
{

  for (uint8_t row_i = 0; row_i < 8; ++row_i) {
    call_digitalWrite(max7219->lat, LOW);
    for (uint8_t matrix_i = 0; matrix_i < length; ++matrix_i) {
        shiftOutToMax7219(max7219, row_i + 1, *((matrixLEDs + matrix_i)->buffer + row_i));
    }
    call_digitalWrite(max7219->lat, HIGH);
    call_digitalWrite(max7219->lat, LOW);
  }
}
