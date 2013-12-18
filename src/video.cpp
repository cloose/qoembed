#include "video.h"

#include <QString>

namespace qoembed {

class VideoPrivate
{
public:
    VideoPrivate() : width(0), height(0) {}

    QString html;
    unsigned width;
    unsigned height;
};

Video::Video() :
    Response(),
    d(new VideoPrivate)
{
}

Video::Video(const Video &other) :
    Response(other)
{
    d = new VideoPrivate;
    d->html = other.d->html;
    d->width = other.d->width;
    d->height = other.d->height;
}

Video::~Video()
{
    delete d;
}

Video &Video::operator=(const Video &rhs)
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

QString Video::render() const
{
    return html();
}

void Video::setHtml(const QString &html)
{
    d->html = html;
}

QString Video::html() const
{
    return d->html;
}

void Video::setWidth(unsigned width)
{
    d->width = width;
}

unsigned Video::width() const
{
    return d->width;
}

void Video::setHeight(unsigned height)
{
    d->height = height;
}

unsigned Video::height() const
{
    return d->height;
}

} // namespace qoembed
