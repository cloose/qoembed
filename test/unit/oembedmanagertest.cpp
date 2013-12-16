#include <QNetworkProxyFactory>
#include <QString>
#include <QtTest>

#include <oembedmanager.h>
#include <request.h>
using qoembed::OEmbedManager;
using qoembed::Request;

class OEmbedManagerTest : public QObject
{
    Q_OBJECT

public:
    OEmbedManagerTest();

private Q_SLOTS:
    void initTestCase();

    void canFetchResource();
};

OEmbedManagerTest::OEmbedManagerTest()
{
}

void OEmbedManagerTest::initTestCase()
{
    QNetworkProxyFactory::setUseSystemConfiguration(true);
}

void OEmbedManagerTest::canFetchResource()
{
    OEmbedManager manager;

    QSignalSpy spy(&manager, SIGNAL(finished()));

    manager.fetch(Request::createForUrl(QUrl("http://www.youtube.com/watch?v=_4K3tsKa1Uc")));

    QVERIFY2(spy.wait(), "fetch request didn't finish after 5000 ms");
}

QTEST_MAIN(OEmbedManagerTest)

#include "oembedmanagertest.moc"
