
#include <QCoreApplication>

#include "lthread.h"
#include "server.h"

int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  Server o_server;

  LThread th_server("SERVER");
  //LThread th_worker("WORKER");

  o_server.moveToThread(&th_server);

  th_server.start();

  return a.exec();
}
