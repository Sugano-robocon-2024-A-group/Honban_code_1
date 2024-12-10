#include <Arduino.h>
#include <CAN.h>

// setupReceiver関数: 受信の初期設定
void setupReceiver() {
  // 受信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Receiver Initialized");
}

// setupSender関数: 送信の初期設定
void setupSender() {
  // 送信側の初期化が行われる際にメッセージをシリアルに表示
  Serial.println("CAN Sender Initialized");
}

// sendPacket関数: CANメッセージを送信する
/*
void sendPacket(int Ashimawari_Command) {
  Serial.print("Sending packet ... ");
  CAN.beginPacket(0x12);  // CANパケットを送信。ID: 0x12
  CAN.write(static_cast<uint8_t>(Ashimawari_Command));
  CAN.endPacket();  // 送信終了
  Serial.println("done");
}
*/
// receivePacket関数: CANメッセージを受信し、内容を表示する


// receivePacket関数: CANメッセージを受信し、内容を表示する
void receivePacket(uint32_t &id, uint16_t *data, uint16_t &length) {
  //delay(10); 
  int packetSize = CAN.parsePacket();  // 受信したパケットのサイズを取得
  //Serial.print("receivepacket\n ");
  /*if(packetSize>0){
    Serial.print("Received ");
  }*/
  if (packetSize==4) {  // パケットが受信された場合
    //Serial.print("Received ");

    for (int i = 0; i < length; i++) {
  uint8_t byte = CAN.read();  // 1 バイト読み取る
  data[i] = static_cast<uint16_t>(byte);  
    }

    // パケットIDを表示
    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    // RTRパケットの場合、要求された長さを表示
    if (CAN.packetRtr()) {Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      // 通常パケットの場合、受信データの長さを表示
      Serial.print(" and length ");
      Serial.println(packetSize);
      // データをシリアルに表示
      
      while (CAN.available()) {
        Serial.print((uint16_t)CAN.read());//⇒こいつで100って出てる。
    id = CAN.packetId();        // CAN IDを取得
    length = CAN.packetDlc();   // データ長を取得
    // データを配列に格納
      }
    Serial.println();  
    }
  }
}
/*
void receivePacket(uint32_t &id, uint16_t *data, uint16_t &length){
  delay(10); 
  int packetSize = CAN.parsePacket();  // 受信したパケットのサイズを取得

  if (packetSize) {  // パケットが受信された場合
    Serial.print("Received ");

    if (packetSize>0) {  // パケットが受信された場合
    Serial.print("Received ");

    for (int i = 0; i < length; i++) {
  uint8_t byte = CAN.read();  // 1 バイト読み取る
  data[i] = static_cast<uint16_t>(byte);  
    }


    // パケットIDを表示
    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    // RTRパケットの場合、要求された長さを表示
    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      // 通常パケットの場合、受信データの長さを表示
      Serial.print(" and length ");
      Serial.println(packetSize);

      // データをシリアルに表示
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }
    Serial.println();
  }
}*/
/*
 // sendPacket関数: CANメッセージを送信する
void sendPacket(int PS4_Circle, int PS4_Triangle, int PS4_R1, int PS4_L1) {
  Serial.print("Sending packet ... ");
  CAN.beginPacket(0x12);  // CANパケットを送信。ID: 0x12
  CAN.write(static_cast<uint8_t>(PS4_Circle));
  Serial.print("Sending 2");
  CAN.write(static_cast<uint8_t>(PS4_Triangle));
  Serial.print("Sending 3 ");
  CAN.write(static_cast<uint8_t>(PS4_R1));
  Serial.print("Sending 4 ");
  CAN.write(static_cast<uint8_t>(PS4_L1));
  CAN.endPacket();  // 送信終了
  
  Serial.println("done");

}
*/
