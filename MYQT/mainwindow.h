#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serialThread.h"

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

#include <QMainWindow>
#include <QSocketNotifier>
#include <QObject>
#include <QWidget>
#include <QtGui>

#include <QThread>
#include <QMutex>
#include <QtCore>
#include <QDebug>
#include <QMutexLocker>
#include <QTime>

#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <chrono>

//define baud rate
#define BUFF_SIZE 3000
extern std::string expName;
extern int serialConnectOn;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QMutex* mu,serialThread* myserialThread,QWidget *parent = 0);
  virtual ~MainWindow();
  void endProgram();

private slots:
  void switchbutton_click();
  void on_connectButton_clicked();
  void setRealtimePlot();
  void slider_triggered(int input);

private:
  int programOnOff_status=-1;
  double denom=1000000.0;
  double rightLim=5.0;

  QMutex* mutex;
  serialThread* thisSerialThread;
  Ui::MainWindow *ui;

  QString experimentalName;
  QTimer dataTimer;

  QTime mytime;

};

#endif // MAINWINDOW_H
