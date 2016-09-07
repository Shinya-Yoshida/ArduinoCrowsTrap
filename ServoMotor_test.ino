#include <Servo.h>
Servo myservo;
int val; //サーボの角度を格納するための変数
int temp_val;
int cnt_val;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {}  
  myservo.attach(9); //デジタル9番ピンをサーボの角度命令出力ピンとして設定
  val = 45;
  temp_val = 1;
  cnt_val = 0;
}
void loop()
{
  cnt_val++;
  if( cnt_val == 1000 ) {
    val = 100;
  }
  else if( cnt_val == 2000 ) {
    val = 45;
    cnt_val = 0;
  }
  
  if( val != temp_val ) {
    temp_val = val;
    if( myservo.attached() == false )
      myservo.attach(9); //デジタル9番ピンをサーボの角度命令出力ピンとして設定
    myservo.write(val); //サーボを動かす
    Serial.println(val);
    delay(1000);
    myservo.detach();
  }

  delay(10);

}
