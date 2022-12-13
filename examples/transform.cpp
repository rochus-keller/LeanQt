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

#include <QImage>
#include <QBuffer>
#include <QtDebug>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		qCritical() << "argument expected";
		return -1;
	}
		
	QImage img;
#ifndef QT_NO_FILEENGINE
	if( !img.load(argv[1]) )
	{
		qCritical() << "cannot load image" << argv[1];
		return -1;
	}
#else
	FILE* in = fopen(argv[1],"rb");
	if( !in )
	{
		qCritical() << "cannot read file" << argv[1];
		return -1;
	}
	fseek(in, 0L, SEEK_END);
	const int len = ftell(in);
	rewind(in);
	QByteArray buf;
	buf.resize(len);
	fread(buf.data(), 1, len, in);
	fclose(in);
	if( !img.loadFromData(buf) )
	{
		qCritical() << "cannot load image" << argv[1];
		return -1;
	}	
#endif
	QImage img2 = img.mirrored().rgbSwapped();
#ifndef QT_NO_FILEENGINE
	if( !img2.save("out.bmp") )
	{
		qCritical() << "cannot save image out.bmp";
		return -1;
	}
#else
	FILE* out = fopen("out.bmp","wb");
	if( !out )
	{
		qCritical() << "cannot open file out.bmp for writing";
		return -1;
	}
	QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    img2.save(&buffer, "BMP"); 
	fwrite(ba.data(),1, ba.size(),out);
	fclose(out);
#endif
	return 0;
}
