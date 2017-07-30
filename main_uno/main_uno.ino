// FOR ARDUINO UNO

#include "fsrSound.h"
#include <Wire.h>

// initial settings
#define expArrSz 32 // The number of stimulations in one trial. Every trial should have the same number of stimulations.
#define expNum 2 // The number of trials. 
const int sign_Freq[][expArrSz]     = {{600,600,600,600,600,600,600,600,300,300,300,300,300,300,300,300,600,600,600,600,600,600,600,600,300,300,300,300,300,300,300,300},
                                       {300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300,300}};// unit : [ms] 
                                   
const int sign_Duration[]           = {4,300}; // unit : [ms], 
                                   
const int sign_Interval[][expArrSz] = {{8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
                                       {500,500,500,500,500,500,500,500,200,200,200,200,200,200,200,200,500,500,500,500,500,500,500,500,200,200,200,200,200,200,200,200}}; // unit : [ms]

//do not change from here

#define audioPin 4
#define LEDPin   8
#define buttonPin 2 // for trial change. (digitalInput pin)

int k=0;
unsigned long t_now;
unsigned long t_ref ; 
float t_gap;
int seq_num = -1;
int buttonOn=0;
int doLoop = 0;

fsrSound *myfsrsound; // create a class object

void setup() {
  Serial.begin(460800); // serial communication with PC by 500000 baudrate
  myfsrsound = new fsrSound(); // fsr with pulldown resistor 10k Ohm
  pinMode(audioPin,OUTPUT); // for AUDIO output 
  pinMode(LEDPin,OUTPUT);// for LED output
  pinMode(buttonPin,INPUT);
  t_ref=micros(); // initial timer
}

void loop() {
  if(doLoop==1){
    for(int k = 0;k<expArrSz;k++){
      int steps=0;
      while(steps==0){ // 
        digitalWrite(3,HIGH);
        t_now = micros();
        t_gap = (float)(t_now - t_ref)/1000.0;
        //Serial.println(t_gap); // for debug
        if(t_gap < sign_Duration[seq_num] && myfsrsound->signOn ==1){
          myfsrsound->playTone(sign_Freq[seq_num][k]); // speaker ON
          digitalWrite(LEDPin,HIGH); // LED ON
        }

        else if(t_gap >= sign_Duration[seq_num] && myfsrsound->signOn==1){
          myfsrsound->signOn=0;
          //playTone(0);// 0 Hz, No sound,
          t_ref = t_now; 
          steps=1;
        }
        myfsrsound->getFsr(1);
        myfsrsound->getTime();
        myfsrsound->sendData();
        digitalWrite(3,LOW);

      }
      while(steps == 1){
        t_now = micros();
        t_gap = (float)(t_now - t_ref)/1000.0;
        // Serial.println(t_gap); // for debug
        if(t_gap <sign_Interval[seq_num][k] && myfsrsound->signOn == 0){
          //playTone(0);// speaker OFF
          digitalWrite(LEDPin,LOW); // LED OFF
        }
        else if(t_gap>=sign_Interval[seq_num][k] && myfsrsound->signOn == 0){
          myfsrsound->signOn=1;
          t_ref = t_now;
          steps=0;
        }
        myfsrsound->getFsr(1);
        myfsrsound->getTime();
        myfsrsound->sendData();

      }
    }
    // finish alarm
    delay(1000);
   // tone(3,523,100);// C, 1000 [ms]
    delay(100);
    //tone(3,587,100);// D, 1000 [ms]
    delay(100);
    //tone(3,659,100);// E, 1000 [ms]
    delay(100);
    //tone(3,698,100);// F, 1000 [ms]
    delay(100);
    //tone(3,783,100);// G, 1000 [ms]

    doLoop=0; // A trial is done. click the "BUTTON" if you want to do next trial.
  }
  
  if(doLoop==0){ // below part is only for the Serial communication with PC.
    buttonOn=digitalRead(buttonPin); // Trial change signal
    Serial.print('N');
    if(buttonOn==1){
      for(int k=0;k<150;k++){
        Serial.print('Y');
      }
      delay(2000);

      doLoop=1;
      seq_num++;
      if(seq_num>expNum-1){
        while(1){
            Serial.print("UUUUUUUUUUUUUUUUUUU"); // All experiments is ended ! ( Sign to the PC.)
            delay(300);
            //tone(3,523,300);// C, 300 [ms]
            delay(300);
            //tone(3,587,300);// D, 300 [ms]
            delay(300);
            //tone(3,659,300);// E, 300 [ms]
            delay(300);
            //tone(3,698,300);// F, 300 [ms]
            delay(300);
            //tone(3,783,300);// G, 300 [ms]

          }
        
        }
    }
  }
}
