#ifndef QOEMBED_JSONPARSER_H
#define QOEMBED_JSONPARSER_H

class QByteArray;
class QJsonObject;

namespace qoembed {

class Response;

class JsonParser
{
public:
    JsonParser();

    Response *fromJson(const QByteArray &data);

private:
    void fillCommonValues(const QJsonObject &obj, Response *response);
};

} // namespace qoembed

#endif // QOEMBED_JSONPARSER_H
