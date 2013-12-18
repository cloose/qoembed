#include "link.h"

#include <QString>

namespace qoembed {

QString Link::render() const
{
    // FIXME: pass original requested URL to response so we can create a HTML link here
    //        return QString("<a href=\"%1\">%2</a>".arg(requestUrl()).arg(title());
    return QString();
}

} // namespace qoembed
