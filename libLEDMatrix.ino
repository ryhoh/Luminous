/*  
 *  SPI接続によるMAX7219の制御
 *  
 *  DATA  = MOSI            = D11へ接続
 *  LATCH = SS(slaveSelect) = デフォルトではD10へ接続
 *  CLOCK = SCK             = D13へ接続
 */

#include "LEDMatrix.h"

//#define SS 10
//#define LEDNUM 4

/*
 *  マトリクスLEDが複数接続（MAX7219のカスケード接続）されている場合、
 *  MAX7219に2Byteのデータを送る度に、古いデータが後ろのMAX7219へ押し出される
 *  
 *  表示内容の更新を行うには、全体の表示内容を作った上で、
 *  それを1行(1digit)ずつMAX7219の数だけ繰り返して送信し、
 *  8行(8digit)分それを繰り返す
 */

//struct MatrixData {
//  int data[][]
//};

Max7219_8x8 max7219_8x8;

// とりあえず1行分 LED8個のONOFFを1Byteで表す
const int sample1[8][4] = {
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                              {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                              {0b10101010, 0b10101010, 0b10101010, 0b10101010}
                            };
const int sample2[8][4] = {
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
  max7219_8x8.SS = 10;
  max7219_8x8.matrix_n = 4;
  max7219_8x8.init();
  max7219_8x8.test();
}

void loop(){
  max7219_8x8.print(sample1);
  delay(1000);

  max7219_8x8.print(sample2);
  delay(1000);
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
