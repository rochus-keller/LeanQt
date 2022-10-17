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
