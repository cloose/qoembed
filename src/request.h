#ifndef QOEMBED_REQUEST_H
#define QOEMBED_REQUEST_H

#include "qoembed_global.h"

#include <QString>
#include <QUrl>

namespace qoembed {

class QOEMBEDSHARED_EXPORT Request
{
public:
    // builder methods
    static Request createForUrl(const QUrl &url);
    Request &withMaxWidth(unsigned width);
    Request &withMaxHeight(unsigned height);

    QUrl url() const;
    unsigned maxWidth() const;
    unsigned maxHeight() const;

    QUrlQuery createQuery() const;

private:
    explicit Request(const QUrl &u);

    QUrl m_url;
    unsigned m_maxWidth;
    unsigned m_maxHeight;
    QString format;
};

} // namespace qoembed

#endif // QOEMBED_REQUEST_H
