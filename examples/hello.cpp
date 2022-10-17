#include <QByteArray>
#include <QString>
#include <QtDebug>
#include <QDateTime>
#include <iostream>

int main(int argc, char *argv[])
{
	QByteArray hello = "hello";
	hello = hello.toUpper();
	QString str = QString::fromUtf8("äöüÄÖÜ");
	QByteArrayList l;
	//QPoint p(33,44);
	//QVariant v = p;
	l << "alpha" << "beta" << "gamma";
	qDebug() << hello << QDateTime::currentDateTime().toString(Qt::ISODate) << str << l; // << v;
    std::cout << str.toUtf8().constData() << " Hello World " << hello.constData() << std::endl;

	return 0;
}
