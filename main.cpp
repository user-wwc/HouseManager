#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    if (client.connectToServer("127.0.0.1", 12345)) {
        // 发送登录请求
        //client.sendLoginRequest("wwc", "123");

        // 获取房屋数据
        //client.sendHouseRequest();

        // 添加新房屋
        client.sendAddHouseRequest("Downtown", 500, "3 bedroom apartment");
    } else {
        qCritical() << "Failed to connect to server!";
    }

    return a.exec();
}
