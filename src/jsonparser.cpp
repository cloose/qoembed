#include "jsonparser.h"

#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "response.h"

namespace qoembed {

JsonParser::JsonParser()
{
}

Response *JsonParser::fromJson(const QByteArray &data)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
//    qDebug() << data;
//    qDebug() << doc.isObject() << doc.isArray() << doc.isEmpty() << doc.isNull();
    qDebug() << error.errorString() << error.offset;

    QJsonObject obj = doc.object();

    Response *response = new Response();
    response->setType(obj.value("type").toString());
    response->setVersion(obj.value("version").toString());
    response->setTitle(obj.value("title").toString());
    response->setAuthorName(obj.value("author_name").toString());
    response->setAuthorUrl(obj.value("author_url").toString());
    response->setProviderName(obj.value("provider_name").toString());
    response->setProviderUrl(obj.value("provider_url").toString());

    return response;
}

} // namespace qoembed
