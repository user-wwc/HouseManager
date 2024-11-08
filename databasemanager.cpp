#include "DatabaseManager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include<QJsonArray>
#include"tool.h"
DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("aa");
    db.setUserName("root");  // 请根据你的设置更改用户名
    db.setPassword("123456");  // 请根据你的设置更改密码
}

DatabaseManager::~DatabaseManager()
{
    db.close();  // 关闭数据库连接
}

bool DatabaseManager::connectToDatabase()
{
    // db = QSqlDatabase::addDatabase("QODBC");
    // db.setHostName("127.0.0.1");
    // db.setPort(3306);
    // db.setDatabaseName("aa");
    // db.setUserName("root");  // 请根据你的设置更改用户名
    // db.setPassword("123456");  // 请根据你的设置更改密码
    if (!db.isOpen()) {
        return db.open();
    }
    return true;
}

bool DatabaseManager::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM user WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec() || !query.next()) {
        return false;
    }

    QString storedPassword = query.value(0).toString();
    return storedPassword == password;  // 验证密码
}

QJsonObject DatabaseManager::getHouseData()
{
    qDebug()<<"执行到了查找房屋u数据";
    QSqlQuery query("SELECT * FROM houses");
    QJsonObject result;

    // 使用 QJsonArray 来存储所有房屋数据
    QJsonArray houses;
    while (query.next()) {
        QJsonObject house;
        house["house_id"] = query.value("house_id").toInt();
        house["location"] = query.value("location").toString();
        house["price"] = query.value("price").toDouble();
        house["description"] = query.value("description").toString();
        houses.append(house);
    }

    result["houses"] = houses;
    qCritical() << "成功查找到数据";
    return result;
}

bool DatabaseManager::addHouseData(const QJsonObject &houseData)
{
     qDebug() << "success add data 1";
    QSqlQuery query;
     QString location=houseData["location"].toString();
     double  price=houseData["price"].toDouble();
      QString description=houseData["description"].toString();
     qDebug() << "Location:" <<location;
     qDebug() << "Price:" << price;
     qDebug() << "Description:" <<description;
     if (location.isEmpty() || description.isEmpty() || price <= 0) {
         qDebug() << "Error: invalid data - location, description, or price is empty/invalid.";
         return false;  // 返回 false，不插入空数据
     }
    query.prepare("INSERT INTO houses (location, price, description) VALUES (:location, :price, :description)");//宏映射
    query.bindValue(":location", location);
    query.bindValue(":price", price);
    query.bindValue(":description", description);

    if (!query.exec()) {//执行
        qDebug() << "Failed to add house data:" << query.lastError().text();
        return false;
    }
   qDebug() << "success add data 1";
    return true;
}

bool DatabaseManager::deleteHouseData(int houseId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM houses WHERE house_id = :house_id");
    query.bindValue(":house_id", houseId);

    if (!query.exec()) {
        qCritical() << "Failed to delete house data:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::isConnected()
{
        return db.isOpen();
}

