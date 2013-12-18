#ifndef QOEMBED_VIDEO_H
#define QOEMBED_VIDEO_H

#include "qoembed_global.h"
#include "response.h"

namespace qoembed {

class VideoPrivate;

class QOEMBEDSHARED_EXPORT Video : public Response
{
public:
    Video();
    Video(const Video &other);
    ~Video();

    Video &operator=(const Video &rhs);

    void setHtml(const QString &html);
    QString html() const;

    void setWidth(unsigned width);
    unsigned width() const;

    void setHeight(unsigned height);
    unsigned height() const;

private:
    VideoPrivate *d;
};

} // namespace qoembed

#endif // QOEMBED_VIDEO_H
