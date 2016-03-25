#ifndef LTHREAD_H
#define LTHREAD_H

#include <QThread>
#include <QString>

class LThread : public QThread
{
  public:
      // constructor
      // set name using initializer
      explicit LThread(QString s);

      // overriding the QThread's run() method
      void run();

  private:
      QString name;
};

#endif // LTHREAD_H
