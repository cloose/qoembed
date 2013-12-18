#include "xmlparser.h"

#include <QByteArray>
#include <QDebug>
#include <QDomDocument>

#include "response.h"
#include "rich.h"
#include "video.h"

namespace qoembed {

XmlParser::XmlParser()
{
}

Response *XmlParser::fromXml(const QByteArray &data)
{
    QString errorMsg;
    int errorLine = 0;
    int errorColumn = 0;

    QDomDocument doc;
    doc.setContent(data, &errorMsg, &errorLine, &errorColumn);
//    qDebug() << data;
    qDebug() << errorMsg << errorLine << errorColumn;

    QDomElement root = doc.documentElement();

    QString type = findElement(root, "type").text();
    if (type == "video") {
        Video* video = new Video();
        fillCommonValues(root, video);

        video->setHtml(findElement(root, "html").text());
        QString width = findElement(root, "width").text();
        video->setWidth(width.toUInt());
        QString height = findElement(root, "height").text();
        video->setHeight(height.toUInt());

        return video;
    } else if (type == "rich") {
        Rich* rich = new Rich();
        fillCommonValues(root, rich);

        rich->setHtml(findElement(root, "html").text());
        QString width = findElement(root, "width").text();
        rich->setWidth(width.toUInt());
        QString height = findElement(root, "height").text();
        rich->setHeight(height.toUInt());

        return rich;
    }

    Response *response = new Response();
    fillCommonValues(root, response);

    return response;
}

void XmlParser::fillCommonValues(const QDomElement &root, Response *response)
{
    response->setType(findElement(root, "type").text());
    response->setVersion(findElement(root, "version").text());
    response->setTitle(findElement(root, "title").text());
    response->setAuthorName(findElement(root, "author_name").text());
    response->setAuthorUrl(findElement(root, "author_url").text());
    response->setProviderName(findElement(root, "provider_name").text());
    response->setProviderUrl(findElement(root, "provider_url").text());
}

QDomElement XmlParser::findElement(const QDomElement &root, const QString &tagName) const
{
    QDomElement element = root.firstChildElement(tagName);

    // Providers like Slideshare use "author-name" instead of "author_name"
    if (element.isNull() && tagName.contains("_")) {
        element = root.firstChildElement(QString(tagName).replace("_", "-"));
    }

    return element;
}

} // namespace qoembed
