#ifndef QOEMBED_RESPONSE_H
#define QOEMBED_RESPONSE_H

#include "qoembed_global.h"

#include <QMetaType>

namespace qoembed {

class ResponsePrivate;

class QOEMBEDSHARED_EXPORT Response
{
public:
    Response();
    Response(const Response &other);
    ~Response();

    Response &operator=(const Response &rhs);

    void setType(const QString &type);
    QString type() const;

    void setVersion(const QString &version);
    QString version() const;

    void setTitle(const QString &title);
    QString title() const;

    void setAuthorName(const QString &authorName);
    QString authorName() const;

    void setAuthorUrl(const QString &authorUrl);
    QString authorUrl() const;

    void setProviderName(const QString &providerName);
    QString providerName() const;

    void setProviderUrl(const QString &providerUrl);
    QString providerUrl() const;

private:
    ResponsePrivate *d;
};

} // namespace qoembed

Q_DECLARE_METATYPE(qoembed::Response*)

#endif // QOEMBED_RESPONSE_H
