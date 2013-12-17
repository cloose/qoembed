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
    int errorLine, errorColumn;

    QDomDocument doc;
    doc.setContent(data, &errorMsg, &errorLine, &errorColumn);
    qDebug() << data;
    qDebug() << errorMsg << errorLine << errorColumn;

    QDomElement root = doc.documentElement();

    Response *response = new Response();
    response->setType(root.firstChildElement("type").text());
    response->setVersion(root.firstChildElement("version").text());

    return response;
}

} // namespace qoembed
