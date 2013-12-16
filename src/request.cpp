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
