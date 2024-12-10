#ifndef TUUSHIN_H
#define TUUSHIN_H

// 関数宣言
void setupReceiver();  // 受信の初期設定
void setupSender();    // 送信の初期設定
void sendPacket(int Ashimawari_Command);
//void receivePacket();  // CANメッセージの受信
void receivePacket(uint32_t &id, uint16_t *data, uint16_t &length);

#endif

//void sendPacket(int PS4_Circle); // CANメッセージの送信
//void sendPacket(int PS4_Circle, int PS4_Triangle, int PS4_R1, int PS4_L1);
