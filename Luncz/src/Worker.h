#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "LRpcResult.h"

class Worker : public QObject
{
    Q_OBJECT

  public:
    explicit Worker(QObject *parent = 0);

  signals:
    // send event to servers thread
    void signal_newResponse(void * socket_desc, const QByteArray &in_data);

  public slots:
    void slot_newRequest(void * socket_desc, const QByteArray &in_data);

  private:
    LRpcResult lrpcRes;

    QByteArray * data;
    const void * client;
};

#endif // WORKER_H
