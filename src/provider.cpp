/*
 * Copyright (c) 2013, Christian Loose
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "provider.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QUrl>
#include <QUrlQuery>

#include "request.h"

namespace qoembed {

/* information comes from https://github.com/panzi/oembedendpoints */
static QMap<QString, QRegularExpression> InitEndpointToUrlSchemes()
{
    QMap<QString, QRegularExpression> endpointToUrlSchemes;

    // Youtube
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/watch.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/v/.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://youtu\\.be/.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/user/.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/[^#?/]+#[^#?/]+/.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://m\\.youtube\\.com/index.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/profile.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/view_play_list.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.youtube.com/oembed"), QRegularExpression("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/playlist.+$"));

    // Flickr
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.flickr.com/services/oembed/"), QRegularExpression("^http://[-\\w]+\\.flickr\\.com/photos/.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.flickr.com/services/oembed/"), QRegularExpression("^http://flic\\.kr\\.com/.+$"));

    // Kickstarter
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.kickstarter.com/services/oembed"), QRegularExpression("^http://[-\\w]+\\.kickstarter\\.com/projects/.+$"));

    // Slideshare
    endpointToUrlSchemes.insertMulti(QStringLiteral("https://www.slideshare.net/api/oembed/2"), QRegularExpression("^http://www\\.slideshare\\.net/.+$"));

    // Twitter
    endpointToUrlSchemes.insertMulti(QStringLiteral("https://api.twitter.com/1/statuses/oembed.{format}"), QRegularExpression("^http(?:s)?://twitter\\.com/(?:#!)?[^#?/]+/status/.+$"));

    // Vimeo
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.vimeo.com/api/oembed.{format}"), QRegularExpression("^http(?:s)?://(?:www\\.)?vimeo\\.com/.+$"));
    endpointToUrlSchemes.insertMulti(QStringLiteral("http://www.vimeo.com/api/oembed.{format}"), QRegularExpression("^http(?:s)?://player\\.vimeo\\.com/.+$"));

    return endpointToUrlSchemes;
}

const QMap<QString, QRegularExpression> Provider::endpointToUrlSchemes = InitEndpointToUrlSchemes();

class ProviderPrivate
{
public:
    ProviderPrivate() : manager(0) {}
    ~ProviderPrivate() { delete manager; }

    QString endpoint;
    QNetworkAccessManager *manager;
};


Provider::Provider(const QString &endpoint, QObject *parent) :
    QObject(parent),
    d(new ProviderPrivate)
{
    setObjectName("Provider for " + endpoint);
    d->endpoint = endpoint;
    d->manager = new QNetworkAccessManager();

    connect(d->manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(replyFinished(QNetworkReply*)));
}

Provider::~Provider()
{
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
    QMapIterator<QString, QRegularExpression> it(endpointToUrlSchemes);
    while (it.hasNext()) {
        it.next();
        QRegularExpressionMatch match = it.value().match(url.toString());
        if (match.hasMatch()) {
            return new Provider(it.key(), parent);
        }
    }

    return 0;
}

void Provider::replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);
        QByteArray contentData = reply->readAll();

        emit finished(contentType.toString(), contentData);
    } else {
        emit error(reply->error(), reply->errorString());
    }

    reply->deleteLater();
}

} // namespace qoembed
