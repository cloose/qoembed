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
    OEmbedManager manager;

    QSignalSpy spy(&manager, SIGNAL(finished(qoembed::Response*)));

    manager.fetch(Request::createForUrl(QUrl("http://www.youtube.com/watch?v=_4K3tsKa1Uc")));

    QVERIFY2(spy.wait(), "fetch request didn't finish after 5000 ms");

    QList<QVariant> args = spy.takeFirst();
    QVERIFY(args.at(0).canConvert<Response*>());
}

void OEmbedManagerTest::returnsResponseThatContainsResourceTypeVideoForYoutube()
{
    OEmbedManager manager;

    QSignalSpy spy(&manager, SIGNAL(finished(qoembed::Response*)));

    manager.fetch(Request::createForUrl(QUrl("http://www.youtube.com/watch?v=_4K3tsKa1Uc")));

    QVERIFY2(spy.wait(), "fetch request didn't finish after 5000 ms");

    QList<QVariant> args = spy.takeFirst();
    Response *response = args.at(0).value<Response*>();

    QVERIFY2(response != 0, "response is null");
    QCOMPARE(response->type(), QStringLiteral("video"));
}

QTEST_MAIN(OEmbedManagerTest)

#include "oembedmanagertest.moc"
