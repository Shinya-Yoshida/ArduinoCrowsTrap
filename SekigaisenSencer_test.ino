void setup() {
//  Serial.begin(9600);
  pinMode(13, OUTPUT);
//  while (!Serial) {}  
}

void loop() {
  int l = analogRead(A0);
  int ll = l;
  
  ll = 12288/ll;

  if(l > 250) {
      digitalWrite(13, HIGH);
  } else {
      digitalWrite(13, LOW);
  }

  Serial.print(l);
  Serial.print(" ");
  Serial.println(ll);
  
  delay(500);
}
