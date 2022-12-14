/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
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

#ifndef QUNICODETOOLS_P_H
#define QUNICODETOOLS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qchar.h>

QT_BEGIN_NAMESPACE

struct QCharAttributes
{
    uchar graphemeBoundary : 1;
    uchar wordBreak        : 1;
    uchar sentenceBoundary : 1;
    uchar lineBreak        : 1;
    uchar whiteSpace       : 1;
    uchar wordStart        : 1;
    uchar wordEnd          : 1;
    uchar mandatoryBreak   : 1;
};
Q_DECLARE_TYPEINFO(QCharAttributes, Q_PRIMITIVE_TYPE);

namespace QUnicodeTools {

// ### temporary
struct ScriptItem
{
    int position;
    int script;
};

enum CharAttributeOption {
    GraphemeBreaks = 0x01,
    WordBreaks = 0x02,
    SentenceBreaks = 0x04,
    LineBreaks = 0x08,
    WhiteSpaces = 0x10,
    DefaultOptionsCompat = GraphemeBreaks | LineBreaks | WhiteSpaces, // ### remove

    DontClearAttributes = 0x1000
};
Q_DECLARE_FLAGS(CharAttributeOptions, CharAttributeOption)

// attributes buffer has to have a length of string length + 1
Q_GUI_EXPORT void initCharAttributes(const ushort *string, int length,
                                      const ScriptItem *items, int numItems,
                                      QCharAttributes *attributes, CharAttributeOptions options = DefaultOptionsCompat);


Q_GUI_EXPORT void initScripts(const ushort *string, int length, uchar *scripts);

} // namespace QUnicodeTools

QT_END_NAMESPACE

#endif // QUNICODETOOLS_P_H
