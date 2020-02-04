#include "LEDMatrix.h"
#include "MatrixData.h"

Max7219_8x8 max7219_8x8;
MatrixData matrixData1, matrixData2;

void setup(){
  max7219_8x8.SS = 10;
  max7219_8x8.matrix_n = 4;
  max7219_8x8.init();
  max7219_8x8.test();

  makeSimpleMatrix(matrixData1, false);
  makeSimpleMatrix(matrixData2, true);
}

void makeSimpleMatrix(MatrixData &matrixData, bool invert) {
  // LED8個のONOFFを1Byteで表す
  const unsigned char sample[8][4] = {  //  1枚目       2枚目        3枚目       4枚目
                                        {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                                        {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                                        {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                                        {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                                        {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                                        {0b10101010, 0b10101010, 0b10101010, 0b10101010},
                                        {0b01010101, 0b01010101, 0b01010101, 0b01010101},
                                        {0b10101010, 0b10101010, 0b10101010, 0b10101010}
                                      };
  matrixData.matrix_size = 8, matrixData.matrix_n = 4;
  matrixData.data = (unsigned char **)malloc(sizeof(unsigned char *) * matrixData.matrix_size);
  if (matrixData1.data == NULL) mallocError();
  
  for (int i = 0; i < matrixData.matrix_size; ++i) {
    matrixData.data[i] = (unsigned char *)malloc(sizeof(unsigned char) * matrixData.matrix_n);
    if (matrixData.data[i] == NULL) mallocError();
    for (int j = 0; j < matrixData.matrix_n; ++j) {
      if (invert) matrixData.data[i][j] = sample[i][j] ^ 0xFF;
      else matrixData.data[i][j] = sample[i][j];
    }
  }
}

void loop(){
  max7219_8x8.print(matrixData1.data);
  delay(1000);

  max7219_8x8.print(matrixData2.data);
  delay(1000);
}

void mallocError() {
  const static int built_in_LED = 13;
  pinMode(built_in_LED, OUTPUT);
  while (true) {
    digitalWrite(built_in_LED, HIGH);
    delay(50);
    digitalWrite(built_in_LED, LOW);
    delay(1000);
  }
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
