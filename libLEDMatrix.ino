/*  
 *  SPI接続によるMAX7219の制御
 *  
 *  DATA  = MOSI            = D11へ接続
 *  LATCH = SS(slaveSelect) = デフォルトではD10へ接続
 *  CLOCK = SCK             = D13へ接続
 */
#include <SPI.h>

#define SS 10
#define LEDNUM 4

#define DEBUG 150

/*
 *  マトリクスLEDが複数接続（MAX7219のカスケード接続）されている場合、
 *  MAX7219に2Byteのデータを送る度に、古いデータが後ろのMAX7219へ押し出される
 *  
 *  表示内容の更新を行うには、全体の表示内容を作った上で、
 *  それを1行(1digit)ずつMAX7219の数だけ繰り返して送信し、
 *  8行(8digit)分それを繰り返す
 */

// とりあえず1行分 LED8個のONOFFを1Byteで表す
const int sample1[8][LEDNUM] = {
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010}
                            };
const int sample2[8][LEDNUM] = {
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101}
                            };
const int sample3[8][LEDNUM] = {
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101}
                            };

void setup(){
  delay(1000);
  SPI.begin();
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);

  /*初期設定*/
  //シャットダウン→オペレート
    //レジスタアドレス  オペレート
  sendTo7219(0x0c, 0x01);
 
  //スキャンリミット設定→8桁
    //レジスタアドレス  8桁全部を使用
  sendTo7219(0x0b, 0x07);
  
  //デコードモード→No decodeモード
    //レジスタアドレス  デコードしない
  sendTo7219(0x09, 0x00);
 
  //残留表示を消去
  for (int i = 1; i <= 8; i++) {
    //レジスタアドレス0x01～0x08を指定
    //文字blankを送信
    sendTo7219(i, 0x0f);
  }
   
  //輝度設定
    //レジスタアドレス  低輝度で
  sendTo7219(0x0a, 0x00);
  delay(2000);
 
  /*動作テスト*/
  
  //ディスプレイテストモード
    //レジスタアドレス  テストモード（全点灯）
  sendTo7219(0x0f, 0x01);
  delay(2000);

    //レジスタアドレス  テストモード終了
  sendTo7219(0x0f, 0x00);
  delay(1000);

  // リセット
  for(int j = 0; j < LEDNUM; j++){
    for(int i = 1; i <= 8; i++){
      sendTo7219(i, 0x00);
    }
  }
}

void loop(){
  printMatrix(sample1);
  delay(1000);

  printMatrix(sample2);
  delay(1000);

//  scrollLeft(table);  
}

// 2次元配列の形で与えれば表示する
void printMatrix(const int pattern[8][LEDNUM]){
  int i, d;                

  for(d = 0; d < 8; d++){
    for(i = 0; i < LEDNUM; i++){
      sendTo7219(d+1, pattern[d][i]);
    }
  }
}

// 引数は レジスタアドレス, データ の形
void sendTo7219(int high, int low){
  digitalWrite(SS, LOW);
  SPI.transfer(high);
  SPI.transfer(low);
  digitalWrite(SS, HIGH);
}

//void scrollLeft(int pattern[8][LEDNUM]){
//  int i, d;
////  int temp;
//
//  for(d = 1; d < 9; d++){
//    for(i = 0; i < LEDNUM; i++){
//      sendTo7219(d, pattern[d][i]);
//    }
//  }
//}

/*
 * // 縦方向のウェーブ
  if(0){
  for(d = 1; d <= 8; d++){
    for(c = 0; c < LEDNUM; c++)
      sendTo7219(d, 0xFF);
    delay(500);
  }

  for(d = 1; d <= 8; d++){
    for(c = 0; c < LEDNUM; c++)
      sendTo7219(d, 0x00);
    delay(500);
  }
  
  // 横方向のウェーブ
    // 作ろう
    // digit: 0b 00000000 00000000 00000000 00000000
  data = 1;
  d = 1;
  for(int x = 0; x < 8*LEDNUM; x++){
    for(d = 1; d < 3; d++){}
    
    for(int i = 0; i < (8*LEDNUM - x) / 8; i++){   // 後ろの表示しない部分
      sendTo7219(d, 0);
      delay(DEBUG);
    }
    
    sendTo7219(d, data << (x % 8));
    delay(DEBUG);
    
    for(int i = 0; i < x / 8; i++){                // 手前の表示しない部分
      sendTo7219(d, 0);
      delay(DEBUG);
    }
    delay(500);
  }*/
  /*for(d = 1; d <= 8; d++){
    for(int x = 0; x < 8*LEDNUM; x++){
      long int temp = data << 1;
      sendTo7219(d, temp >> 24);
      sendTo7219(d, temp >> 16);
      sendTo7219(d, temp >> 8);
      sendTo7219(d, temp);
    }
    delay(300);
  }*/
  /*
  data = 0xFFFFFFFF;
  for(int x = 0; x < 8*LEDNUM; x++){
    data = data & !(1 << x);
    for(d = 1; d <= 8; d++){
      sendTo7219(d, data >> 24);
      sendTo7219(d, data >> 16);
      sendTo7219(d, data >> 8);
      sendTo7219(d, data);
    }
    delay(300);
  }*/
