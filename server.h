#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThreadPool>
#include "ConnectionHandler.h"
#include"databasemanager.h"
class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    bool startServer(quint16 port);  // 启动服务器并监听指定端口

private slots:
    void onNewConnection();  // 处理新连接

private:
    QTcpServer *tcpServer;    // TCP服务器对象
    QThreadPool *threadPool;  // 线程池对象
    //DatabaseManager *dbManager ;
};

#endif // SERVER_H
