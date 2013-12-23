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
#ifndef QOEMBED_PROVIDER_H
#define QOEMBED_PROVIDER_H

#include "qoembed_global.h"

#include <QObject>
#include <QMap>
#include <QNetworkReply>
class QUrl;

namespace qoembed {

class ProviderPrivate;
class Request;

class QOEMBEDSHARED_EXPORT Provider : public QObject
{
    Q_OBJECT

public:
    ~Provider();

    void setEndpoint(const QString &endpoint);
    QString endpoint() const;

    void fetch(const Request &request);

    static Provider *createForUrl(const QUrl &url, QObject *parent = 0);

Q_SIGNALS:
    void error(QNetworkReply::NetworkError code, const QString &errorString);
    void finished(const QString &contentType, const QByteArray &content);

private Q_SLOTS:
    void replyFinished(QNetworkReply *reply);

private:
    explicit Provider(const QString &endpoint, QObject *parent = 0);
    Q_DISABLE_COPY(Provider)

    ProviderPrivate *d;

    static const QMap<QString, QRegularExpression> endpointToUrlSchemes;
};


} // namespace qoembed

#endif // QOEMBED_PROVIDER_H
