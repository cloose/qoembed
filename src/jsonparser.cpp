#include "jsonparser.h"

#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "response.h"
#include "rich.h"
#include "video.h"

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

    QString type = obj.value("type").toString();
    if (type == "video") {
        Video* video = new Video();
        fillCommonValues(obj, video);

        video->setHtml(obj.value("html").toString());
        QString width = obj.value("width").toString();
        video->setWidth(width.toUInt());
        QString height = obj.value("height").toString();
        video->setHeight(height.toUInt());

        return video;
    } else if (type == "rich") {
        Rich* rich = new Rich();
        fillCommonValues(obj, rich);

        rich->setHtml(obj.value("html").toString());
        QString width = obj.value("width").toString();
        rich->setWidth(width.toUInt());
        QString height = obj.value("height").toString();
        rich->setHeight(height.toUInt());

        return rich;
    }

    Response *response = new Response();
    fillCommonValues(obj, response);

    return response;
}

void JsonParser::fillCommonValues(const QJsonObject &obj, Response *response)
{
    response->setType(obj.value("type").toString());
    response->setVersion(obj.value("version").toString());
    response->setTitle(obj.value("title").toString());
    response->setAuthorName(obj.value("author_name").toString());
    response->setAuthorUrl(obj.value("author_url").toString());
    response->setProviderName(obj.value("provider_name").toString());
    response->setProviderUrl(obj.value("provider_url").toString());
}

} // namespace qoembed
