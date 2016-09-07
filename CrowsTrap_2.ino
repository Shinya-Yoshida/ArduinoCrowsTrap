//********************************************************************
//*　超音波距離センサーを使用したカラス捕獲プログラム
//********************************************************************
#include <Servo.h>
Servo myservo;

#define ECHO_PIN 7        // 距離センサーEcho Pin    (超音波入力用の信号を受信)
#define TRIG_PIN 6        // 距離センサーTrigger Pin (超音波出力用の信号を送信)
#define SERV_PIN 9        // サーボモータPin
#define SERVO_VAL_ON 45   // 糸を緩める（リールのロックを外す）
#define SERVO_VAL_OFF 100 // 糸を固定（リールをロック状態（初期値））
int servo_val;            // 
 
double Duration = 0; //受信した間隔
double Distance = 0; //距離

void setup() {
//  Serial.begin( 9600 );
  pinMode( ECHO_PIN, INPUT );
  pinMode( TRIG_PIN, OUTPUT );
  myservo.attach( SERV_PIN );  //サーボの角度命令出力ピンとして設定  
  servo_val = SERVO_VAL_OFF;
}
void loop() {
  digitalWrite( TRIG_PIN, LOW ); 
  delayMicroseconds(2); 
  digitalWrite( TRIG_PIN, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( TRIG_PIN, LOW );
  Duration = pulseIn( ECHO_PIN, HIGH ); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance = Duration*340*100/1000000; // 音速を340m/sに設定
//    Serial.print( "Respons:" );
//    Serial.print( Duration );
//    Serial.print( " Distance:" );
//    Serial.print( Distance );
//    Serial.println( " cm" );
  }

  // 7～30cmの時にロック解除
  if( ( Distance >= 7.0 ) && ( Distance <= 30.0 ) ) {
      servo_cnt(SERVO_VAL_ON);
  } else {
      servo_cnt(SERVO_VAL_OFF);
  }
  delay( 500 );
}

// ==============================
// = サーボ制御処理
// ==============================
int servo_cnt( int ang ){
  static int ang_temp;  
  
  // 同じ値が設定されていたら何もしない
  if( ang != ang_temp ){
    ang_temp = ang;
    if( myservo.attached() == false )
      myservo.attach( SERV_PIN );   //デジタル9番ピンをサーボの角度命令出力ピンとして設定
    myservo.write( ang );           //サーボを動かす
//    Serial.println( ang );
    delay( 1000 );
    myservo.detach();
  }
}

