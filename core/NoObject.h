#ifndef __NO_OBJECT__
#define __NO_OBJECT__

// ** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
// licensed under GPL/LGPL

#include <QtCore/qobjectdefs.h>
#include <qglobal.h>
#include <QScopedPointer>
#include <QList>
#include <QVariant>

class QObject;

typedef QList<QObject*> QObjectList;

class Q_CORE_EXPORT QObjectPrivate
{
    Q_DECLARE_PUBLIC(QObject)
public:
    QObjectPrivate();
    virtual ~QObjectPrivate();
    QObject *q_ptr;
    QObject *parent;
    QObjectList children;
    QString name;
    
    void setParent_helper(QObject *o);
};

class Q_CORE_EXPORT QObject
{
public:
    explicit QObject(QObject *parent= 0);
    virtual ~QObject();
    const QObjectList &children() const;
    void setObjectName(const QString & name);
    void setParent(QObject *parent);
    QObject * parent() const;
    void deleteLater();

    static QString tr(const char *sourceText, const char * = Q_NULLPTR, int = -1)
        { return QString::fromUtf8(sourceText); }

protected:
    QObject(QObjectPrivate &dd, QObject *parent = Q_NULLPTR);
    QScopedPointer<QObjectPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(QObject)
};

#endif // __NO_OBJECT__
