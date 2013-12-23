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
#include "oembedmanager.h"

#include <QDebug>
#include <QUrl>

#include "error.h"
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

    if (!provider) {
        Error *error = new Error(tr("No suitable provider found for requested URL"));
        emit finished(error);
        return;
    }

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
