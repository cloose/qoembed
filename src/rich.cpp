#include "rich.h"

#include <QString>

namespace qoembed {

class RichPrivate
{
public:
    RichPrivate() : width(0), height(0) {}

    QString html;
    unsigned width;
    unsigned height;
};

Rich::Rich() :
    Response(),
    d(new RichPrivate)
{
}

Rich::Rich(const Rich &other) :
    Response(other)
{
    d = new RichPrivate;
    d->html = other.d->html;
    d->width = other.d->width;
    d->height = other.d->height;
}

Rich::~Rich()
{
    delete d;
}

Rich &Rich::operator=(const Rich &rhs)
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

QString Rich::render() const
{
    return html();
}

void Rich::setHtml(const QString &html)
{
    d->html = html;
}

QString Rich::html() const
{
    return d->html;
}

void Rich::setWidth(unsigned width)
{
    d->width = width;
}

unsigned Rich::width() const
{
    return d->width;
}

void Rich::setHeight(unsigned height)
{
    d->height = height;
}

unsigned Rich::height() const
{
    return d->height;
}

} // namespace qoembed
