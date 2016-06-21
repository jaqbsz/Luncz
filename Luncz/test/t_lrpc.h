#include <QObject>
#include <QDebug>
#include <QtTest>

#include "src/Lrpc.h"

class TestLRpc : public QObject
{
  Q_OBJECT

  private slots:
    // functions executed by QtTest before and after test suite
    void initTestCase(){}
    void cleanupTestCase(){}

    // functions executed by QtTest before and after each test
    void init(){}
    void cleanup(){}

    // test functions - all functions prefixed with "test" will be ran as tests
    void test_TEST();
};
