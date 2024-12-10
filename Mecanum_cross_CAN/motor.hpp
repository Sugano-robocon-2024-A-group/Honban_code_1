#ifndef MOTOR_HPP
#define MOTOR_HPP

// モーターのピン設定 （左前　左後　右前　右後）
const int motor_pwm[4] = {21, 13, 16, 4}; // PWM出力ピン
const int motor_dir1[4] = {18, 25, 22, 32}; // 方向ピン1
const int motor_dir2[4] = {19, 14, 23, 33}; // 方向ピン2

// 関数のプロトタイプ宣言
void setupMotors();
void driveMotor(int index, float controlSignal);
void stopMotors();

#endif
