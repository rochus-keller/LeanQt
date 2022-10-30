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
