#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <chrono>

//define serial port
#define DEVICE00 "/dev/ttyS0"
#define DEVICE01 "/dev/ttyS1"
#define DEVICE02 "/dev/ttyS2"
#define DEVICE_USB0 "/dev/ttyUSB0"
#define DEVICE_USB1 "/dev/ttyUSB1"
#define DEVICE_ARDU0 "/dev/ttyACM0"
#define DEVICE_ARDU1 "/dev/ttyACM1"

//define baud rate
extern char shared_data_recv[1000];
extern int shared_fsr;
extern int shared_time;
extern int shared_signalOnOff;
extern int shared_frequency;
extern int shared_data_len;
extern int shared_updated;
extern int shared_update_count;
extern std::vector<int> shared_fsr_vec;
extern std::vector<int> shared_time_vec;
extern std::vector<int> shared_signal_vec;
extern std::vector<int> shared_frequency_vec;
extern std::string expName;
extern int shared_seq_num;

#define BUFF_SIZE 255

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QMutex* mu,QWidget *parent = 0);
  virtual ~MainWindow();
  void endProgram();
  char data_recv[BUFF_SIZE];

private slots:
  void switchbutton_click();
  void on_connectButton_clicked();
  void setEvent();
  void saveData();
  void setRealtimePlot();
  //void deserialize();
private:
  int onOff_status=-1;
  char buf_temp[BUFF_SIZE];
  int fd;

  QMutex* mutex;
  Ui::MainWindow *ui;
  QSocketNotifier *notRsRead;

  QString experimentalName;
  QTimer dataTimer;

};

#endif // MAINWINDOW_H
