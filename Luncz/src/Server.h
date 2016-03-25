#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

// could be used to list connected clients
//#include <list>

class Server : public QObject
{
    Q_OBJECT

  public:
    explicit Server(QObject *parent = 0);

  signals:
    // send event to worker thread
    void signal_newRequest(void * socket_desc, QByteArray data);

  public slots:
    void slot_newConnection();
    void slot_disconnected();
    void slot_bytesWritten(qint64 bytes);
    void slot_readyRead();
    void slot_newResponse(void * socket_desc, QByteArray data);

  private:
    QTcpServer *server;

    // currently not necessary to list connected clients
    //list<QTcpSocket*> sock_list;
};

#endif // SERVER_H
