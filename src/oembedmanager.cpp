#include "oembedmanager.h"

#include <QDebug>
#include <QUrl>

#include "jsonparser.h"
#include "provider.h"
#include "request.h"
#include "xmlparser.h"

namespace qoembed {

OEmbedManager::OEmbedManager(QObject *parent) :
    QObject(parent)
{
}

OEmbedManager::~OEmbedManager()
{
}

void OEmbedManager::fetch(const Request &request)
{
    Provider *provider = Provider::createForUrl(request.url()/*, this*/);

    connect(provider, SIGNAL(finished(QString, QByteArray)),
            SLOT(replyFinished(QString,QByteArray)));
    connect(provider, SIGNAL(error(QNetworkReply::NetworkError,QString)),
            SLOT(replyError(QNetworkReply::NetworkError,QString)));

    provider->fetch(request);
}

void OEmbedManager::replyFinished(const QString &contentType, const QByteArray &content)
{
    qDebug() << contentType;
    qDebug() << content;

    Response *response = 0;

    if (contentType.contains("json")) {
        JsonParser parser;
        response = parser.fromJson(content);
    }

    if (contentType.contains("xml")) {
        XmlParser parser;
        response = parser.fromXml(content);
    }

    emit finished(response);

    // delete now unneeded provider
    sender()->deleteLater();
}

void OEmbedManager::replyError(QNetworkReply::NetworkError code, const QString &errorString)
{
    // TODO!
    qDebug() << code << errorString;

    // delete now unneeded provider
    sender()->deleteLater();
}

} // namespace qoembed
