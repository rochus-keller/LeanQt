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

#ifndef QT_NO_QOBJECT
#include <QObject>
#include <QTimer>
#include <QPointer>

class A : public QObject
{
public:
	A(QObject* p):QObject(p){}
	~A() { qDebug() << "A destructed"; }
};

class B : public QObject
{
public:
	B(QObject* p):QObject(p){}
	~B() { qDebug() << "B destructed"; }
};

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
    
#if 0 //ndef QT_NO_THREAD
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
	
	qDebug() << "translate" << A::tr("Ürgöl");
	
	QTimer t1;
	t1.setSingleShot(true);
	t1.connect(&t1,SIGNAL(timeout()),qApp,SLOT(quit()));
	t1.start(2000);

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
