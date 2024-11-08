#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include "housemanager.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    bool connectToServer(const QString &host, quint16 port);  // 连接到服务器
    void sendLoginRequest(const QString &username, const QString &password);  // 发送登录请求
    void sendHouseRequest();  // 请求房屋数据
    void sendAddHouseRequest(const QString &location, double price, const QString &description);  // 添加房屋请求

private slots:
    void onConnected();  // 连接成功
    void onReadyRead();  // 接收到服务器数据

private:
    QTcpSocket *socket;  // TCP套接字
    HouseManager *houseManager;  // 房屋操作管理
};

#endif // CLIENT_H

