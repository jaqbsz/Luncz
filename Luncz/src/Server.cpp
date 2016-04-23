
#include <QDebug>
#include <QJsonDocument>

#include <QFile>

#include "server.h"

//**************************************************************************************
//* constructor()
//*
//**************************************************************************************
Server::Server(QObject *parent) : QObject(parent)
{
  this->server = new QTcpServer(this);

  // define callback for new connections
  connect(this->server, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));

  if(!server->listen(QHostAddress::Any, 9876))
  {
      qDebug() << "Server could not start";
  }
  else
  {
      qDebug() << "Server started!";
  }
}

//**************************************************************************************
//* slot_newConnection()
//*
//**************************************************************************************
void Server::slot_newConnection()
{
  QTcpSocket* sock = NULL;

  do
  {
    QTcpSocket* sock = this->server->nextPendingConnection();

    qDebug() << "New connection established.";

    if ( sock )
    {
      connect(sock, SIGNAL(disconnected()),this, SLOT(slot_disconnected()));
      connect(sock, SIGNAL(bytesWritten(qint64)),this, SLOT(slot_bytesWritten(qint64)));
      connect(sock, SIGNAL(readyRead()),this, SLOT(slot_readyRead()));
    }
  }while (sock);
}

//**************************************************************************************
//* slot_disconnected()
//*
//**************************************************************************************
void Server::slot_disconnected()
{
    qDebug() << "disconnected..."<<endl;
}

//**************************************************************************************
//* slot_bytesWritten()
//*
//**************************************************************************************
void Server::slot_bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written..."<<endl;
}

//**************************************************************************************
//* slot_readyRead()
//*
//**************************************************************************************
void Server::slot_readyRead()
{
    qDebug() << "reading..."<<endl;

    // get socket from event sender
    QTcpSocket* sock = qobject_cast<QTcpSocket*>(sender());

    // read received data
    QByteArray data = sock->readAll();

    emit signal_newRequest(static_cast<void*>(sock), data);

    // emit event with received data
//    if (data.at(0)=='w')
//    {
//      qDebug() << "new request emited"<<endl;
//      QByteArray test_data = test_list_users();
//      emit signal_newRequest(static_cast<void*>(sock), test_data);
//    }

//    if (data.at(0)=='e')
//    {
//      qDebug() << "new request emited"<<endl;
//      QByteArray test_data = test_add_user();
//      emit signal_newRequest(static_cast<void*>(sock), test_data);
//    }

//    if (data.at(0)=='r')
//    {
//      qDebug() << "new request emited"<<endl;
//      QByteArray test_data = test_add_order();
//      emit signal_newRequest(static_cast<void*>(sock), test_data);
//    }
}

//**************************************************************************************
//* slot_newResponse()
//*
//* note: in_data is a copy here - check intertherad communication in QT
//**************************************************************************************
void Server::slot_newResponse(void * socket_desc, const QByteArray &out_data)
{
  QTcpSocket* sock = static_cast<QTcpSocket*>(socket_desc);

  qDebug() << "new resnponse..."<<endl;
  qDebug() << out_data;

//  sock->write(out_data);
//  sock->flush();
}

//**************************************************************************************
//* test_JSON()
//*
//**************************************************************************************
QByteArray Server::test_list_users()
{
  QFile file;

  file.setFileName("../json/test_list_users.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QByteArray data = file.readAll();
  file.close();

  return data;
}

QByteArray Server::test_add_user()
{
  QFile file;

  file.setFileName("../json/test_add_user.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QByteArray data = file.readAll();
  file.close();

  return data;
}

QByteArray Server::test_add_order()
{
  QFile file;

  file.setFileName("../json/test_add_order.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QByteArray data = file.readAll();
  file.close();

  return data;
}
