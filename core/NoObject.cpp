// ** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
// licensed under GPL/LGPL

#include "NoObject.h"

QObjectPrivate::QObjectPrivate():q_ptr(0),parent(0)
{

}

QObjectPrivate::~QObjectPrivate()
{

}

QObjectPrivate *QObjectPrivate::get(QObject *o)
{
    return o->d_func();
}

void QObjectPrivate::setParent_helper(QObject *o)
{
	Q_Q(QObject);
	if (o == parent)
	    return;
	if (parent) {
	    QObjectPrivate *parentD = parent->d_func();
    	const int index = parentD->children.indexOf(q);
	    parentD->children.removeAt(index);
	}
	parent = o;
	if (parent) {
	    parent->d_func()->children.append(q);
	}
}

QObject::QObject(QObject *parent):d_ptr(new QObjectPrivate)
{
    d_ptr->q_ptr = this;
    if (parent)
       setParent(parent);	
}

QObject::QObject(QObjectPrivate &dd, QObject *parent):d_ptr(&dd)
{
    d_ptr->q_ptr = this;
    if (parent)
       setParent(parent);
}
 
QObject::~QObject()
{
	foreach( QObject* sub, d_ptr->children )
		delete sub;
}

const QObjectList & QObject::children() const
{
	return d_ptr->children;
}

void QObject::setObjectName(const QString & name)
{
	d_ptr->name = name;
}

QString QObject::objectName() const
{
    return d_ptr->name;
}

void QObject::setParent(QObject *parent)
{
    Q_D(QObject);
    d->setParent_helper(parent);
}

QObject * QObject::parent() const
{
	return d_ptr->parent;
}

void QObject::deleteLater()
{
	delete this;
}
