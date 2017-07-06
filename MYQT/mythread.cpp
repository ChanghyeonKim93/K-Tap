#include "mythread.h"

#include <QtCore>
#include <QDebug>
#include <QMutexLocker>
#include <iostream>
#include <fstream>
#include <sstream>

void mythread::saveData(){
  std::cout<<"seq num "<<sequence_num<<" : save data..."<<std::endl;
  std::fstream dataStream;
  std::stringstream myFileNameStream;
  myFileNameStream<<"../fsrExpData/"<<expName<<"_exp_"<<sequence_num<<"_dataLog.txt";
  std::string myFileNameString=myFileNameStream.str();

  dataStream.open(myFileNameString.c_str(),std::fstream::out);
  std::cout<<"vector size : "<<shared_time_vec.size()<<std::endl;
  if(dataStream.is_open()){
      dataStream<<"time[us],volt(fsr)[v],Stimul,frequency[Hz]"<<std::endl;
      for(int k=0;k<shared_time_vec.size();++k){
          dataStream<< shared_time_vec[k]<< ',';
          dataStream<< shared_fsr_vec[k]<< ',';
          dataStream<< shared_signal_vec[k]<<',';
          dataStream<< shared_frequency_vec[k]<<std::endl;
        }
    }
  dataStream.close();
  std::cout<<"save done!"<<std::endl;
}

int mythread::decode(char in){
  if(in=='0') return 0;
  else if(in=='1') return 1;
  else if(in=='2') return 2;
  else if(in=='3') return 3;
  else if(in=='4') return 4;
  else if(in=='5') return 5;
  else if(in=='6') return 6;
  else if(in=='7') return 7;
  else if(in=='8') return 8;
  else if(in=='9') return 9;
  else if(in=='a') return 10;
  else if(in=='b') return 11;
  else if(in=='c') return 13;
  else if(in=='d') return 14;
  else if(in=='e') return 15;
  else if(in=='f') return 16;
  else if(in=='g') return 17;
  else if(in=='h') return 18;
  else if(in=='i') return 19;
  else if(in=='j') return 20;
  else if(in=='k') return 21;
  else if(in=='l') return 22;
  else if(in=='m') return 23;
  else if(in=='n') return 24;
  else if(in=='o') return 25;
  else if(in=='p') return 26;
  else if(in=='q') return 27;
  else if(in=='r') return 28;
  else if(in=='s') return 29;
  else if(in=='t') return 30;
  else if(in=='u') return 31;
  else if(in=='v') return 32;

}
void mythread::run_org(){
  int th_count=0;
  while(1){
      //qDebug()<<"Thread running! mytime :  "<<(*mytime);
      if(shared_data_len>0 && shared_updated==1){
          // mutex->lock();
          for(int k=0;k<shared_data_len;k++){
              myQueue.push(shared_data_recv[k]);
            }
          std::cout<<"queue length : "<< myQueue.size()<<", port count : "<<shared_update_count<<", thread count : "<<th_count<<std::endl;
          int len=3;
          if(myQueue.size()>700) len = 16;
          for(int k=0;k<len;k++){
              while(1){
                  if(myQueue.front()=='S'){
                      myQueue.pop();

                      char temp[10];
                      std::cout<<"found!!"<<std::endl;
                      temp[0] = myQueue.front(); myQueue.pop();
                      temp[1] = myQueue.front(); myQueue.pop();
                      temp[2] = myQueue.front(); myQueue.pop();
                      temp[3] = myQueue.front(); myQueue.pop();
                      temp[4] = myQueue.front(); myQueue.pop();
                      temp[5] = myQueue.front(); myQueue.pop();
                      temp[6] = myQueue.front(); myQueue.pop();
                      temp[7] = myQueue.front(); myQueue.pop();
                      temp[8] = myQueue.front(); myQueue.pop();
                      temp[9] = myQueue.front(); myQueue.pop();
                      if(myQueue.front()=='E'){
                          myQueue.pop();
                          shared_fsr = decode(temp[7]) + decode(temp[8])*32;
                          shared_time = decode(temp[0]) + decode(temp[1])*32 +decode(temp[2])*32*32 + decode(temp[3])*32*32*32 + decode(temp[1])*32+decode(temp[1])*32+decode(temp[1])*32+decode(temp[1])*32;
                          shared_signalOnOff = decode(temp[9]);

                          shared_time_vec.push_back(shared_time);
                          shared_fsr_vec.push_back(shared_fsr);
                          shared_signal_vec.push_back(shared_signalOnOff);
                        }
                      else{
                          myQueue.pop();
                          break;
                        }
                      break;
                    }
                  else{
                      myQueue.pop();
                    }
                }

            }
          shared_updated=0;
          th_count++;
          // mutex->unlock();
        }
    }
}

void mythread::run(){
  int th_count=0;
  while(1){
      if(shared_data_len>0 && shared_updated == 1){
          for(int k=0;k<shared_data_len;k++){
              myQueue.push(shared_data_recv[k]);
            }
         std::cout<<"queue data :"<<myQueue.front()<<", queue length : "<< myQueue.size()<<", shared_update_count : "<<shared_update_count<<", thread count : "<<th_count<<", seq num : "<< sequence_num <<std::endl;
          int len=3;
          if(myQueue.size()>100){
              if(myQueue.size()>500) len=20;
              for(int m=0;m<len;m++){
                  if(myQueue.front()=='S'){
                      myQueue.pop();
                      char temp[14];
                      //std::cout<<"S : found!!"<<std::endl;
                      temp[0] = myQueue.front(); myQueue.pop();
                      temp[1] = myQueue.front(); myQueue.pop();
                      temp[2] = myQueue.front(); myQueue.pop();
                      temp[3] = myQueue.front(); myQueue.pop();
                      temp[4] = myQueue.front(); myQueue.pop();
                      temp[5] = myQueue.front(); myQueue.pop();
                      temp[6] = myQueue.front(); myQueue.pop();

                      temp[7] = myQueue.front(); myQueue.pop();
                      temp[8] = myQueue.front(); myQueue.pop();
                      temp[9] = myQueue.front(); myQueue.pop();


                      temp[10] = myQueue.front(); myQueue.pop();

                      temp[11] = myQueue.front(); myQueue.pop();
                      temp[12] = myQueue.front(); myQueue.pop();
                      temp[13] = myQueue.front(); myQueue.pop();

                      if(myQueue.front()=='E'){
                          myQueue.pop();
                          shared_fsr = decode(temp[7]) + decode(temp[8])*32 + decode(temp[9])*32*32;
                          shared_time = decode(temp[0]) + decode(temp[1])*32 +decode(temp[2])*32*32 + decode(temp[3])*32*32*32 + decode(temp[4])*32*32*32*32+decode(temp[5])*32*32*32*32*32+decode(temp[6])*32*32*32*32*32*32+decode(temp[7])*32*32*32*32*32*32*32;
                          shared_signalOnOff = decode(temp[10]);
                          shared_frequency = decode(temp[11]) + decode(temp[12])*32 + decode(temp[13])*32*32;

                          shared_time_vec.push_back(shared_time);
                          shared_fsr_vec.push_back(shared_fsr);
                          shared_signal_vec.push_back(shared_signalOnOff);
                          shared_frequency_vec.push_back(shared_frequency);
                        }
                      else{
                          myQueue.pop();
                          break;
                        }
                    }

                  else if(myQueue.front()=='Y' ){//&& shared_time_vec.size()>=1){ // (from arduino) if button is not pushed, 'N' is sended.
                      for(int k=1;k<10;k++){
                          std::cout<<"in seq change"<<std::endl;
                        }
                      myQueue.pop();
                      if(sequence_num>=0){
                          saveData();
                        }

                      sequence_num++;
                      shared_seq_num=sequence_num;

                      // initialize all containers.
                      while(!myQueue.empty()){
                          myQueue.pop(); // clear queue
                        }
                      for(int k =0;k<3;k++)  std::cout<<"Queue size : "<<myQueue.size()<<std::endl;

                      myQueue.push('C');
                      shared_fsr=0;
                      shared_time=0;
                      shared_signalOnOff=0;
                      shared_frequency=0;
                      shared_fsr_vec.clear(); // clear dataSave vector
                      shared_time_vec.clear();
                      shared_signal_vec.clear();
                      shared_frequency_vec.clear();

                      break;
                    }
                  else if(myQueue.front()=='N'){
                      shared_fsr=0;
                      shared_time=0;
                      shared_signalOnOff=0;
                      shared_frequency=0;
                      while(!myQueue.empty()){
                          if(myQueue.front()=='Y'){
                              break;
                            }
                          myQueue.pop();
                        }
                      myQueue.push('C');
                      break;
                    }
                  else{ // (from arduino) maybe 'N'...
                          myQueue.pop();
                      break;
                    }
                }


            }
          shared_updated=0;
          th_count++;
        }



    }
}
