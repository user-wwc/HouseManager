#include"housemanager.h"

HouseManager::HouseManager(QObject *parent) : QObject(parent)
{
}

QJsonObject HouseManager::createAddHouseRequest(const QString &location, double price, const QString &description)
{
    // QJsonObject request;
    // request["action"] = "add_house_data";
    // request["location"] = location;
    // request["price"] = price;
    // request["description"] = description;
    // return request;

    QJsonObject request;
    request["action"] = "add_house_data";

    // 将 house_data 封装为一个子对象
    QJsonObject houseData;
    houseData["location"] = location;
    houseData["price"] = price;
    houseData["description"] = description;

    // 将 house_data 放入请求中
    request["house_data"] = houseData;

    return request;
}

QJsonObject HouseManager::createGetHouseRequest()
{
    QJsonObject request;
    request["action"] = "get_house_data";
    return request;
}
