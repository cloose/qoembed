#ifndef QOEMBED_LINK_H
#define QOEMBED_LINK_H

#include "qoembed_global.h"
#include "response.h"

namespace qoembed {

class QOEMBEDSHARED_EXPORT Link : public Response
{
public:
    virtual QString render() const;
};

} // namespace qoembed

#endif // QOEMBED_LINK_H
