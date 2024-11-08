#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonObject>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool connectToDatabase();
    bool authenticateUser(const QString &username, const QString &password);
    QJsonObject getHouseData();
    bool addHouseData(const QJsonObject &houseData);
    bool deleteHouseData(int houseId);

    bool isConnected();

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
