#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QObject>
#include <QtCore>
#include <QMutex>
#include <QMutexLocker>
#include <QThread>
#include <QCoreApplication>
#include <QSocketNotifier>
#include <QTime>

#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <math.h>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/poll.h>
#include <stdio.h>
#include <queue>

#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <chrono>

#define DEVICE_ARDU0 "/dev/ttyACM0"
#define DEVICE_ARDU1 "/dev/ttyACM1"

#define BUFF_SIZE 3000

extern std::string expName;
extern int serialConnectOn;

class serialThread : public QObject
{
  Q_OBJECT
public:
  serialThread(QMutex* mu, QObject *parent = 0):QObject(parent){
    mutex = mu;
    std::cout<<"Serial thread made!"<<std::endl;
  }

  int discard_ind = 0;

  char shared_data_recv[BUFF_SIZE]={'\0'};
  int shared_fsr=0;
  int shared_time=0;
  int shared_signalOnOff=0;
  int shared_data_len=0;
  int shared_updated=0;
  int shared_update_count=0;
  int shared_frequency=0;
  std::vector<int> shared_fsr_vec;
  std::vector<int> shared_time_vec;
  std::vector<int> shared_signal_vec;
  std::vector<int> shared_frequency_vec;
  int shared_seq_num=0;

  void serial_connect();
  void serial_getData();
  void serial_analyzer();
  int decode(char in);
  void saveData();

signals:
  void finished();

private:
  QMutex* mutex;
  QTime mytime;

  // for serial termios
  int fd;
  struct termios newtio;

  // for serial polling
  int poll_state;
  struct pollfd poll_events;

  // other purposes
  int sequence_num=1;
  int prevent_mult_save = 1;
  std::queue<char> dataQueue;
  QSocketNotifier *notRsRead;

public slots:
  void run();
};

#endif // SERIALTHREAD_H
