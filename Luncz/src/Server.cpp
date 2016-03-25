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

  if(!server->listen(QHostAddress::Any, 23))
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

    if ( sock )
    {
      connect(sock, SIGNAL(disconnected()),this, SLOT(slot_disconnected()));
      connect(sock, SIGNAL(bytesWritten(qint64)),this, SLOT(slot_bytesWritten(qint64)));
      connect(sock, SIGNAL(readyRead()),this, SLOT(slot_readyRead()));
    }
  }while (sock);

  connect(this, SIGNAL(signal_newRequest(void*,QByteArray)), this, SLOT(slot_newResponse(void*,QByteArray)));
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

    //TODO process data againt the protocol

    // emit event with received data
    if (data.at(0)=='w')
      emit signal_newRequest(static_cast<void*>(sock), data);
}

//**************************************************************************************
//* slot_newResponse()
//*
//**************************************************************************************
void Server::slot_newResponse(void * socket_desc, QByteArray data)
{
  QTcpSocket* sock = static_cast<QTcpSocket*>(socket_desc);

  qDebug() << "new resnponse..."<<endl;

  sock->write(data);
  sock->flush();
}
