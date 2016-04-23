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
    void signal_newRequest(void * socket_desc, const QByteArray &in_data);

  public slots:
    void slot_newConnection();
    void slot_disconnected();
    void slot_bytesWritten(qint64 bytes);
    void slot_readyRead();
    void slot_newResponse(void * socket_desc, const QByteArray &out_data);

  private:
    QTcpServer *server;

    // for test purposes
    QByteArray test_add_user();
    QByteArray test_add_order();
    QByteArray test_list_users();

    // currently not necessary to list connected clients
    //list<QTcpSocket*> sock_list;
};

#endif // SERVER_H
