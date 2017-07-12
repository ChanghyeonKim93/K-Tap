
#include "mainwindow.h"
#include "mythread.h"
#include <QApplication>
#include <QThread>

char shared_data_recv[1000];
int shared_fsr=0;
int shared_time=0;
int shared_signalOnOff=0;
int shared_data_len=0;
int shared_updated=0;
int shared_update_count=0;
int shared_seq_num=0;
int shared_frequency=0;
std::vector<int> shared_fsr_vec;
std::vector<int> shared_time_vec;
std::vector<int> shared_signal_vec;
std::vector<int> shared_frequency_vec;
std::string expName;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMutex mMutex;
    QThread thread1;
    MainWindow w(&mMutex);
    mythread threadworker(&mMutex);
    threadworker.moveToThread(&thread1);
    QObject::connect(&thread1, SIGNAL(started()), &threadworker, SLOT(run()));
    QObject::connect(&threadworker, SIGNAL(finished()), &thread1, SLOT(quit()));
    QObject::connect(&thread1, SIGNAL(finished()), &a, SLOT(quit()));

    w.show();
    thread1.start();

    return a.exec();
}
