#include <QtTest>

#include <typeinfo>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

#include <jsonparser.h>
#include <link.h>
#include <photo.h>
#include <response.h>
#include <rich.h>
#include <video.h>
using qoembed::JsonParser;
using qoembed::Response;

class JsonParserTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void defectIfEmptyByteArray();
    void defectIfEmptyJsonDocument();
    void returnsBasicResponseIfTypeMissing();
    void parsesLinkResponse();
    void parsesPhotoResponse();
    void parsesRichResponse();
    void parsesVideoResponse();
};

void JsonParserTest::defectIfEmptyByteArray()
{
    JsonParser parser;
    Response *response = parser.fromJson(QByteArray());

    QVERIFY2(response->isError(), qPrintable(QString("response type is %1").arg(response->type())));
}

void JsonParserTest::defectIfEmptyJsonDocument()
{
    QJsonDocument doc;

    JsonParser parser;
    Response *response = parser.fromJson(doc.toJson());

    QVERIFY2(response->isError(), qPrintable(QString("response type is %1").arg(response->type())));
}

void JsonParserTest::returnsBasicResponseIfTypeMissing()
{
    QJsonObject responseData;
    responseData.insert("version", QLatin1String("1.0"));

    JsonParser parser;
    Response *response = parser.fromJson(QJsonDocument(responseData).toJson());

    QVERIFY(typeid(*response) == typeid(qoembed::Response));
    QCOMPARE(response->type(), QString());
}

void JsonParserTest::parsesLinkResponse()
{
    QJsonObject responseData;
    responseData.insert("type", QLatin1String("link"));
    responseData.insert("version", QLatin1String("1.0"));

    JsonParser parser;
    Response *response = parser.fromJson(QJsonDocument(responseData).toJson());

    QVERIFY2(response->isLink(), qPrintable(QString("response type is %1").arg(response->type())));
    QVERIFY(typeid(*response) == typeid(qoembed::Link));
}

void JsonParserTest::parsesPhotoResponse()
{
    QJsonObject responseData;
    responseData.insert("type", QLatin1String("photo"));
    responseData.insert("version", QLatin1String("1.0"));

    JsonParser parser;
    Response *response = parser.fromJson(QJsonDocument(responseData).toJson());

    QVERIFY2(response->isPhoto(), qPrintable(QString("response type is %1").arg(response->type())));
    QVERIFY2(typeid(*response) == typeid(qoembed::Photo), typeid(*response).name());
}

void JsonParserTest::parsesRichResponse()
{
    QJsonObject responseData;
    responseData.insert("type", QLatin1String("rich"));
    responseData.insert("version", QLatin1String("1.0"));

    JsonParser parser;
    Response *response = parser.fromJson(QJsonDocument(responseData).toJson());

    QVERIFY2(response->isRich(), qPrintable(QString("response type is %1").arg(response->type())));
    QVERIFY2(typeid(*response) == typeid(qoembed::Rich), typeid(*response).name());
}

void JsonParserTest::parsesVideoResponse()
{
    QJsonObject responseData;
    responseData.insert("type", QLatin1String("video"));
    responseData.insert("version", QLatin1String("1.0"));

    JsonParser parser;
    Response *response = parser.fromJson(QJsonDocument(responseData).toJson());

    QVERIFY2(response->isVideo(), qPrintable(QString("response type is %1").arg(response->type())));
    QVERIFY2(typeid(*response) == typeid(qoembed::Video), typeid(*response).name());
}

QTEST_APPLESS_MAIN(JsonParserTest)

#include "jsonparsertest.moc"
