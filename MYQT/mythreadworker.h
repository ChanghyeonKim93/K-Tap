#ifndef MYTHREADWORKER_H
#define MYTHREADWORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>

class mythreadworker : public QObject
{
  Q_OBJECT
public:
  mythreadworker(QObject *parent = 0): QObject(parent) {}

signals:
void finished();

public slots:


};

#endif // MYTHREADWORKER_H
