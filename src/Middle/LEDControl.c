/**
 * @file LEDControl.c
 * @author ryhoh
 * @brief LEDデバイスの制御を行う関数群
 * 
 */

/* インクルード -----------------------------------------------*/
#include "Middle\LEDControl.h"

/* 外部変数宣言 -----------------------------------------------*/
MatrixBuffer_t gst_MatrixBuffer = {
  .u8_size = m_LEDCONTROL_BUFFER_SIZE,
  .u8_data = { 0 },
};

/* 関数定義 ---------------------------------------------------*/
/**
 * @brief LED制御タスクのメイン処理
 * 
 */
void f_LED_TaskMain(void) {
  /* Max7219 の構造体 */
  static Max7219_t sst_Max7219 = {
    .u8_dat = 0,
    .u8_lat = 0,
    .u8_clk = 0,
    .u8_state = m_LEDCONTROL_STATE_POWERON,
    .u8_setupStep = m_LEDCONTROL_MAX7219_SETUP_STEP0,
  };

  /* 初期化処理 */
  f_LED_MAX7219_Init(&sst_Max7219);

  /* バッファ出力処理 */
  f_LED_MAX7219_Flush(
    &sst_Max7219,
    &gst_MatrixBuffer.u8_data[0],
    gst_MatrixBuffer.u8_size
  );
}

/**
 * @brief Initialize Max7219.
 * @param max7219 [in] Pointer of Max7219 to initialize.
*/
static void f_LED_MAX7219_Init(Max7219_t *pst_max7219)
{
  /*  */
  uint8_t u8_state = pst_max7219->u8_state;

  if (u8_state != m_LEDCONTROL_STATE_DRIVE) {
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
        f_driver_pinMode(pst_max7219->u8_dat, m_OUTPUT);
        f_driver_pinMode(pst_max7219->u8_lat, m_OUTPUT);
        f_driver_pinMode(pst_max7219->u8_clk, m_OUTPUT);

        /* SPI通信 */
        f_driver_shiftOuts(
          &u8_sendData,
          m_LEDCONTROL_MAX7219_SETUP_STEP0_DATA_NUM,
          pst_max7219->u8_dat,
          pst_max7219->u8_clk,
          pst_max7219->u8_lat
        );

        /* 次の状態 */
        u8_state = m_LEDCONTROL_STATE_SETUP;

        break;
      case m_LEDCONTROL_MAX7219_SETUP_STEP1:
        // 残留表示を消去
        const uint8_t u8_sendData[m_LEDCONTROL_MAX7219_SETUP_STEP1_DATA_NUM] = {
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
        f_driver_shiftOuts(
          &u8_sendData,
          m_LEDCONTROL_MAX7219_SETUP_STEP1_DATA_NUM,
          pst_max7219->u8_dat,
          pst_max7219->u8_clk,
          pst_max7219->u8_lat
        );

        break;
      case m_LEDCONTROL_MAX7219_SETUP_STEP5:
        /* @@暫定 4周期=64ms後に使用可能とする */
        u8_state = m_LEDCONTROL_STATE_DRIVE;
        break;
      default:
        break;
    }

    /* セットアップステップの更新 */
    M_CLIPINC(pst_max7219->u8_setupStep, UINT8_MAX);
  }

  /* 状態の更新 */
  pst_max7219->u8_state = u8_state;
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

/**
 * @brief データをMAX7219に送信する
 * 
 * @param pst_max7219 MAX7219の情報
 * @param pu8_data 送信するデータ
 * @param u8_len 送信するデータの長さ
 */
static void f_LED_MAX7219_Flush(const Max7219_t *pst_max7219, const uint8_t pu8_data[], uint8_t u8_len)
{
  /* データ送信 */
  f_driver_shiftOuts(
    pu8_data,
    u8_len,
    pst_max7219->u8_dat,
    pst_max7219->u8_clk,
    pst_max7219->u8_lat
  );
}

/**
 * @brief MatrixBuffer_t アドレスを外部公開する
 * 
 * @return MatrixBuffer_t* 
 */
MatrixBuffer_t *f_LED_Get_MatrixBuffer(void)
{
  return &gst_MatrixBuffer;
}
