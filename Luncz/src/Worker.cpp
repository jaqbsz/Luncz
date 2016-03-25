#include <QDebug>
#include <QString>

#include "Worker.h"


Worker::Worker(QObject *parent) : QObject(parent)
{
}


void Worker::slot_newRequest(void * socket_desc, QByteArray data)
{
  qDebug() << "new request received..." << QString(data) << endl;

  data[0] = 'Q';

  emit signal_newResponse(socket_desc, data);
}
