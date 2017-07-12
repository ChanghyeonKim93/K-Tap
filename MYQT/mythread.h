#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtCore>
#include <QMutex>
#include <QMutexLocker>
#include <queue>
#include <QThread>
#include <QCoreApplication>
#include <iostream>
extern char shared_data_recv[1000];
extern int shared_fsr;
extern int shared_time;
extern int shared_signalOnOff;
extern int shared_data_len;
extern int shared_updated;
extern int shared_update_count;
extern int shared_frequency;
extern std::vector<int> shared_fsr_vec;
extern std::vector<int> shared_time_vec;
extern std::vector<int> shared_signal_vec;
extern std::vector<int> shared_frequency_vec;
extern std::string expName;
extern int shared_seq_num;

class mythread : public QObject
{
  Q_OBJECT

public:
  int discard_ind = 0;
  mythread(QMutex* mu, QObject *parent=0):QObject(parent){
    mutex = mu;
    std::cout<<"thread made"<<std::endl;

  }
  void saveData();
  void run_org();
  int tt=0;
  int decode(char in);

signals:
  void finished();

private:
  QMutex* mutex;
  std::queue<char> myQueue;
  int sequence_num=0;

public slots:
  void run();

};



#endif // MYTHREAD_H
