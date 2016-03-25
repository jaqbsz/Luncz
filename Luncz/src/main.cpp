
#include <QCoreApplication>

#include "lthread.h"
#include "server.h"
#include "Worker.h"

int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  Server o_server;
  Worker o_worker;

  LThread th_server("SERVER");
  LThread th_worker("WORKER");

  QObject::connect(&o_server, SIGNAL(signal_newRequest(void*,QByteArray)), &o_worker, SLOT(slot_newRequest(void*,QByteArray)));
  QObject::connect(&o_worker, SIGNAL(signal_newResponse(void*,QByteArray)), &o_server, SLOT(slot_newResponse(void*,QByteArray)));

  o_server.moveToThread(&th_server);
  o_worker.moveToThread(&th_worker);

  th_server.start();
  th_worker.start();

  return a.exec();
}
