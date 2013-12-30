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
#ifndef QOEMBED_RESPONSE_H
#define QOEMBED_RESPONSE_H

#include "qoembed_global.h"

#include <QMetaType>

namespace qoembed {

class ResponsePrivate;

/*!
 * \brief Contains the oEmbed data about a URL, as returned by a qoembed::Provider.
 */
class QOEMBEDSHARED_EXPORT Response
{
public:
    Response();
    Response(const Response &other);
    virtual ~Response();

    Response &operator=(const Response &rhs);

    virtual QString render() const;

    void setType(const QString &type);

    /*!
     * \return the resource type
     */
    QString type() const;

    void setVersion(const QString &version);

    /*!
     * \return the oEmbed version number
     */
    QString version() const;

    void setTitle(const QString &title);

    /*!
     * \return a text title, describing the resource
     */
    QString title() const;

    void setAuthorName(const QString &authorName);

    /*!
     * \return the name of the author/owner of the resource
     */
    QString authorName() const;

    void setAuthorUrl(const QString &authorUrl);

    /*!
     * \return a URL for the author/owner of the resource
     */
    QString authorUrl() const;

    void setProviderName(const QString &providerName);
    QString providerName() const;

    void setProviderUrl(const QString &providerUrl);
    QString providerUrl() const;

    void setThumbnailUrl(const QString &thumbnailUrl);
    QString thumbnailUrl() const;

    void setThumbnailWidth(unsigned thumbnailWidth);
    unsigned thumbnailWidth() const;

    void setThumbnailHeight(unsigned thumbnailHeight);
    unsigned thumbnailHeight() const;

    /*!
     * \return \c true if this is an error response
     */
    bool isError() const;

    /*!
     * \return \c true if this is an oEmbed link response
     */
    bool isLink() const;

    /*!
     * \return \c true if this is an oEmbed photo response
     */
    bool isPhoto() const;

    /*!
     * \return \c true if this is an oEmbed rich response
     */
    bool isRich() const;

    /*!
     * \return \c true if this is an oEmbed video response
     */
    bool isVideo() const;

private:
    ResponsePrivate *d;
};

} // namespace qoembed

Q_DECLARE_METATYPE(qoembed::Response*)

#endif // QOEMBED_RESPONSE_H
