void setup() {
  // put your setup code here, to run once:
pinMode(4,OUTPUT);
pinMode(A0,INPUT);
Serial.begin(230400*2);
}
int a=1;
void loop() {
  // put your main code here, to run repeatedly:
      digitalWrite(4,HIGH);
    Serial.print("S!)@(#*$&%*!E");
   //analogRead(A0);
      digitalWrite(4,LOW);

  /*if(a==1){
    digitalWrite(4,HIGH);
    a=0;
  }
  else{
    digitalWrite(4,LOW);
    a=1;
  }*/
}

// # digitalWrite delay
// 146.4 kHz ( 6.83 us)
// 159.4 kHz ( 6.274 us) 

// # analogRead delay
// uno 8.338kHz analogRead ( 119.90 us delay )
// due 97kHz analogRead    (  10.31 us delay )

// # serial.print delay ( 1 character ) 460800
// uno
// due 47.71 kHz  (20.89 us delay)


// # serial.print delay ( 2 character ) 460800
// uno
// due 23.89 kHz  (41.86 us delay)


// # serial.print delay ( 3 character ) 460800
// uno
// due 15.91 kHz  (62.84 us delay)


// # serial.print delay ( 3 character ) 230400
// uno
// due 7.956 kHz  (125.7 us delay)

// # serial. print delay (13 char) 460800
// uno 
// due 3.672 kHz ( 272.4 us)

// all loop 460800
// uno 1.39 kHz ( 719.6 us )
// due 3.978 kHz ( 251.4 us )

// all loop 230400
// uno 
// due 1.989 kHz (502.8 us)

// from tone to analogRead 460800
// uno 1.33 kHz (751.9 us)
// due 3.977 kHz (251.4 us)

// from tone to memory register (delay) 
// uno 577.6 us 
// due 25.43 us 
