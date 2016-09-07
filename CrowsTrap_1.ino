#include <Servo.h>
Servo myservo;

int SERVO_VAL_ON;       // 糸を緩める（リールのロックを外す）
int SERVO_VAL_OFF;      // 糸を固定（リールをロック状態（初期値））
int CNV_IR_TO_DISTANCE; // 赤外線センサー値を距離に変換する定数
int ang_temp;
int ir_val;             // 赤外線センサーの読み取り値
int distance;           // 距離に変換後の値

void setup() {
//  Serial.begin(9600);
  while (!Serial) {}
  SERVO_VAL_ON = 45;
  SERVO_VAL_OFF = 100;
  CNV_IR_TO_DISTANCE = 12288;
  myservo.attach(9); //デジタル9番ピンをサーボの角度命令出力ピンとして設定
}

void loop() {
  ir_val = analogRead(A0);
  distance = ir_val;
  
  distance = 12288/distance;

  if(ir_val > 250) {
      servo_cnt(SERVO_VAL_ON);
  } else {
      servo_cnt(SERVO_VAL_OFF);
  }

//  Serial.print(ir_val);
//  Serial.print(" ");
//  Serial.println(distance);
  
  delay(500);
}

int servo_cnt( int ang ){

  // 同じ値が設定されていたら何もしない
  if( ang != ang_temp ){
    ang_temp = ang;
    if( myservo.attached() == false )
      myservo.attach(9); //デジタル9番ピンをサーボの角度命令出力ピンとして設定
    myservo.write(ang); //サーボを動かす
//    Serial.println(ang);
    delay(1000);
    myservo.detach();
  }

}

