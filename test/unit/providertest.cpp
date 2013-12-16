#include <QNetworkProxyFactory>
#include <QString>
#include <QtTest>

#include <provider.h>
#include <request.h>
using qoembed::Provider;
using qoembed::Request;

class ProviderTest : public QObject
{
    Q_OBJECT

public:
    ProviderTest();

private Q_SLOTS:
    void initTestCase();

    void returnsNullForUnknownUrl();
    void returnsProviderForKnownUrl();
    void returnsDifferentProviderForDifferentUrls();
    void canFetchResource();
};

ProviderTest::ProviderTest()
{
}

void ProviderTest::initTestCase()
{
    QNetworkProxyFactory::setUseSystemConfiguration(true);
}

void ProviderTest::returnsNullForUnknownUrl()
{
    QScopedPointer<Provider> provider(Provider::createForUrl(QUrl("http://example.com")));
    QVERIFY2(provider.isNull(), "Returned provider is not null");
}

void ProviderTest::returnsProviderForKnownUrl()
{
    QScopedPointer<Provider> provider(Provider::createForUrl(QUrl("http://youtube.com/watch&v=DM3r2XDceM6A")));

    QVERIFY2(!provider.isNull(), "Returned provider is null");
    QCOMPARE(provider->endpoint(), QStringLiteral("http://www.youtube.com/oembed"));
}

void ProviderTest::returnsDifferentProviderForDifferentUrls()
{
    QScopedPointer<Provider> provider(Provider::createForUrl(QUrl("http://www.flickr.com/photos/bees/2341623661/")));

    QVERIFY2(!provider.isNull(), "Returned provider is null");
    QCOMPARE(provider->endpoint(), QStringLiteral("http://www.flickr.com/services/oembed/"));

    provider.reset(Provider::createForUrl(QUrl("http://www.slideshare.net/JuhaPeltomki/qt5-cplus-lyhytkurssi")));

    QVERIFY2(!provider.isNull(), "Returned provider is null");
    QCOMPARE(provider->endpoint(), QStringLiteral("https://www.slideshare.net/api/oembed/2"));
}

void ProviderTest::canFetchResource()
{
    QScopedPointer<Provider> provider(Provider::createForUrl(QUrl("http://www.slideshare.net/JuhaPeltomki/qt5-cplus-lyhytkurssi")));

    QSignalSpy spy(provider.data(), SIGNAL(finished(QString,QByteArray)));

    provider->fetch(Request::createForUrl(QUrl("http://www.slideshare.net/JuhaPeltomki/qt5-cplus-lyhytkurssi")));

    QVERIFY2(spy.wait(), "fetch request didn't finish after 5000 ms");
}

QTEST_MAIN(ProviderTest)

#include "providertest.moc"
