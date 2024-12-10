#include <Arduino.h>
#include "PWM.h"

// 電圧からデューティサイクルを計算する関数
int calculateDutyCycle(float voltage,float maxVoltage, float minVoltage) {
  // 電圧が範囲外の場合は制限
  if (voltage < minVoltage) voltage = minVoltage;
  if (voltage > maxVoltage) voltage = maxVoltage;

  // デューティサイクルを計算
  return (int)((voltage / maxVoltage) * 510);
}
