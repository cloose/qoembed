#include "oembedmanager.h"

#include <QDebug>
#include <QUrl>

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
    emit finished();
}

} // namespace qoembed
