#include <ESP32Servo.h>  // ESP32用のサーボライブラリ
#include <Arduino.h>
#include <CAN.h>
#include "souten.h"

Servo soutenServo;  // サーボオブジェクトを作成

// 装填用サーボモータの速度調整（大きいほど遅い）
const int Souten_Motor_Speed = 3;
// 装填用サーボモータ初期角度
const int Souten_Motor_initialAngle = 45;
const int Souten_Motor_targetAngle = -30;
const int Souten_Modoshi = 500;


void Souten(){
  moveServo(Souten_Motor_initialAngle, Souten_Motor_targetAngle); // 20度 -> 60度
  delay(Souten_Modoshi);                           // 一時停止
  moveServo(Souten_Motor_targetAngle, Souten_Motor_initialAngle); // 60度 -> 20度
}
//引いて、戻すを２つにわけるパターンを
void Souten_hiki(){
  moveServo(Souten_Motor_initialAngle, Souten_Motor_targetAngle); // 20度 -> 60度
  delay(Souten_Modoshi);                           // 一時停止
}
void Souten_modoshi(){
  moveServo(Souten_Motor_targetAngle, Souten_Motor_initialAngle); // 60度 -> 20度
  delay(Souten_Modoshi);
}

// サーボの動きを制御する関数
void moveServo(int startAngle, int endAngle) {
  int step = (startAngle < endAngle) ? 1 : -1; // 動きの方向
  for (int angle = startAngle; angle != endAngle + step; angle += step) {
    soutenServo.write(angle);
    delay(Souten_Motor_Speed); // 動作速度
  }
}
