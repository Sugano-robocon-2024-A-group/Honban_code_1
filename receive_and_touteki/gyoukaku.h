#include <ESP32Servo.h>  // ESP32用のサーボライブラリ
#include <Arduino.h>
int currentAngle =45;        // サーボの初期角度
extern Servo gyoukakuServo; // 外部から参照

void movegyoukakuServoBy(int delta) {
  currentAngle += delta;               // 角度を更新
  currentAngle = constrain(currentAngle, -5, 75); // 角度を制限 (-5°～75°)//25°で水平
  Serial.printf("仰角%d\n",currentAngle);
  gyoukakuServo.write(currentAngle);         // サーボを新しい角度に移動
  delay(15);                           // サーボが動く時間を確保
}
