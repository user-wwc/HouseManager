#include "client.h"
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)), houseManager(new HouseManager(this))
{
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}
Client::~Client()
{
    socket->disconnectFromHost();
}

bool Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    return socket->waitForConnected();
}

void Client::onConnected()
{
    qDebug() << "Connected to server!";
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        QJsonObject response = doc.object();
        // 根据返回的响应做不同的处理
        qDebug() << "Received from server:" << response;
    }
}

void Client::sendLoginRequest(const QString &username, const QString &password)
{
    QJsonObject request;
    request["action"] = "login";
    request["username"] = username;
    request["password"] = password;

    QJsonDocument doc(request);
    socket->write(doc.toJson());
}

void Client::sendHouseRequest()
{
    QJsonObject request = houseManager->createGetHouseRequest();
    QJsonDocument doc(request);
    qDebug() << "doc的数据为   "<<doc.toJson(QJsonDocument::Indented);
    socket->write(doc.toJson());
}

void Client::sendAddHouseRequest(const QString &location, double price, const QString &description)
{
    QJsonObject request = houseManager->createAddHouseRequest(location, price, description);
    QJsonDocument doc(request);
     qDebug() << "doc的数据为   "<<doc.toJson(QJsonDocument::Indented);
    int ret=socket->write(doc.toJson());
       qDebug() << "doc的数据为   "<<ret;
}
