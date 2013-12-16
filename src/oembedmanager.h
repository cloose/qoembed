#ifndef QOEMBED_OEMBEDMANAGER_H
#define QOEMBED_OEMBEDMANAGER_H

#include "qoembed_global.h"

#include <QObject>

namespace qoembed {

class Request;

class QOEMBEDSHARED_EXPORT OEmbedManager : public QObject
{
    Q_OBJECT

public:
    explicit OEmbedManager(QObject *parent = 0);
    ~OEmbedManager();

    void fetch(const Request &request);

Q_SIGNALS:
    void finished();

private Q_SLOTS:
    void replyFinished(const QString &contentType, const QByteArray &content);
};

} // namespace qoembed

#endif // QOEMBED_OEMBEDMANAGER_H
