#ifndef QTEXTBROWSER_P_H
#define QTEXTBROWSER_P_H

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

#include "qtextbrowser.h"
#include "qtextedit_p.h"
#include <qstack.h>

QT_BEGIN_NAMESPACE

class QTextBrowserPrivate : public QTextEditPrivate
{
    Q_DECLARE_PUBLIC(QTextBrowser)
public:
    inline QTextBrowserPrivate()
        : textOrSourceChanged(false), forceLoadOnSourceChange(false), openExternalLinks(false),
          openLinks(true)
#ifdef QT_KEYPAD_NAVIGATION
        , lastKeypadScrollValue(-1)
#endif
    {}

    void init();

    struct HistoryEntry {
        inline HistoryEntry()
            : hpos(0), vpos(0), focusIndicatorPosition(-1),
              focusIndicatorAnchor(-1) {}
        QUrl url;
        QString title;
        int hpos;
        int vpos;
        int focusIndicatorPosition, focusIndicatorAnchor;
    };

    HistoryEntry history(int i) const
    {
        if (i <= 0)
            if (-i < stack.count())
                return stack[stack.count()+i-1];
            else
                return HistoryEntry();
        else
            if (i <= forwardStack.count())
                return forwardStack[forwardStack.count()-i];
            else
                return HistoryEntry();
    }


    HistoryEntry createHistoryEntry() const;
    void restoreHistoryEntry(const HistoryEntry entry);

    QStack<HistoryEntry> stack;
    QStack<HistoryEntry> forwardStack;
    QUrl home;
    QUrl currentURL;

    QStringList searchPaths;

    /*flag necessary to give the linkClicked() signal some meaningful
      semantics when somebody connected to it calls setText() or
      setSource() */
    bool textOrSourceChanged;
    bool forceLoadOnSourceChange;

    bool openExternalLinks;
    bool openLinks;

#ifndef QT_NO_CURSOR
    QCursor oldCursor;
#endif

    QString findFile(const QUrl &name) const;

    inline void _q_documentModified()
    {
        textOrSourceChanged = true;
        forceLoadOnSourceChange = !currentURL.path().isEmpty();
    }

    void _q_activateAnchor(const QString &href);
    void _q_highlightLink(const QString &href);

    void setSource(const QUrl &url);

    // re-imlemented from QTextEditPrivate
    virtual QUrl resolveUrl(const QUrl &url) const Q_DECL_OVERRIDE;
    inline QUrl resolveUrl(const QString &url) const
    { return resolveUrl(QUrl(url)); }

#ifdef QT_KEYPAD_NAVIGATION
    void keypadMove(bool next);
    QTextCursor prevFocus;
    int lastKeypadScrollValue;
#endif
};


QT_END_NAMESPACE

#endif // QTEXTBROWSER_H
