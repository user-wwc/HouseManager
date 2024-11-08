#include "Server.h"
#include <QDebug>
#include <QTcpSocket>

Server::Server(QObject *parent)
    : QObject(parent), tcpServer(new QTcpServer(this)), threadPool(new QThreadPool(this))
{
    threadPool->setMaxThreadCount(1);  // 最大线程数

}

Server::~Server()
{
    if (tcpServer->isListening()) {
        tcpServer->close();
    }
    qDebug() << "Server closed and all connections are released.";
}

bool Server::startServer(quint16 port)
{
    if (!tcpServer->listen(QHostAddress::LocalHost, port)) {
        qCritical() << "Server failed to start!";
        return false;
    }

    qDebug() << "Server started, listening on port" << port;
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);
    return true;
}

void Server::onNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();//返回客户端套接字
    if (clientSocket) {
        qDebug() << "New connection from" << clientSocket->peerAddress().toString();
         DatabaseManager *dbManager = new DatabaseManager();
        // 创建并投递一个处理该连接的任务
        ConnectionHandler *handler = new ConnectionHandler(clientSocket,dbManager);
        threadPool->start(handler);  // 使用线程池处理连接
    }
}
