#include "xmlparser.h"

#include <QByteArray>
#include <QDebug>
#include <QDomDocument>

#include "response.h"

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

    Response *response = new Response();
    response->setType(findElement(root, "type").text());
    response->setVersion(findElement(root, "version").text());
    response->setTitle(findElement(root, "title").text());
    response->setAuthorName(findElement(root, "author_name").text());
    response->setAuthorUrl(findElement(root, "author_url").text());
    response->setProviderName(findElement(root, "provider_name").text());
    response->setProviderUrl(findElement(root, "provider_url").text());

    return response;
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
