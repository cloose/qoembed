#ifndef QOEMBED_XMLPARSER_H
#define QOEMBED_XMLPARSER_H

class QByteArray;
class QDomElement;
class QString;

namespace qoembed {

class Response;

class XmlParser
{
public:
    XmlParser();

    Response *fromXml(const QByteArray &data);

private:
    void fillCommonValues(const QDomElement &root, Response *response);
    QDomElement findElement(const QDomElement &root, const QString &tagName) const;
};

} // namespace qoembed

#endif // QOEMBED_XMLPARSER_H
