#include <QString>
#include <QtTest>

#include <request.h>
using qoembed::Request;

class RequestTest : public QObject
{
    Q_OBJECT

public:
    RequestTest();

private Q_SLOTS:
    void holdsUrlPassedOnCreation();
    void returnsMaxWidthZeroIfNotProvided();
    void holdsMaxWidth();
    void returnsMaxHeightZeroIfNotProvided();
    void holdsMaxHeight();
    void returnsEmptyFormatIfNotProvided();
    void holdsFormat();
    void createsUrlQueryFromRequestData();
};

RequestTest::RequestTest()
{
}

void RequestTest::holdsUrlPassedOnCreation()
{
    QUrl url("http://example.com");
    Request request = Request::createForUrl(url);

    QCOMPARE(request.url(), url);
}

void RequestTest::returnsMaxWidthZeroIfNotProvided()
{
    QUrl url("http://example.com");
    Request request = Request::createForUrl(url);

    QVERIFY(request.maxWidth() == 0);
}

void RequestTest::holdsMaxWidth()
{
    QUrl url("http://example.com");
    unsigned maxWidth = 400;
    Request request = Request::createForUrl(url)
                              .withMaxWidth(maxWidth);

    QCOMPARE(request.maxWidth(), maxWidth);
}

void RequestTest::returnsMaxHeightZeroIfNotProvided()
{
    QUrl url("http://example.com");
    Request request = Request::createForUrl(url);

    QVERIFY(request.maxHeight() == 0);
}

void RequestTest::holdsMaxHeight()
{
    QUrl url("http://example.com");
    unsigned maxHeight = 400;
    Request request = Request::createForUrl(url)
                              .withMaxHeight(maxHeight);

    QCOMPARE(request.maxHeight(), maxHeight);
}

void RequestTest::returnsEmptyFormatIfNotProvided()
{
    QUrl url("http://example.com");
    Request request = Request::createForUrl(url);

    QVERIFY(request.format().isEmpty());
}

void RequestTest::holdsFormat()
{
    QUrl url("http://example.com");
    QString format("xml");
    Request request = Request::createForUrl(url)
                              .withFormat(format);

    QCOMPARE(request.format(), format);
}

void RequestTest::createsUrlQueryFromRequestData()
{
    QUrl url("http://example.com");
    unsigned maxWidth = 123;
    unsigned maxHeight = 456;
    QString format = "json";

    QString expectedQuery = QString("url=%1&maxwidth=%2&maxheight=%3&format=%4")
            .arg(QString(url.toEncoded()))
            .arg(maxWidth)
            .arg(maxHeight)
            .arg(format);

    Request request = Request::createForUrl(url)
                              .withMaxWidth(maxWidth)
                              .withMaxHeight(maxHeight)
                              .withFormat(format);

    QUrlQuery query = request.createQuery();

    QVERIFY(query.hasQueryItem("url"));
    QVERIFY(query.hasQueryItem("maxwidth"));
    QVERIFY(query.hasQueryItem("maxheight"));
    QVERIFY(query.hasQueryItem("format"));
    QCOMPARE(query.query(), expectedQuery);
}

QTEST_APPLESS_MAIN(RequestTest)

#include "requesttest.moc"
