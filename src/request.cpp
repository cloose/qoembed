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
#include "request.h"

#include <QUrlQuery>

namespace qoembed {

Request Request::createForUrl(const QUrl &url)
{
    return Request(url);
}

Request &Request::withMaxWidth(unsigned width)
{
    m_maxWidth = width;
    return *this;
}

Request &Request::withMaxHeight(unsigned height)
{
    m_maxHeight = height;
    return *this;
}

QUrl Request::url() const
{
    return m_url;
}

unsigned Request::maxWidth() const
{
    return m_maxWidth;
}

unsigned Request::maxHeight() const
{
    return m_maxHeight;
}

QUrlQuery Request::createQuery() const
{
    QUrlQuery query;
    query.addQueryItem("url", m_url.toEncoded());

    if (m_maxWidth > 0) {
        query.addQueryItem("maxwidth", QString::number(m_maxWidth));
    }

    if (m_maxHeight > 0) {
        query.addQueryItem("maxheight", QString::number(m_maxHeight));
    }

    return query;
}

Request::Request(const QUrl &u) :
    m_url(u),
    m_maxWidth(0),
    m_maxHeight(0)
{
}

} // namespace qoembed
