#include <Arduino.h>
#include "auto.hpp"
#include "motor.hpp"
#include "PS4cross.hpp"
#include "tuushin.h"
//sendToutekiCommand(PS4_Circle, PS4_Triangle, PS4_R1, PS4_L1);//先に送る
//PS4Cross(Ashimawari_Command);

bool movementComplete = true;

void moveMecanumAuto()
{
  Serial.println("Jidou");
  /*
  */
  Serial.println("Unten");

  // 左方向　このSpeedを変える形。1直線に進む形になる。
  targetDistance[0] = -speed[0];
  targetDistance[1] = speed[1];
  targetDistance[2] = speed[2];
  targetDistance[3] = -speed[3];
//目標まで進める
  for (int i = 0; i < 4; i++)
  {
    // 制御信号に基づいてモーターを駆動
    driveMotor(i, targetDistance[i]);
  }
  delay(1000);//この値を変えて進む距離を決める
  stopMotors();// 現在の移動を停止
  //投げるフェーズ
  sendToutekiCommand(1, 0, 0, 0);//Moter ON
  delay(100);
  
  /*sendToutekiCommand(0, 1, 0, 0);
  delay(300);
  sendToutekiCommand(0, 1, 0, 0);
  delay(300);*/
  for (int j = 0; j < 12; j++){
    sendToutekiCommand(0, 1, 0, 0);
  delay(800);
  }//6発打つ！

  sendToutekiCommand(1, 0, 0, 0);//Moter OFF
  delay(1000);

  // 前方向
  targetDistance[0] = speed[0];
  targetDistance[1] = speed[1];
  targetDistance[2] = speed[2];
  targetDistance[3] = speed[3];

  for (int i = 0; i < 4; i++)
  {
    // 制御信号に基づいてモーターを駆動
    driveMotor(i, targetDistance[i]);
  }
  delay(1000); //この値を変えて進む距離を決める

  stopMotors(); // 現在の移動を停止
  delay(1000);
  
  // 前方向の移動も完了した場合、全移動完了
  movementComplete = true;
}
