/****************************************************************************
**
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QProcess>
#include <QtDebug>

int main(int argc, char *argv[])
{
#ifdef _WIN32
	QProcess::execute("dir");
#else
	QProcess::execute("ls");
#endif
	QProcess gzip;
    gzip.start("gzip", QStringList() << "-c");
    if (!gzip.waitForStarted())
    {
    	qCritical() << "waitForStarted returned false";
        return false;
    }

    gzip.write("Qt rocks!");
    gzip.closeWriteChannel();

    if (!gzip.waitForFinished())
    {
    	qCritical() << "waitForFinished returned false";
        return false;
    }
	QByteArray compressed = gzip.readAll();
    qDebug() << "compressed:" << compressed.toHex();
    
    gzip.start("gzip", QStringList() << "-d");
    if (!gzip.waitForStarted())
    {
    	qCritical() << "waitForStarted returned false";
        return false;
    }

    gzip.write(compressed);
    gzip.closeWriteChannel();

    if (!gzip.waitForFinished())
    {
    	qCritical() << "waitForFinished returned false";
        return false;
    }
    qDebug() << "decompressed:" << gzip.readAll();

	return 0;
}
