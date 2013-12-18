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
