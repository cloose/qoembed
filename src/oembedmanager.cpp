#include "oembedmanager.h"

#include <QDebug>
#include <QUrl>

#include "jsonparser.h"
#include "provider.h"
#include "request.h"

namespace qoembed {

OEmbedManager::OEmbedManager(QObject *parent) :
    QObject(parent)
{
}

OEmbedManager::~OEmbedManager()
{
    qDebug() << Q_FUNC_INFO;
}

void OEmbedManager::fetch(const Request &request)
{
    Provider *provider = Provider::createForUrl(request.url(), this);

    connect(provider, SIGNAL(finished(QString, QByteArray)),
            SLOT(replyFinished(QString,QByteArray)));

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

    emit finished(response);
}

} // namespace qoembed
