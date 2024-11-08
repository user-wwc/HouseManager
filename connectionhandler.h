#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QRunnable>
#include <QTcpSocket>
#include "databasemanager.h"
#include "networkprotocol.h"

class ConnectionHandler : public QRunnable ,public QObject  //直接继承QRunnale当作pool的任务类
{
public:
    explicit ConnectionHandler(QTcpSocket *socket,DatabaseManager* database);
    void run() override;  // 处理客户端请求

private:
    QTcpSocket *socket;
    DatabaseManager *dbManager;

    void handleLoginRequest(const QByteArray &data);  // 处理登录请求
    void handleDataRequest(const QByteArray &data);   // 处理房屋数据请求
    int sendResponse(const QByteArray &response);    // 发送响应给客户端
    void onDisconnected();
};

#endif // CONNECTIONHANDLER_H
