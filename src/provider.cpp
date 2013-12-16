#include "provider.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegExp>
#include <QUrl>
#include <QUrlQuery>

#include "request.h"

namespace qoembed {

static QMap<QString, QString> InitUrlSchemeToEndpoints()
{
    QMap<QString, QString> urlSchemeToEndpoints;
    urlSchemeToEndpoints.insert("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/watch.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http://[-\\w]+\\.flickr\\.com/photos/.+$", "http://www.flickr.com/services/oembed/");
    urlSchemeToEndpoints.insert("^http://www\\.slideshare\\.net/.+$", "https://www.slideshare.net/api/oembed/2");
    return urlSchemeToEndpoints;
}

const QMap<QString, QString> Provider::urlSchemeToEndpoints = InitUrlSchemeToEndpoints();

class ProviderPrivate
{
public:
    ~ProviderPrivate() { delete manager; }

    QString endpoint;
    QNetworkAccessManager *manager;
};


Provider::Provider(const QString &endpoint, QObject *parent) :
    QObject(parent),
    d(new ProviderPrivate)
{
    d->endpoint = endpoint;
    d->manager = new QNetworkAccessManager();

    connect(d->manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(replyFinished(QNetworkReply*)));
}

Provider::~Provider()
{
    qDebug() << Q_FUNC_INFO;
    delete d;
}

void Provider::setEndpoint(const QString &endpoint)
{
    d->endpoint = endpoint;
}

QString Provider::endpoint() const
{
    return d->endpoint;
}

void Provider::fetch(const Request &request)
{
    QUrl requestUrl(endpoint());
    requestUrl.setQuery(request.createQuery());

    qDebug() << request.url() << requestUrl;

    d->manager->get(QNetworkRequest(requestUrl));
}

Provider *Provider::createForUrl(const QUrl &url, QObject *parent)
{
    QMapIterator<QString, QString> it(urlSchemeToEndpoints);
    while (it.hasNext()) {
        it.next();
        QRegExp rx(it.key());
        if (rx.exactMatch(url.toString())) {
            return new Provider(it.value(), parent);
        }
    }

    return 0;
}

void Provider::replyFinished(QNetworkReply *reply)
{
    QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);
    QByteArray contentData = reply->readAll();

    emit finished(contentType.toString(), contentData);
}

} // namespace qoembed
