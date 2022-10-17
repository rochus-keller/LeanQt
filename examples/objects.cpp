#include <QObject>
#include <QTimer>
#include <QPointer>
#include <QtDebug>
#include <QCoreApplication>

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

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationDomain("https://github.com/rochus-keller/LeanQt");
    app.setApplicationName("objects");
    
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
}

#include "objects.moc"

