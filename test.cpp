#include <iostream>
#include <QByteArray>
#include <QString>
#include <QDateTime>
#include <QtDebug>
#include <QByteArrayList>
#include <QPoint>
#include <QVariant>
#include <QCoreApplication>
#include <QThread>
#include <QTextStream>
#include <QProcess>

#ifndef QT_NO_QOBJECT
#include <QObject>
#include <QTimer>
#include <QPointer>

class A : public QObject
{
	Q_OBJECT
public:
	A(QObject* p):QObject(p){}
	~A() { qDebug() << "A destructed"; }
signals:
	void sayHello();
};

class B : public QObject
{
	Q_OBJECT
public:
	B(QObject* p):QObject(p){}
	~B() { qDebug() << "B destructed"; }
public slots:
	void hello()
	{
		qDebug() << "hello from B";
	}
};
#include "test.moc"
#endif

#ifndef QT_NO_THREAD
class TestThread : public QThread
{
public:
	QByteArray title;
	TestThread(const QByteArray& t):title(t){}
protected:
	void run()
	{
		for( int i = 0; i < 10; i++ )
		{
			qDebug() << title << QDateTime::currentDateTime().toString(Qt::ISODate) << i;
			msleep( qrand() % 1000 );
		}
	} 
};
#endif

int main(int argc, char *argv[])
{
#ifndef QT_NO_COREAPPLICATION
    QCoreApplication app(argc, argv);
    app.setOrganizationDomain("https://github.com/rochus-keller/LeanQt");
    app.setApplicationName("test");
#endif

	QByteArray hello = "hello";
	hello = hello.toUpper();
	QString str = QString::fromUtf8("äöüÄÖÜ");
	QByteArrayList l;
	//QPoint p(33,44);
	//QVariant v = p;
	l << "alpha" << "beta" << "gamma";
	qDebug() << hello << QDateTime::currentDateTime().toString(Qt::ISODate) << str << l; // << v;
    std::cout << str.toUtf8().constData() << " Hello World " << hello.constData() << std::endl;
    
#ifndef QT_NO_PROCESS
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

#endif
    
#ifndef QT_NO_THREAD
	TestThread a("A"), b("B"), c("C");
	a.start();
	b.start();
	c.start();
	a.wait();
	b.wait();
	c.wait();
	qDebug() << "threads done";
#endif
 
#ifndef QT_NO_QOBJECT
	QPointer<A> ap = new A(0);
	QPointer<B> bp = new B(ap);
	
	A::connect(ap, SIGNAL(sayHello()), bp, SLOT(hello()));
	
	qDebug() << "translate" << A::tr("Ölförderung");
	
	QTimer t1;
	t1.setSingleShot(true);
	t1.connect(&t1,SIGNAL(timeout()),qApp,SLOT(quit()));
	t1.start(2000);
	
	ap->sayHello();

	QTimer t2;
	t2.setSingleShot(true);
	t2.connect(&t2,SIGNAL(timeout()),bp,SLOT(deleteLater()));
	t2.start(1000);

    int res = app.exec();
    qDebug() << "quitting";
    Q_ASSERT( !ap.isNull());
    Q_ASSERT( bp.isNull());
    return res;
#else
	return 0;
#endif
}
