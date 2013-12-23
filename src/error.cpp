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
#include "error.h"

#include <QString>

namespace qoembed {

class ErrorPrivate
{
public:
    QString errorString;
};

Error::Error(const QString &errorString) :
    Response(),
    d(new ErrorPrivate)
{
    setType("error");
    setErrorString(errorString);
}

Error::Error(const Error &other) :
    Response(other)
{
    d = new ErrorPrivate;
    d->errorString = other.d->errorString;
}

Error::~Error()
{
    delete d;
}

Error &Error::operator=(const Error &rhs)
{
    // no self-assignment
    if (this != &rhs) {
        Response::operator =(rhs);
        d->errorString = rhs.d->errorString;
    }

    return *this;
}

QString Error::render() const
{
    return QString("<p>%1</p>").arg(errorString());
}

void Error::setErrorString(const QString &errorString)
{
    d->errorString = errorString;
}

QString Error::errorString() const
{
    return d->errorString;
}

} // namespace qoembed
