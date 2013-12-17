#ifndef QOEMBED_XMLPARSER_H
#define QOEMBED_XMLPARSER_H

class QByteArray;

namespace qoembed {

class Response;

class XmlParser
{
public:
    XmlParser();

    Response *fromXml(const QByteArray &data);
};

} // namespace qoembed

#endif // QOEMBED_XMLPARSER_H
