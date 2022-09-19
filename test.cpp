#include <iostream>
#include <QByteArray>
#include <QString>
#include <QDateTime>
#include <QtDebug>
#include <QByteArrayList>
#include <QPoint>
#include <QVariant>

int main()
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
