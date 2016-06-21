#include <QCoreApplication>
#include <iostream>
#include <QtTest>
#include <QDebug>

#include "t_lrpc.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  qDebug() << "Test build";

  TestLRpc lrpc;

  auto failed_cnt = QTest::qExec(&lrpc, argc, argv);

  qDebug() << "\nFailed " << failed_cnt << " tests";

  return a.exec();
}
