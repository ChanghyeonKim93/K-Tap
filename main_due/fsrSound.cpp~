#include "Arduino.h"
#include "fsrSound.h"

fsrSound::fsrSound() { // constructor

  pinMode(fsrPin, INPUT); // for FSR
  pinMode(tonePin, OUTPUT); // for tone generation
}
fsrSound::~fsrSound() { // destructor

}

void fsrSound::getTime() {
  time_now = micros();
  dotriaconta_7(time_now);
}
void fsrSound::getFsr(int fsrOrButton) {

  if(fsrOrButton==0)  fsr_data_now = digitalRead(buttonPin)*1000;
  else fsr_data_now = analogRead(fsrPin);
  //Serial.println(fsr_data_now);
  dotriaconta_2((int)fsr_data_now);
}

void fsrSound::getFreq(int freq) {
  dotriaconta_3(freq);
}

void fsrSound::playTone(int freq) {
  //tone(tonePin,freq,2); //
}

void fsrSound::sendData() {
  dataArrSend[0] = 'S'; // start parity

  dataArrSend[1] = dataArr7[0]; // time
  dataArrSend[2] = dataArr7[1]; // time
  dataArrSend[3] = dataArr7[2]; // time
  dataArrSend[4] = dataArr7[3]; // time
  dataArrSend[5] = dataArr7[4]; // time
  dataArrSend[6] = dataArr7[5]; // time
  dataArrSend[7] = dataArr7[6]; // time

  dataArrSend[8] = dataArr2[0]; // low  : fsr
  dataArrSend[9] = dataArr2[1]; // high : fsr
  dataArrSend[10] = dataArr2[2]; // TT

  dataArrSend[11] = dataArrList[signOn]; // sign On off

  dataArrSend[12] = dataArr3[0]; // freq data send
  dataArrSend[13] = dataArr3[1];
  dataArrSend[14] = dataArr3[2];

  dataArrSend[15] = 'E'; // end parity

  //dataArrSend[16] = '\n';
  Serial.write(dataArrSend,16);
  Serial.flush();
  delayMicroseconds(100);
}


void fsrSound::dotriaconta_7(unsigned long input) {

  int ind = 0;
  int Q, R;
  int num = (int)input;
  for (int k = 0; k < 7; k++) {
        dataArr7[k] = '0';
      }
  while (1) {
    Q = num / 32;
    R = num % 32;
    if (Q == 0) {
      dataArr7[ind] = dataArrList[R];
      break;
    }
    dataArr7[ind] = dataArrList[R];
    ind++;
    num = Q;
  }
}
void fsrSound::dotriaconta_2(int input) {

  int Q, R, ind = 0;
  int num = (int)input;
   for (int k = 0; k < 3; k++) {
        dataArr2[k] = '0';
      }
  while (1) {
    Q = num / 32;
    R = num % 32;
    if (Q == 0) {
      dataArr2[ind] = dataArrList[R];
      break;
    }
    dataArr2[ind] = dataArrList[R];
    ind++;
    num = Q;
  }
}

void fsrSound::dotriaconta_3(int freq){
  
  int Q, R, ind = 0;
  int num = (int)freq;
  for (int k = 0; k < 3; k++) {
        dataArr3[k] = '0';
      }
  while (1) {
    Q = num / 32;
    R = num % 32;
    if (Q == 0) {
      dataArr3[ind] = dataArrList[R];  
      break;
    }
    dataArr3[ind] = dataArrList[R];
    ind++;
    num = Q;
  }
}

