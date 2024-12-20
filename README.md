##
# Honban Code 1

## 作成・許諾 
Sugano Robocon Aチーム (益田隆太郎、大谷卓輝、藤上晃成、洲﨑一眞)  
## * このソフトウェアパッケージは、3条項BSDライセンスの下、再配布及び使用が許可されます
## @ 2024 Sugano Robocon A team

## 制御主担当・ReadMe初期文文責  Otani
## 制御副担当　Fujiue

---

## ファイル構成
- **足回り側**: `Mechanum_Cross_CAN`
- **投擲側**: `Toutek_Honbanyou`

全体システムは、全体のReadmeの方の図を参照あれ

---

## 使用媒体
- **マイコン**: ESP32-WROOM-32 (2個)
  - 非正規品はBluetoothが使用できない場合があるため、正規品の使用を推奨。
- **書き込みツール**: Arduino Duo
- **使用コントローラ**: PS4Controller

---

## 使用ライブラリとバージョン
- **<Arduino.h>**         (ボードでついてくる）Arduino　AVR　Boards  ver.1.8.3
- **<CAN.h>**               ver.0.3.1
- **<ESP.h>**
- ⇒ (ボード) **esp32**  ver.2.0.14  （これが大事）
- **<ESP32Servo.h>**　　　　ver.3.0.5
- **<PS4Controller.h>**:別途参照⇒

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
   - IDを確認する
   - `Mechanum_Cross_CAN`　のmainの24行目「PS4.begin("1c:69:20:e6:20:d2");」に反映させる（IDを書く部分が見ての通りある）
   - あとはPS4コントローラの電源ボタンを押せばつながる（Resetごとに電源ボタンをおしてつながなければならない）

---

## 各ファイル詳細プログラム説明
### Mechanum_Cross_CAN
- **main.cpp**　Mainの関数　先にCANで送るコマンドを処理し、次に十字キー入力を変数に変換、そして足回りの動作実行。
変数に一度置き換えているのは、前後の駆動を別のマイコンでやっていた時代の名残だ。しかしわかりやすいので残した。
- **tuushin.cpp**　CAN通信用の関数。送信用の設定が入っている　あえて初期の変数を5にしたのは、送れていない時の0と区別するため
- **tuushin.h**　「tuushin.cpp」に対応したヘッダファイル
- **auto.cpp**　自動運転用。2秒左に行き１秒前へのプログラム。なんだが、これは暴走してしまう可能性が高い
なぜなら、ちょっとだけ動かすときと、続けて動かす場合では摩擦や回転数などの振れ幅も違うからである。
PIDができるんだったら、これがありになるのだが、、。
- **auto.h**「tuushin.cpp」に対応したヘッダファイル
- **PS4cross.cpp**　十字キーに対応した出力。
speed[4]に１入力分の値が入る。これはフィードフォワード制御による値だ（わけ合って前後が入れ替わったのでマイナスの値をとっている。）
電圧かけて、どれくらいの速度がでるかをエンコーダを使ってはかり、そこから値を割り出す形である。
- **PS4cross.h**　「tuushin.cpp」に対応したヘッダファイル
- **moter.cpp**　モータのピンと方向制御を規定しているファイルである。
- **moter.h**　「tuushin.cpp」に対応したヘッダファイル
- **Jidou_unten.cpp** 没ファイルなので気にしないでください

### Toutek_Honbanyou
- **main.cpp**　Mainの関数　CANの割り込みを行うにあたり、Roop付きの判定関数onReceiveはMain関数での定義となった
ピン設定して、CAN初期化して、実行。　2入力一セットのものは、それぞれ判定変数つけてるよ。ボタンを押す時間も考慮しDelayを入れている。
- **tuushin.cpp**　CAN通信用の関数。受信用の設定が入っている　receivePacketすると反応するようにした。また、向こうのプログラム「Mechanum_Cross_CAN」で通信のきっかけがこないと向こうから通信こないよ。
- **tuushin.h**　「tuushin.cpp」に対応したヘッダファイル
- **gyoukaku.h** 仰角系は全てここに入っている。(これだけヘッダファイルのみの運用）
- 仰角の初期値はこちらにもある(int currentAngle)のでお忘れなく！
- constrain関数で仰角の範囲を制限しているよ　（currentAngle = constrain(currentAngle, -75, 75);　－７５度から７５度まで
- movegyoukakuServoBy(int delta)は、delta分だけずらす関数。（movegyoukakuServoTo(int delta)は結局使用しなかったが、deltaに仰角を合わせる関数の予定で作った）
- **PWM.cpp**　電圧からでいゆーてぃサイクルを計算する関数が入っています。
- **PWM.h**「PWM.cpp」に対応したヘッダファイル
- **souten.cpp**　装填のことが入っている
-（引いて、もう一度コマンドが入ると戻す　引く⇒戻すを、コマンドで行う）（2コマンドで１セット）
Souten_Motor_Speedで装填速度（小さいほど早い）、Souten_Motor_initialAngleで初期角度、Souten_Motor_targetAngleで目標角度設定ができるぞ。
Souten_Modoshiは、1コマンドで連続してた時は、間のDelayの役回りだったが、今となってはただのDelay。
- **souten.h** 「souten.cpp」に対応したヘッダファイル
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

