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
#include "video.h"

#include <QString>

namespace qoembed {

class VideoPrivate
{
public:
    VideoPrivate() : width(0), height(0) {}

    QString html;
    unsigned width;
    unsigned height;
};

Video::Video() :
    Response(),
    d(new VideoPrivate)
{
}

Video::Video(const Video &other) :
    Response(other)
{
    d = new VideoPrivate;
    d->html = other.d->html;
    d->width = other.d->width;
    d->height = other.d->height;
}

Video::~Video()
{
    delete d;
}

Video &Video::operator=(const Video &rhs)
{
    // no self-assignment
    if (this != &rhs) {
        Response::operator =(rhs);
        d->html = rhs.d->html;
        d->width = rhs.d->width;
        d->height = rhs.d->height;
    }

    return *this;
}

QString Video::render() const
{
    return html();
}

void Video::setHtml(const QString &html)
{
    d->html = html;
}

QString Video::html() const
{
    return d->html;
}

void Video::setWidth(unsigned width)
{
    d->width = width;
}

unsigned Video::width() const
{
    return d->width;
}

void Video::setHeight(unsigned height)
{
    d->height = height;
}

unsigned Video::height() const
{
    return d->height;
}

} // namespace qoembed
