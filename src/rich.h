#ifndef QOEMBED_RICH_H
#define QOEMBED_RICH_H

#include "qoembed_global.h"
#include "response.h"

namespace qoembed {

class RichPrivate;

class QOEMBEDSHARED_EXPORT Rich : public Response
{
public:
    Rich();
    Rich(const Rich &other);
    ~Rich();

    Rich &operator=(const Rich &rhs);

    virtual QString render() const;

    void setHtml(const QString &html);
    QString html() const;

    void setWidth(unsigned width);
    unsigned width() const;

    void setHeight(unsigned height);
    unsigned height() const;

private:
    RichPrivate *d;
};

} // namespace qoembed

#endif // QOEMBED_RICH_H
