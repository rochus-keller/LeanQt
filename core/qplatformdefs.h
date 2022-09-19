#ifndef _QPLATFORMDEFS_X_
#define _QPLATFORMDEFS_X_

/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2014 Intel Corporation.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt.
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#include "qglobal.h"
#include "qcompilerdetection.h"
#include "qsystemdetection.h"

#if defined(Q_OS_MACOS)
#include "qplatformdefs_mac.h"

#elif defined(Q_OS_DARWIN) && defined(Q_CC_GNU)
#include "qplatformdefs_darwin.h"

#elif defined(Q_OS_WIN32) && ( defined(Q_CC_MSVC) || defined(Q_CC_INTEL) )
#include "qplatformdefs_win32_msvc.h"

#elif defined(Q_OS_WIN32) && defined(Q_CC_GNU)
#include "qplatformdefs_win32_g++.h"

#elif defined(Q_OS_CYGWIN) && defined(Q_CC_GNU)
#include "qplatformdefs_cygwin_g++.h"

#elif defined(Q_OS_LINUX) && defined(Q_CC_CLANG)
#include "qplatformdefs_linux_clang.h"

#elif defined(Q_OS_LINUX) && defined(Q_CC_GNU)
#include "qplatformdefs_linux_g++.h"

#elif ( defined(Q_OS_FREEBSD) || defined(Q_OS_NETBSD) || defined(Q_OS_OPENBSD) ) && ( defined(Q_CC_CLANG) || defined(Q_CC_GNU) )
#include "qplatformdefs_bsd.h"

#else
#error "platform/compiler combination not supported"
#endif

#endif // 
