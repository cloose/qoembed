#ifndef QOEMBED_PHOTO_H
#define QOEMBED_PHOTO_H

#include "qoembed_global.h"
#include "response.h"

namespace qoembed {

class PhotoPrivate;

class QOEMBEDSHARED_EXPORT Photo : public Response
{
public:
    Photo();
    Photo(const Photo &other);
    ~Photo();

    Photo &operator=(const Photo &rhs);

    virtual QString render() const;

    void setUrl(const QString &url);
    QString url() const;

    void setWidth(unsigned width);
    unsigned width() const;

    void setHeight(unsigned height);
    unsigned height() const;

private:
    PhotoPrivate *d;
};

} // namespace qoembed

#endif // QOEMBED_PHOTO_H
