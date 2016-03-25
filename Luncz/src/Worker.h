#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT

  public:
    explicit Worker(QObject *parent = 0);

  signals:
    // send event to worker thread
    void signal_newResponse(void * socket_desc, QByteArray data);

  public slots:
    void slot_newRequest(void * socket_desc, QByteArray);

  private:
    QByteArray * data;
    const void * client;
};

#endif // WORKER_H
