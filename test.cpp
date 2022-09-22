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

#ifndef QT_NO_THREADS

class TestThread : public QThread
{
public:
	QByteArray title;
	TestThread(const QByteArray& t):title(t){}
protected:
	void run()
	{
		QTextStream out(stdout);
		for( int i = 0; i < 10; i++ )
		{
			out << title << " " << QDateTime::currentDateTime().toString(Qt::ISODate) << " " << i << endl << flush;
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
    
#ifndef QT_NO_THREADS
	TestThread a("A"), b("B"), c("C");
	a.start();
	b.start();
	c.start();
	a.wait();
	b.wait();
	c.wait();
	qDebug() << "threads done";
#endif
  
    return 0;
}
