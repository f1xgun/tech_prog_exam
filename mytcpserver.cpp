#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include "functions.h"

MyTcpServer::~MyTcpServer()
{
    foreach (int i, SClients.keys())
    {
        SClients[i]->close();
        SClients.remove(i);
    }
    mTcpServer->close();
    server_status = 0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333))
    {
        qDebug() << "server is not started";
    }
    else
    {
        server_status = 1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    if (server_status == 1)
    {
        QTcpSocket *clientSocket = mTcpServer->nextPendingConnection();
        int user_socket_id = clientSocket->socketDescriptor();
        SClients[user_socket_id] = clientSocket;
        connect(SClients[user_socket_id], &QTcpSocket::readyRead,
                this, &MyTcpServer::slotServerRead);
        connect(SClients[user_socket_id], &QTcpSocket::disconnected,
                this, &MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket *clientSocket = (QTcpSocket *)sender();
    QByteArray array;
    while (clientSocket->bytesAvailable() > 0)
    {
        array = clientSocket->readAll();
    }
    QByteArray result = parser(array.trimmed(), clientSocket->socketDescriptor());
    if (result.toStdString().find("disconnect") != std::string::npos) {
        QStringList strings = QString(result).split("\r\n");
        for (int i = 1; i < 8; i++) {
            for (int j = 8; j < 15; j++) {
                SClients[strings[i].toInt()]->write(strings[j].toUtf8()+ "\r\n");
            }
            SClients[strings[i].toInt()]->write("Отключение от очереди в комнату!");
            SClients.remove(strings[i].toInt());
        }
    }
    else {
        clientSocket->write(result + "\r\n");
    }

}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *clientSocket = (QTcpSocket *)sender();
    int user_socket_id = clientSocket->socketDescriptor();
    clientSocket->close();
    SClients.remove(user_socket_id);
}
