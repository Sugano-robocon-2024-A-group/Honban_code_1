##
# Honban Code 1

## 作成・許諾
Sugano Robocon Aチーム (Masda, Otani, Suzaki, Fujiue)  

##(ここに例の文を入れる）##

## 制御主担当・ReadMe初期文文責
Otani

---

## ファイル構成
- **足回り側**: `Mechanum_Cross_CAN`
- **投擲側**: `Toutek_Honbanyou`

---

## 使用媒体
- **マイコン**: ESP32-WROOM-32 (2個)
  - 非正規品はBluetoothが使用できない場合があるため、正規品の使用を推奨。
- **書き込みツール**: Arduino Duo
- **使用コントローラ**: PS4Controller

---

## 使用方法
1. **マイコンの分割**
   - 足回り側: `Mechanum_Cross_CAN`
   - 投擲側: `Toutek_Honbanyou`

2. **接続ピンの設定**
   - 足回り側マイコン:
     - メカナムホイール用モータのピン（※エンコーダは接続しない）
   - 投擲側マイコン:
     - 投擲用モータの入力ピン
     - 仰角サーボのピン
     - 装填用サーボのピン

3. **CAN通信の接続**
   - マイコン同士をCAN通信で接続する。
   - GPIO26ピン（RX）とGPIO27ピン（TX）をそれぞれ接続。
   - CAN通信は「送信」が足回り側、「受信」が投擲側になる。

4. **PS4コントローラの設定と対象コード変更**
   - IDを確認し、`Mechanum_Cross_CAN`　に反映させる（これでつながるようになる）
   - 

---

## 注意事項
- 機構を変更する場合は、上記以外の使い方も可能。

---

## プログラム書き込み手順
1. **足回り側 (Mechanum_Cross_CAN)**:
   - Arduino IDEを開く。
   - `Mechanum_Cross_CAN`のコードをロード。
   - 選択:
     - ボード: `ESP32 Dev Module`
     - ポート: 接続されたESP32のポートを選択。
   - 書き込みボタンをクリックしてコードをマイコンにアップロード。

2. **投擲側 (Toutek_Honbanyou)**:
   - Arduino IDEを開く。
   - `Toutek_Honbanyou`のコードをロード。
   - 選択:
     - ボード: `ESP32 Dev Module`
     - ポート: 接続されたESP32のポートを選択。
   - 書き込みボタンをクリックしてコードをマイコンにアップロード。

---

## その他
必要に応じて各コードファイルや接続図を確認してください。

