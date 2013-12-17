#ifndef QOEMBED_PROVIDER_H
#define QOEMBED_PROVIDER_H

#include "qoembed_global.h"

#include <QObject>
#include <QMap>
#include <QNetworkReply>
class QUrl;

namespace qoembed {

class ProviderPrivate;
class Request;

class QOEMBEDSHARED_EXPORT Provider : public QObject
{
    Q_OBJECT

public:
    ~Provider();

    void setEndpoint(const QString &endpoint);
    QString endpoint() const;

    void fetch(const Request &request);

    static Provider *createForUrl(const QUrl &url, QObject *parent = 0);

Q_SIGNALS:
    void error(QNetworkReply::NetworkError code, const QString &errorString);
    void finished(const QString &contentType, const QByteArray &content);

private Q_SLOTS:
    void replyFinished(QNetworkReply *reply);

private:
    explicit Provider(const QString &endpoint, QObject *parent = 0);
    Q_DISABLE_COPY(Provider)

    ProviderPrivate *d;

    static const QMap<QString, QString> urlSchemeToEndpoints;
};


} // namespace qoembed

#endif // QOEMBED_PROVIDER_H
