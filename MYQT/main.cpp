#include "mainwindow.h"
#include "serialThread.h"
#include <QApplication>
#include <QThread>

std::string expName;
int serialConnectOn=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMutex mMutex;

    QThread thread1;
    serialThread mySerialThread(&mMutex);
    mySerialThread.moveToThread(&thread1);

    QObject::connect(&thread1, SIGNAL(started()), &mySerialThread, SLOT(run()));
    QObject::connect(&mySerialThread, SIGNAL(finished()), &thread1, SLOT(quit()));
    QObject::connect(&thread1, SIGNAL(finished()), &a, SLOT(quit()));

    MainWindow w(&mMutex,&mySerialThread);

    w.show();
    thread1.start();

    return a.exec();
}
