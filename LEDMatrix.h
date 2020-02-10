#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <SPI.h>
#include "MatrixData.h"

/*  
 *  SPI接続によるMAX7219の制御
 *  
 *  DATA  = MOSI            = D11へ接続
 *  LATCH = SS(slaveSelect) = デフォルトではD10へ接続
 *  CLOCK = SCK             = D13へ接続
 *  
 *  MAX7219: 7セグメントLED8桁を制御可能なチップ
 *           8x8ドットマトリクスLEDの制御にも転用可能
 */

/* 
 *  マトリクスLEDが複数接続（MAX7219のカスケード接続）されている場合、
 *  MAX7219に2Byteのデータを送る度に、古いデータが後ろのMAX7219へ押し出される
 *  
 *  表示内容の更新を行うには、全体の表示内容を作った上で、
 *  それを1行(1digit)ずつMAX7219の数だけ繰り返して送信し、
 *  8行(8digit)分それを繰り返す
 *  
 *  データ送信は (レジスタアドレス 1Byte, データ 1Byte) で行う
 *  レジスタアドレスは 0x01 ~ 0x08 を使う（0スタートでない）ことに注意
 */

struct Max7219_8x8 {
  unsigned char SS;
  unsigned char screen_n;

  void init();
  void test();
  void sendToDevice(int addr, int data);
  void print(MatrixData *matrixData);
};

#endif
