#include "NetworkProtocol.h"
#include <QJsonDocument>

QByteArray NetworkProtocol::encodeJson(const QJsonObject &jsonObj)
{
    QJsonDocument doc(jsonObj);
    return doc.toJson();  // 将JSON对象编码为字节流
}

QJsonObject NetworkProtocol::decodeJson(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qCritical() << "Failed to parse JSON data";
        return QJsonObject();
    }
    return doc.object();  // 返回JSON对象
}
