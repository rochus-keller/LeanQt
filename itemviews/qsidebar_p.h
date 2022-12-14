/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSIDEBAR_H
#define QSIDEBAR_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qurl.h>

#ifndef QT_NO_FILEDIALOG

#include <qlistwidget.h>
#include <qstandarditemmodel.h>
#include <qstyleditemdelegate.h>

QT_BEGIN_NAMESPACE

class QFileSystemModel;

class QSideBarDelegate : public QStyledItemDelegate
{
 public:
     QSideBarDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}
     void initStyleOption(QStyleOptionViewItem *option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class Q_AUTOTEST_EXPORT QUrlModel : public QStandardItemModel
{
    Q_OBJECT

public:
    enum Roles {
        UrlRole = Qt::UserRole + 1,
        EnabledRole = Qt::UserRole + 2
    };

    QUrlModel(QObject *parent = 0);

    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    QMimeData *mimeData(const QModelIndexList &indexes) const Q_DECL_OVERRIDE;
#ifndef QT_NO_DRAGANDDROP
    bool canDrop(QDragEnterEvent *event);
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) Q_DECL_OVERRIDE;
#endif
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) Q_DECL_OVERRIDE;

    void setUrls(const QList<QUrl> &list);
    void addUrls(const QList<QUrl> &urls, int row = -1, bool move = true);
    QList<QUrl> urls() const;
    void setFileSystemModel(QFileSystemModel *model);
    bool showFullPath;

private Q_SLOTS:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void layoutChanged();

private:
    void setUrl(const QModelIndex &index, const QUrl &url, const QModelIndex &dirIndex);
    void changed(const QString &path);
    void addIndexToWatch(const QString &path, const QModelIndex &index);
    QFileSystemModel *fileSystemModel;
    QList<QPair<QModelIndex, QString> > watching;
    QList<QUrl> invalidUrls;
};

class Q_AUTOTEST_EXPORT QSidebar : public QListView
{
    Q_OBJECT

Q_SIGNALS:
    void goToUrl(const QUrl &url);

public:
    QSidebar(QWidget *parent = 0);
    void setModelAndUrls(QFileSystemModel *model, const QList<QUrl> &newUrls);
    ~QSidebar();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setUrls(const QList<QUrl> &list) { urlModel->setUrls(list); }
    void addUrls(const QList<QUrl> &list, int row) { urlModel->addUrls(list, row); }
    QList<QUrl> urls() const { return urlModel->urls(); }

    void selectUrl(const QUrl &url);

protected:
    bool event(QEvent * e) Q_DECL_OVERRIDE;
    void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_DRAGANDDROP
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
#endif

private Q_SLOTS:
    void clicked(const QModelIndex &index);
#ifndef QT_NO_MENU
    void showContextMenu(const QPoint &position);
#endif
    void removeEntry();

private:
    QUrlModel *urlModel;
};

QT_END_NAMESPACE

#endif // QT_NO_FILEDIALOG

#endif // QSIDEBAR_H

