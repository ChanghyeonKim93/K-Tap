void setup() {
  // put your setup code here, to run once:
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(A0,INPUT);
analogReadResolution(12);
Serial.begin(115200);
}
  unsigned long ref_time =0,curr_time;
  char temp[16]={'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'};
  bool mysign=true;
  int temp_=0;

void loop() {
  // put your main code here, to run repeatedly:
  ref_time=millis();
  digitalWrite(4,mysign);
  
  while(1){   
    curr_time=millis();
    if(curr_time-ref_time>=3){
      ref_time=curr_time;
      mysign=!mysign;
    }
    digitalWrite(4,mysign);
    temp_=analogRead(A0); 
    if(temp_>4000){
      digitalWrite(3,1);
    }
    else if(temp_<=100){
      digitalWrite(3,0);

    }
  }

}
