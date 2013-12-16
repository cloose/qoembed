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

} // namespace qoembed
