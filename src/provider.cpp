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
#include <QRegExp>
#include <QUrl>
#include <QUrlQuery>

#include "request.h"

namespace qoembed {

static QMap<QString, QString> InitUrlSchemeToEndpoints()
{
    QMap<QString, QString> urlSchemeToEndpoints;

    // Youtube
    urlSchemeToEndpoints.insert("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/watch.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/v/.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http(?:s)?://youtu\\.be/.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/user/.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/[^#?/]+#[^#?/]+/.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http(?:s)?://m\\.youtube\\.com/index.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/profile.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/view_play_list.+$", "http://www.youtube.com/oembed");
    urlSchemeToEndpoints.insert("^http(?:s)?://(?:[-\\w]+\\.)?youtube\\.com/playlist.+$", "http://www.youtube.com/oembed");

    // Flickr
    urlSchemeToEndpoints.insert("^http://[-\\w]+\\.flickr\\.com/photos/.+$", "http://www.flickr.com/services/oembed/");
    urlSchemeToEndpoints.insert("^http://flic\\.kr\\.com/.+$", "http://www.flickr.com/services/oembed/");

    // Slideshare
    urlSchemeToEndpoints.insert("^http://www\\.slideshare\\.net/.+$", "https://www.slideshare.net/api/oembed/2");

    // Twitter
    urlSchemeToEndpoints.insert("^http(?:s)?://twitter\\.com/(?:#!)?[^#?/]+/status/.+$", "https://api.twitter.com/1/statuses/oembed.{format}");

    return urlSchemeToEndpoints;
}

const QMap<QString, QString> Provider::urlSchemeToEndpoints = InitUrlSchemeToEndpoints();

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
