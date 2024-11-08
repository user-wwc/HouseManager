#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

#include <QObject>
#include <QJsonObject>

class HouseManager : public QObject
{
    Q_OBJECT

public:
    explicit HouseManager(QObject *parent = nullptr);

    // 构建房屋添加请求的 JSON 数据
    QJsonObject createAddHouseRequest(const QString &location, double price, const QString &description);

    // 构建获取所有房屋数据请求的 JSON 数据
    QJsonObject createGetHouseRequest();

private:
         // 这里可以封装一些房屋操作的具体实现逻辑（例如格式验证等）
};

#endif // HOUSEMANAGER_H
