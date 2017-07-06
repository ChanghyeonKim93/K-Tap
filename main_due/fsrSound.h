#ifndef FSRSOUND_H
#define FSRSOUND_H
#include "Arduino.h"
#include <Wire.h>

class fsrSound
{
 
  public:
    int signOn=1;
    char dataArr7[7]={'0','0','0','0','0','0','0'};
    char dataArr2[3]={'0','0','0'};
    char dataArr3[3]={'0','0','0'};
    
    fsrSound();
    ~fsrSound();
    void getTime();
    void getFsr(int fsrOrButton);
    void getFreq(int freq);
    
    void playTone(int freq);
    void sendData();

    void dotriaconta_7(unsigned long input);
    void dotriaconta_2(int input);
    void dotriaconta_3(int freq);
       
  private:
    unsigned long time_now;
    unsigned short fsr_data_now;
    int fsrPin = A0;
    int buttonPin = 10;
    int tonePin = 3;
    int ledPin = 11;
    char dataArrList[32] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
    char dataArrSend[15] = {'0'};
    
};

#endif
