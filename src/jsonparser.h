#ifndef QOEMBED_JSONPARSER_H
#define QOEMBED_JSONPARSER_H

class QByteArray;

namespace qoembed {

class Response;

class JsonParser
{
public:
    JsonParser();

    Response *fromJson(const QByteArray &data);
};

} // namespace qoembed

#endif // QOEMBED_JSONPARSER_H
