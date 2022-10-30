#include <QImage>
#include <QtDebug>

int main(int argc, char *argv[])
{
	if( argc < 2 )
	{
		qCritical() << "argument expected";
		return -1;
	}
		
	QImage img;
	if( !img.load(argv[1]) )
	{
		qCritical() << "cannot load image" << argv[1];
		return -1;
	}
	QImage img2 = img.mirrored().rgbSwapped();
	if( !img2.save("out.bmp") )
	{
		qCritical() << "cannot save image out.bmp";
		return -1;
	}
	return 0;
}
