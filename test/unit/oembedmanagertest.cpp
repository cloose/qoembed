#include <QNetworkProxyFactory>
#include <QString>
#include <QtTest>

#include <oembedmanager.h>
#include <request.h>
#include <response.h>
using qoembed::OEmbedManager;
using qoembed::Request;
using qoembed::Response;

class OEmbedManagerTest : public QObject
{
    Q_OBJECT

public:
    OEmbedManagerTest();

private Q_SLOTS:
    void initTestCase();

    void canFetchResource();
    void returnsResponseThatContainsResourceTypeVideoForYoutube();
    void returnsResponseThatContainsResourceTypePhotoForFlicker();
    void returnsResponseThatContainsResourceTypeRichForSlideshare();
};

OEmbedManagerTest::OEmbedManagerTest()
{
    qRegisterMetaType<qoembed::Response*>();
}

void OEmbedManagerTest::initTestCase()
{
    QNetworkProxyFactory::setUseSystemConfiguration(true);
}

void OEmbedManagerTest::canFetchResource()
{
#if 0
    OEmbedManager manager;

    QSignalSpy spy(&manager, SIGNAL(finished(qoembed::Response*)));

    manager.fetch(Request::createForUrl(QUrl("http://www.youtube.com/watch?v=_4K3tsKa1Uc")));

    QVERIFY2(spy.wait(), "fetch request didn't finish after 5000 ms");

    QList<QVariant> args = spy.takeFirst();
    QVERIFY(args.at(0).canConvert<Response*>());
#endif
}

void OEmbedManagerTest::returnsResponseThatContainsResourceTypeVideoForYoutube()
{
#if 0
    OEmbedManager manager;

    QSignalSpy spy(&manager, SIGNAL(finished(qoembed::Response*)));

    manager.fetch(Request::createForUrl(QUrl("http://www.youtube.com/watch?v=_4K3tsKa1Uc")));

    QVERIFY2(spy.wait(), "fetch request didn't finish after 5000 ms");

    QList<QVariant> args = spy.takeFirst();
    Response *response = args.at(0).value<Response*>();

    QVERIFY2(response != 0, "response is null");
    QVERIFY(response->isVideo());
    QCOMPARE(response->type(), QStringLiteral("video"));
#endif
}

void OEmbedManagerTest::returnsResponseThatContainsResourceTypePhotoForFlicker()
{
    OEmbedManager manager;

    QSignalSpy spy(&manager, SIGNAL(finished(qoembed::Response*)));

    manager.fetch(Request::createForUrl(QUrl("http://www.flickr.com/photos/bees/2341623661/")));

    QVERIFY2(spy.wait(), "fetch request didn't finish after 5000 ms");

    QList<QVariant> args = spy.takeFirst();
    Response *response = args.at(0).value<Response*>();

    QVERIFY2(response != 0, "response is null");
    QVERIFY(response->isPhoto());
    QCOMPARE(response->type(), QStringLiteral("photo"));
}

void OEmbedManagerTest::returnsResponseThatContainsResourceTypeRichForSlideshare()
{
    OEmbedManager manager;

    QSignalSpy spy(&manager, SIGNAL(finished(qoembed::Response*)));

    manager.fetch(Request::createForUrl(QUrl("http://www.slideshare.net/JuhaPeltomki/qt5-cplus-lyhytkurssi")));

    QVERIFY2(spy.wait(), "fetch request didn't finish after 5000 ms");

    QList<QVariant> args = spy.takeFirst();
    Response *response = args.at(0).value<Response*>();

    QVERIFY2(response != 0, "response is null");
    QVERIFY(response->isRich());
    QCOMPARE(response->type(), QStringLiteral("rich"));
}

QTEST_MAIN(OEmbedManagerTest)

#include "oembedmanagertest.moc"
