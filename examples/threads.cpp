#include <QThread>
#include <QtDebug>
#include <QDateTime>

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


int main(int argc, char *argv[])
{
	TestThread a("A"), b("B"), c("C");
	a.start();
	b.start();
	c.start();
	a.wait();
	b.wait();
	c.wait();
	qDebug() << "threads done";
	return 0;
}
