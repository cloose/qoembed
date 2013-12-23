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
#include "photo.h"

#include <QString>

namespace qoembed {

class PhotoPrivate
{
public:
    PhotoPrivate() : width(0), height(0) {}

    QString url;
    unsigned width;
    unsigned height;
};

Photo::Photo() :
    Response(),
    d(new PhotoPrivate)
{
}

Photo::Photo(const Photo &other) :
    Response(other)
{
    d = new PhotoPrivate;
    d->url = other.d->url;
    d->width = other.d->width;
    d->height = other.d->height;
}

Photo::~Photo()
{
    delete d;
}

Photo &Photo::operator=(const Photo &rhs)
{
    // no self-assignment
    if (this != &rhs) {
        Response::operator =(rhs);
        d->url = rhs.d->url;
        d->width = rhs.d->width;
        d->height = rhs.d->height;
    }

    return *this;
}

QString Photo::render() const
{
    return QString("<img src=\"%1\" style=\"width:%2px; height:%3px;\" alt=\"%4\" title=\"%4\"/>").arg(url()).arg(width()).arg(height()).arg(title());
}

void Photo::setUrl(const QString &url)
{
    d->url = url;
}

QString Photo::url() const
{
    return d->url;
}

void Photo::setWidth(unsigned width)
{
    d->width = width;
}

unsigned Photo::width() const
{
    return d->width;
}

void Photo::setHeight(unsigned height)
{
    d->height = height;
}

unsigned Photo::height() const
{
    return d->height;
}

} // namespace qoembed
