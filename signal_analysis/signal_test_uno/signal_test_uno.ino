void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(460800);
}

void loop() {
  // put your main code here, to run repeatedly:
  char _temp[16]={'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'};
  while (1) {
    digitalWrite(3, HIGH);
digitalRead(2);
digitalWrite(3, LOW);
  }
}
