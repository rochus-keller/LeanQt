/****************************************************************************
**
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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

