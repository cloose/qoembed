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
#ifndef QOEMBED_REQUEST_H
#define QOEMBED_REQUEST_H

#include "qoembed_global.h"

#include <QString>
#include <QUrl>

namespace qoembed {


/*!
 * \brief Contains the query parameters for a request sent to a qoembed::Provider.
 */
class QOEMBEDSHARED_EXPORT Request
{
public:
    // builder methods
    static Request createForUrl(const QUrl &url);
    Request &withMaxWidth(unsigned width);
    Request &withMaxHeight(unsigned height);
    Request &withFormat(const QString &format);

    /*!
     * \return the URL to retrieve embedding information for
     */
    QUrl url() const;

    /*!
     * \return the maximum width of the embedded resource
     */
    unsigned maxWidth() const;

    /*!
     * \return the maximum height of the embedded resource
     */
    unsigned maxHeight() const;

    /*!
     * \return the required response format
     */
    QString format() const;

    QUrlQuery createQuery() const;

private:
    explicit Request(const QUrl &u);

    QUrl m_url;
    unsigned m_maxWidth;
    unsigned m_maxHeight;
    QString m_format;
};

} // namespace qoembed

#endif // QOEMBED_REQUEST_H
