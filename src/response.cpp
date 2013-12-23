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
#include "response.h"

#include <QString>

namespace qoembed {

class ResponsePrivate
{
public:
    ResponsePrivate() : thumbnailWidth(0), thumbnailHeight(0) {}

    QString type;
    QString version;
    QString title;
    QString authorName;
    QString authorUrl;
    QString providerName;
    QString providerUrl;
    QString thumbnailUrl;
    unsigned thumbnailWidth;
    unsigned thumbnailHeight;
};

Response::Response() :
    d(new ResponsePrivate)
{
}

Response::Response(const Response &other)
{
    d = new ResponsePrivate;
    d->type = other.d->type;
    d->version = other.d->version;
    d->title = other.d->title;
    d->authorName = other.d->authorName;
    d->authorUrl = other.d->authorUrl;
    d->providerName = other.d->providerName;
    d->providerUrl = other.d->providerUrl;
    d->thumbnailUrl = other.d->thumbnailUrl;
    d->thumbnailWidth = other.d->thumbnailWidth;
    d->thumbnailHeight = other.d->thumbnailHeight;
}

Response::~Response()
{
    delete d;
}

Response &Response::operator=(const Response &rhs)
{
    // no self-assignment
    if (this != &rhs) {
        d->type = rhs.d->type;
        d->version = rhs.d->version;
        d->title = rhs.d->title;
        d->authorName = rhs.d->authorName;
        d->authorUrl = rhs.d->authorUrl;
        d->providerName = rhs.d->providerName;
        d->providerUrl = rhs.d->providerUrl;
        d->thumbnailUrl = rhs.d->thumbnailUrl;
        d->thumbnailWidth = rhs.d->thumbnailWidth;
        d->thumbnailHeight = rhs.d->thumbnailHeight;
    }

    return *this;
}

QString Response::render() const
{
    return QString();
}

void Response::setType(const QString &type)
{
    d->type = type;
}

QString Response::type() const
{
    return d->type;
}

void Response::setVersion(const QString &version)
{
    d->version = version;
}

QString Response::version() const
{
    return d->version;
}

void Response::setTitle(const QString &title)
{
    d->title = title;
}

QString Response::title() const
{
    return d->title;
}

void Response::setAuthorName(const QString &authorName)
{
    d->authorName = authorName;
}

QString Response::authorName() const
{
    return d->authorName;
}

void Response::setAuthorUrl(const QString &authorUrl)
{
    d->authorUrl = authorUrl;
}

QString Response::authorUrl() const
{
    return d->authorUrl;
}

void Response::setProviderName(const QString &providerName)
{
    d->providerName = providerName;
}

QString Response::providerName() const
{
    return d->providerName;
}

void Response::setProviderUrl(const QString &providerUrl)
{
    d->providerUrl = providerUrl;
}

QString Response::providerUrl() const
{
    return d->providerUrl;
}

void Response::setThumbnailUrl(const QString &thumbnailUrl)
{
    d->thumbnailUrl = thumbnailUrl;
}

QString Response::thumbnailUrl() const
{
    return d->thumbnailUrl;
}

void Response::setThumbnailWidth(unsigned thumbnailWidth)
{
    d->thumbnailWidth = thumbnailWidth;
}

unsigned Response::thumbnailWidth() const
{
    return d->thumbnailWidth;
}

void Response::setThumbnailHeight(unsigned thumbnailHeight)
{
    d->thumbnailHeight = thumbnailHeight;
}

unsigned Response::thumbnailHeight() const
{
    return d->thumbnailHeight;
}

} // namespace qoembed
