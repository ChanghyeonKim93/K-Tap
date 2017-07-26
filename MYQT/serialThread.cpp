#include "serialThread.h"

void serialThread::serial_connect(){

    fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY | O_NDELAY );
    poll_events.fd=fd; // for polling
    poll_events.events = POLLIN;
    poll_events.revents = 0;

    cfsetispeed(&newtio, B460800);    // set baud rates
    newtio.c_cflag = B460800 | CS8 | CREAD | CLOCAL;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    tcsetattr(fd, TCSANOW, &newtio); // apply the settings to the port

    notRsRead = new QSocketNotifier(fd,QSocketNotifier::Read,this);
    connect(notRsRead,SIGNAL(activated(int)),this,SLOT(setEvent()));
    mytime.start();
}

void serialThread::serial_getData(){

   // mutex->lock();
  int nElapsed ;
  poll_state = poll((struct pollfd*)&poll_events,1,0);
  if(poll_state>0){
      if(poll_events.revents & POLLIN){//
          int sizeRead = read(fd,&shared_data_recv,BUFF_SIZE);
          if(sizeRead>0)  {
              nElapsed=mytime.elapsed(); // for debug and estimate the execution time.
              qDebug() <<"Elapsed Serial Thread recv time [ms] : "<<nElapsed<<",data length:"<<sizeRead<<", queue data :"<<dataQueue.front()<<", queue length : "<< dataQueue.size()<<", shared_update_count : "<<shared_update_count<<", seq num : "<< sequence_num <<" , discard_ind : "<<discard_ind;
              //std::cout<<"queue data :"<<dataQueue.front()<<", queue length : "<< dataQueue.size()<<", shared_update_count : "<<shared_update_count<<", seq num : "<< sequence_num <<" , discard_ind : "<<discard_ind<<std::endl;

              shared_update_count++;
              for(int k=0;k<sizeRead;k++){
                  dataQueue.push(shared_data_recv[k]);
                }
              sizeRead=0;
            }
            shared_data_recv[sizeRead] = '\0';

        }
    }
}

void serialThread::saveData(){
  std::cout<<"seq num "<<sequence_num<<" : save data..."<<std::endl;
  std::fstream dataStream;
  std::stringstream myFileNameStream;
  myFileNameStream<<"../fsrExpData/"<<expName<<"_exp_"<<sequence_num<<"_dataLog.txt";
  std::string myFileNameString=myFileNameStream.str();

  dataStream.open(myFileNameString.c_str(),std::fstream::out);
  std::cout<<"vector size : "<<shared_time_vec.size()<<std::endl;
  if(dataStream.is_open()){
      dataStream<<"time[us],volt(fsr)[v],signal,signal frequency[Hz]"<<std::endl;
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

int serialThread::decode(char in){
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
  else if(in=='c') return 12;
  else if(in=='d') return 13;
  else if(in=='e') return 14;
  else if(in=='f') return 15;
  else if(in=='g') return 16;
  else if(in=='h') return 17;
  else if(in=='i') return 18;
  else if(in=='j') return 19;
  else if(in=='k') return 20;
  else if(in=='l') return 21;
  else if(in=='m') return 22;
  else if(in=='n') return 23;
  else if(in=='o') return 24;
  else if(in=='p') return 25;
  else if(in=='q') return 26;
  else if(in=='r') return 27;
  else if(in=='s') return 28;
  else if(in=='t') return 29;
  else if(in=='u') return 30;
  else if(in=='v') return 31;
}

void serialThread::serial_analyzer(){

  int len=5;
  if(dataQueue.size()>150){
      if(dataQueue.size()>700) len=16;
      for(int m=0;m<len;m++){
          if(dataQueue.front()=='S'){
              dataQueue.pop();
              char temp[14];
              //std::cout<<"S : found!!"<<std::endl;
              temp[0] = dataQueue.front(); dataQueue.pop();
              temp[1] = dataQueue.front(); dataQueue.pop();
              temp[2] = dataQueue.front(); dataQueue.pop();
              temp[3] = dataQueue.front(); dataQueue.pop();
              temp[4] = dataQueue.front(); dataQueue.pop();
              temp[5] = dataQueue.front(); dataQueue.pop();
              temp[6] = dataQueue.front(); dataQueue.pop();

              temp[7] = dataQueue.front(); dataQueue.pop();
              temp[8] = dataQueue.front(); dataQueue.pop();
              temp[9] = dataQueue.front(); dataQueue.pop();


              temp[10] = dataQueue.front(); dataQueue.pop();

              temp[11] = dataQueue.front(); dataQueue.pop();
              temp[12] = dataQueue.front(); dataQueue.pop();
              temp[13] = dataQueue.front(); dataQueue.pop();

              if(dataQueue.front()=='E'){
                  dataQueue.pop();
                  shared_fsr = decode(temp[7]) + decode(temp[8])*32 + decode(temp[9])*32*32;
                  shared_time = decode(temp[0]) + decode(temp[1])*32 +decode(temp[2])*32*32 + decode(temp[3])*32*32*32 + decode(temp[4])*32*32*32*32 + decode(temp[5])*32*32*32*32*32 + decode(temp[6])*32*32*32*32*32*32;

                  shared_signalOnOff = decode(temp[10]);

                  shared_frequency = decode(temp[11]) + decode(temp[12])*32 + decode(temp[13])*32*32;

                  shared_time_vec.push_back(shared_time);
                  shared_fsr_vec.push_back(shared_fsr);
                  shared_signal_vec.push_back(shared_signalOnOff);
                  shared_frequency_vec.push_back(shared_frequency);
                }
              else{
                  dataQueue.pop();
                  break;
                }
            }

          else if(dataQueue.front()=='Y' ){//&& shared_time_vec.size()>=1){ // (from arduino) if button is not pushed, 'N' is sended.
              for(int k=1;k<3;k++){
                  std::cout<<"in seq change"<<std::endl;
                }
              dataQueue.pop();
              if(sequence_num>=0){
                  saveData();
                }

              sequence_num++;
              shared_seq_num=sequence_num;

              // initialize all containers.
              while(!dataQueue.empty()){
                  dataQueue.pop(); // clear queue
                }
              for(int k =0;k<3;k++)  std::cout<<"Queue size : "<<dataQueue.size()<<std::endl;

              dataQueue.push('C');
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
          else if(dataQueue.front()=='N'){
              shared_fsr=0;
              shared_time=0;
              shared_signalOnOff=0;
              shared_frequency=0;
              while(!dataQueue.empty()){
                  if(dataQueue.front()=='Y'){
                      break;
                    }
                  dataQueue.pop();
                }
              dataQueue.push('C');
              break;
            }
          else{ // (from arduino) maybe 'N'...
                  dataQueue.pop();
                  discard_ind++;
            }
        }
    }
}

void serialThread::run(){
  int th_count = 0;
  // query serial connection
  while(1){
      th_count++;
      if(serialConnectOn==1){
          serial_connect();
          std::cout<<"Serial Connected Done!"<<std::endl;
          break;
        }
    }

  // query serial data consecutively.
  while(1){
      th_count++;
      serial_getData(); // data update if there is a new data.
      serial_analyzer();
    }
}
