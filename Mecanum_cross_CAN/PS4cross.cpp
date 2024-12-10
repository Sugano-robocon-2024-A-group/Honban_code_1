#include <PS4Controller.h>
#include "PS4cross.hpp"

// 移動距離の目標設定（mm単位）
float targetDistance[4] = {0, 0, 0, 0}; // 各ホイールの移動距離
int speed[4]={160, 135, 160, 128};

//int speed_hidari_mae=160;//左前
//int speed_hidari_ushiro=135;//左後ろ255
//int speed_migi_mae=160;//右前
//int speed_migi_ushiro= 128;//右後

void PS4Cross(int Ashimawari_Command)
{
  //if (PS4.isConnected())
  //{
  if (Ashimawari_Command==0){
    targetDistance[0] = 0;
      targetDistance[1] =0;
      targetDistance[2] = 0;
      targetDistance[3] = 0;
    }
    if (Ashimawari_Command==4)
    {
      Serial.println("Left");
      targetDistance[0] = -speed[0];
      targetDistance[1] = speed[1];
      targetDistance[2] = speed[2];
      targetDistance[3] = -speed[3];
    }
    if (Ashimawari_Command==1)
    {
      Serial.println("Up");
      targetDistance[0] = speed[0];//左前
      targetDistance[1] = speed[1];//左後ろ
      targetDistance[2] = speed[2];//右前
      targetDistance[3] = speed[3];//右後
    }
    if (Ashimawari_Command==3)
    {
      Serial.println("Right");
      /*targetDistance[0] = speed;
      targetDistance[1] = -speed;
      targetDistance[2] = -speed;
      targetDistance[3] = speed;*/
      targetDistance[0] = speed[0];
      targetDistance[1] = -speed[1];
      targetDistance[2] = -speed[2];
      targetDistance[3] = speed[3];
    }
    
    if (Ashimawari_Command==2)
    {
      Serial.println("Down");
      targetDistance[0] = -speed[0];
      targetDistance[1] = -speed[1];
      targetDistance[2] = -speed[2];
      targetDistance[3] = -speed[3];
    }
    if (Ashimawari_Command==6)
    {
      Serial.println("Up Left");
      targetDistance[0] = 0;
      targetDistance[1] = speed[1];
      targetDistance[2] = speed[2];
      targetDistance[3] = 0;
    }
    if (Ashimawari_Command==5)
    {
      Serial.println("Up Right");
      targetDistance[0] = speed[0];
      targetDistance[1] = 0;
      targetDistance[2] = 0;
      targetDistance[3] = speed[3];
    }
    if (Ashimawari_Command==7)
    {
      Serial.println("Down Right");
      targetDistance[0] = 0;
      targetDistance[1] = -speed[1];
      targetDistance[2] = -speed[2];
      targetDistance[3] = 0;
    }
    if (Ashimawari_Command==8)
    {
      Serial.println("Down Left");
      targetDistance[0] = -speed[0];
      targetDistance[1] = 0;
      targetDistance[2] = 0;
      targetDistance[3] = -speed[3];
    }

    if (Ashimawari_Command==11)
    {
      Serial.println("Migi mawari");
      targetDistance[0] = speed[0];
      targetDistance[1] = speed[1];
      targetDistance[2] = -speed[2];
      targetDistance[3] = -speed[3];
    }
    if (Ashimawari_Command==12)
    {
      Serial.println("Hidari mawari");
      targetDistance[0] = -speed[0];
      targetDistance[1] = -speed[1];
      targetDistance[2] = speed[2];
      targetDistance[3] = speed[3];
    }
  //}
}

/*
void Jidou＿unten(){
  //2秒左へ


  //打て。
  
  //2秒
  
  
  }*/
