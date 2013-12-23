/*
 * Copyright (c) 2013, Christian Loose
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "xmlparser.h"

#include <QByteArray>
#include <QDebug>
#include <QDomDocument>

#include "link.h"
#include "photo.h"
#include "response.h"
#include "rich.h"
#include "video.h"

namespace qoembed {

XmlParser::XmlParser()
{
}

Response *XmlParser::fromXml(const QByteArray &data)
{
    QString errorMsg;
    int errorLine = 0;
    int errorColumn = 0;

    QDomDocument doc;
    doc.setContent(data, &errorMsg, &errorLine, &errorColumn);
//    qDebug() << data;
    qDebug() << errorMsg << errorLine << errorColumn;

    QDomElement root = doc.documentElement();

    QString type = findElement(root, "type").text();
    if (type == "video") {
        Video* video = new Video();
        fillCommonValues(root, video);

        video->setHtml(findElement(root, "html").text());
        QString width = findElement(root, "width").text();
        video->setWidth(width.toUInt());
        QString height = findElement(root, "height").text();
        video->setHeight(height.toUInt());

        return video;
    } else if (type == "rich") {
        Rich* rich = new Rich();
        fillCommonValues(root, rich);

        rich->setHtml(findElement(root, "html").text());
        QString width = findElement(root, "width").text();
        rich->setWidth(width.toUInt());
        QString height = findElement(root, "height").text();
        rich->setHeight(height.toUInt());

        return rich;
    } else if (type == "photo") {
        Photo* photo = new Photo();
        fillCommonValues(root, photo);

        photo->setUrl(findElement(root, "url").text());
        QString width = findElement(root, "width").text();
        photo->setWidth(width.toUInt());
        QString height = findElement(root, "height").text();
        photo->setHeight(height.toUInt());

        return photo;
    } else if (type == "link") {
        Link* link = new Link();
        fillCommonValues(root, link);
        return link;
    }

    Response *response = new Response();
    fillCommonValues(root, response);
    return response;
}

void XmlParser::fillCommonValues(const QDomElement &root, Response *response)
{
    response->setType(findElement(root, "type").text());
    response->setVersion(findElement(root, "version").text());
    response->setTitle(findElement(root, "title").text());
    response->setAuthorName(findElement(root, "author_name").text());
    response->setAuthorUrl(findElement(root, "author_url").text());
    response->setProviderName(findElement(root, "provider_name").text());
    response->setProviderUrl(findElement(root, "provider_url").text());
}

QDomElement XmlParser::findElement(const QDomElement &root, const QString &tagName) const
{
    QDomElement element = root.firstChildElement(tagName);

    // Providers like Slideshare use "author-name" instead of "author_name"
    if (element.isNull() && tagName.contains("_")) {
        element = root.firstChildElement(QString(tagName).replace("_", "-"));
    }

    return element;
}

} // namespace qoembed
