#include "ConnectionHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QThread>
ConnectionHandler::ConnectionHandler(QTcpSocket *socket,DatabaseManager* database)
    : socket(socket), dbManager(database)
{
    // 确保在处理请求时保持长连接
    socket->moveToThread(QThread::currentThread());


    connect(socket, &QTcpSocket::readyRead, this, &ConnectionHandler::run);//类似于epoll的EPOLLIN
  connect(socket, &QTcpSocket::disconnected, this, &ConnectionHandler::onDisconnected);
}

void ConnectionHandler::run()
{
    QThread::usleep(1000);
      //qDebug() << "success add data 15";
    if (!dbManager->isConnected()) {
        dbManager->connectToDatabase();  // 确保数据库连接是线程安全的
    }
    QByteArray data = socket->readAll();  // 读取客户端发送的数据
    if (data.isEmpty()) return;

    // 解码并处理请求
    QJsonObject request = NetworkProtocol::decodeJson(data);//解析成json数据包
    QString action = request["action"].toString(); //先解析命令
    qDebug()<<"解析命令添加action ："<<action;
    if (action == "login") {
        handleLoginRequest(data);
          qDebug() << "success add data 28";
    } else if (action == "get_house_data" || action == "add_house_data" || action == "delete_house_data") {
        handleDataRequest(data);
          qDebug() << "success add data 30";
    } else {
        qDebug() << "Unknown action" << action;
    }
}

void ConnectionHandler::onDisconnected()
{
    socket->close();
    socket->deleteLater(); // 确保 socket 在断开后正确释放
}

void ConnectionHandler::handleLoginRequest(const QByteArray &data)//处理登录返回true
{
    QJsonObject request = NetworkProtocol::decodeJson(data);
    QString username = request["username"].toString();
    QString password = request["password"].toString();

    bool isAuthenticated = dbManager->authenticateUser(username, password);
    QJsonObject response;
    response["authenticated"] = isAuthenticated;
    qDebug() << "login is "<<isAuthenticated;
    sendResponse(NetworkProtocol::encodeJson(response));  // 返回登录结果  1
}

void ConnectionHandler::handleDataRequest(const QByteArray &data)
{
      qDebug() << "success add data 51";
    qDebug() << "success add data 54"<<data;
    QJsonObject request = NetworkProtocol::decodeJson(data);
     qDebug() << "success add data 56"<<request;
    QString action = request["action"].toString();
    QJsonObject response;
qDebug()<<"解析命令添加house ："<<action;
    if (action == "get_house_data") {
        response = dbManager->getHouseData();  // 获取房屋数据

    } else if (action == "add_house_data") {
          qDebug() << "success add data 60";
        // 打印 house_data 内容
        QJsonObject houseData = request["house_data"].toObject();
        qDebug() << "success add data 62" << QJsonDocument(houseData).toJson(QJsonDocument::Indented);

        response["success"] = dbManager->addHouseData(houseData);  // 添加房屋数据
            qDebug() << "success add data 62";
    } else if (action == "delete_house_data") {
        response["success"] = dbManager->deleteHouseData(request["house_id"].toInt());  // 删除房屋数据
    }
qDebug() << "success add data 68";
    int ret=sendResponse(NetworkProtocol::encodeJson(response));  // 转成二进制发回去
qDebug() << "sendResponse ret:"<<ret;
}

int ConnectionHandler::sendResponse(const QByteArray &response)
{
   int ret= socket->write(response);
    if(ret<0){
       return -1;
    }
       // 将响应数据发送回客户端
    socket->flush();
    return 0;
}
