#ifndef THREADTEST_H
#define THREADTEST_H

#include <QThread>
#include <QMutexLocker>
#include <QDebug>
#include <QtCore>
#include <QMutex>

class threadtest : public QThread
{
private:
  void run();
  QMutex* mutex;

public:
  threadtest(QMutex* mu, int myNum, int* shardNum);
  int myNumber;
  int* num;


};

#endif // THREADTEST_H
