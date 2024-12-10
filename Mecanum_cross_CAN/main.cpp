#include <Arduino.h>
#include <PS4Controller.h>
#include <CAN.h>
#include <ESP.h>
#include "motor.hpp"
#include "PS4cross.hpp"
#include "tuushin.h"
#include "auto.hpp"

//int speed = 100;  // (0~255)
int Ashimawari_Command=0;
//使用ボタン設定用変数
  int PS4_Circle=5;
  int PS4_Triangle=5;
  int PS4_R1=5;
  int PS4_L1=5;

void setup()
{
  setupMotors();
  stopMotors();

  Serial.begin(115200);
  PS4.begin("1c:69:20:e6:20:d2");

  //CAN設定
const int CAN_TX_PIN = 27;  // 送信ピン（GPIO27）
const int CAN_RX_PIN = 26;  // 受信ピン（GPIO26）
  Serial.println("CAN Communication");
  CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);
  CAN.begin(500E3);// CANバスの初期化（通信速度500kbps）
  if (!CAN.begin(500E3)) {
    Serial.println("CANの初期化に失敗しました！"); // CAN初期化に失敗した場合、エラーメッセージを表示して停止
    while (1);  // 永久ループで停止
  }

  // 受信と送信の初期化関数を呼び出し
  //setupReceiver();
  setupSender();
  Serial.println("Start");

  Serial.println("Ready.");
}

void loop()
{

  Ashimawari_Command=0;
  
  if (PS4.Circle()){Serial.println("Circle Button");
      PS4_Circle=1;//
      Serial.printf("%d\n", PS4_Circle); 
    }
    if (PS4.Triangle()) {Serial.println("Triangle Button");
      PS4_Triangle=1;//
      Serial.printf("%d\n", PS4_Triangle);
      }
    if (PS4.R1()){Serial.println("R1 Button");
      PS4_R1=1;//
      Serial.printf("%d\n", PS4_R1);
      }
     if (PS4.L1()){Serial.println("L1 Button");
      PS4_L1=1;//]
      Serial.printf("%d\n", PS4_L1);
      }
 if(PS4_Circle==1||PS4_Triangle==1||PS4_R1==1||PS4_L1==1){
  sendToutekiCommand(PS4_Circle, PS4_Triangle, PS4_R1, PS4_L1);//先に送る
  PS4_Circle=0;
  PS4_Triangle=0;
  PS4_R1=0;
  PS4_L1=0;
  delay(150);
  }
  
  
  if (PS4.Right()){Ashimawari_Command=3;
      }
      if (PS4.Down()){Ashimawari_Command=2;
      }
      if (PS4.Up()){Ashimawari_Command=1;
      }
      if (PS4.Left()){Ashimawari_Command=4;
      }
      if (PS4.UpRight()){Ashimawari_Command=5;
      }
      if (PS4.DownRight()){Ashimawari_Command=6;
      }
      if (PS4.UpLeft()){Ashimawari_Command=7;
      }
      if (PS4.DownLeft()){Ashimawari_Command=8;
      }
   //その場回転をここで
   if (PS4.R2()){Serial.println("R1 Button");
      Ashimawari_Command=11;
      }
     if (PS4.L2()){Serial.println("L1 Button");
      Ashimawari_Command=12;
      }
  if (PS4.Cross()){//強制Restart
    ESP.restart();
      }
//Optionでコマンド「自動運転」
if (PS4.Options()){//強制Restart
    moveMecanumAuto();
      }
  //これは動かす関数
  PS4Cross(Ashimawari_Command);
  for (int i = 0; i < 4; i++)
  {
    driveMotor(i, targetDistance[i]);
  }
  delay(10);
}
