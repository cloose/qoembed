#include "response.h"

#include <QString>

namespace qoembed {

class ResponsePrivate
{
public:
    QString type;
    QString version;
    QString title;
    QString authorName;
    QString authorUrl;
    QString providerName;
    QString providerUrl;
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
    }

    return *this;
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

} // namespace qoembed
