#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "LDatabase.h"

class Worker : public QObject
{
    Q_OBJECT

  public:
    explicit Worker(QObject *parent = 0);

  signals:
    // send event to worker thread
    void signal_newResponse(void * socket_desc, const QByteArray &in_data);

  public slots:
    void slot_newRequest(void * socket_desc, const QByteArray &in_data);

  private:
    LDatabase ldb;

    QByteArray * data;
    const void * client;

    //TODO make a class to use in LDatabase class as well
    QJsonDocument lunchRpc;
    QByteArray getRpcFile(const char * file_name);
};

#endif // WORKER_H
