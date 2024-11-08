#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <QObject>
#include <QJsonObject>
#include <QByteArray>

class NetworkProtocol : public QObject
{
    Q_OBJECT

public:
    static QByteArray encodeJson(const QJsonObject &jsonObj);  // 将JSON编码为字节流
    static QJsonObject decodeJson(const QByteArray &data);  // 从字节流解码为JSON对象
};

#endif // NETWORKPROTOCOL_H
