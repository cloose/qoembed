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
#include "jsonparser.h"

#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "link.h"
#include "photo.h"
#include "response.h"
#include "rich.h"
#include "video.h"

namespace qoembed {

JsonParser::JsonParser()
{
}

Response *JsonParser::fromJson(const QByteArray &data)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
//    qDebug() << data;
//    qDebug() << doc.isObject() << doc.isArray() << doc.isEmpty() << doc.isNull();
    qDebug() << error.errorString() << error.offset;

    QJsonObject obj = doc.object();

    QString type = obj.value("type").toString();
    if (type == "video") {
        Video* video = new Video();
        fillCommonValues(obj, video);

        video->setHtml(obj.value("html").toString());
        QString width = obj.value("width").toString();
        video->setWidth(width.toUInt());
        QString height = obj.value("height").toString();
        video->setHeight(height.toUInt());

        return video;
    } else if (type == "rich") {
        Rich* rich = new Rich();
        fillCommonValues(obj, rich);

        rich->setHtml(obj.value("html").toString());
        QString width = obj.value("width").toString();
        rich->setWidth(width.toUInt());
        QString height = obj.value("height").toString();
        rich->setHeight(height.toUInt());

        return rich;
    } else if (type == "photo") {
        Photo* photo = new Photo();
        fillCommonValues(obj, photo);

        photo->setUrl(obj.value("url").toString());
        QString width = obj.value("width").toString();
        photo->setWidth(width.toUInt());
        QString height = obj.value("height").toString();
        photo->setHeight(height.toUInt());

        return photo;
    } else if (type == "link") {
        Link* link = new Link();
        fillCommonValues(obj, link);
        return link;
    }

    Response *response = new Response();
    fillCommonValues(obj, response);
    return response;
}

void JsonParser::fillCommonValues(const QJsonObject &obj, Response *response)
{
    response->setType(obj.value("type").toString());
    response->setVersion(obj.value("version").toString());
    response->setTitle(obj.value("title").toString());
    response->setAuthorName(obj.value("author_name").toString());
    response->setAuthorUrl(obj.value("author_url").toString());
    response->setProviderName(obj.value("provider_name").toString());
    response->setProviderUrl(obj.value("provider_url").toString());
}

} // namespace qoembed
