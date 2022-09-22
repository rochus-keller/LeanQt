## Welcome to LeanQt - the lean, adaptable Qt version

LeanQt is a stripped-down Qt version which includes the essential features and is easy to build from source and to integrate with an application.

My primary motivation for LeanQt was to make my Oberon compiler (and also the IDE in future) easier to compile and deploy on all relevant platforms with as few dependencies as possible. Many of my tools are based on Qt 5, which is an excellent framework that provides all the necessary features in a platform-independent way. Qt 5 has low requirements for the C++ compiler and is available virtually on all platforms where there is a C++98 compiler. 

Unfortunately, there has been a certain proliferation over the years where Qt has been bloated with all sorts of features with questionable value. The standard binary installation of Qt swallows several gigabytes and requires a login to a commercial company server, which discourages many people. The non-essential features make the build even more complicated. The now initiated development with Qt 6 makes even higher demands on compiler and system, and follows a development that I cannot make sense of.

For LeanQt I used the code of Qt 5.6.3 which was the last Qt version available under both LGPL v2.1 and v3. Instead of qmake the BUSY build system (see https://github.com/rochus-keller/BUSY) is used, which was one of the reasons I implemented it. LeanQt has a different source tree structure compared to the original Qt toolkit; a lot of the original subdirectories (e.g. mkspecs, qmake) are no longer required; there are no longer separate subdirectories under corelib since each was depending on every other anyway. I also added additional configuration options so it is possible to use a minimal version even without the file engine and core application (see the BUSY file in the root for more information); many changes were necessary to the original source code for this, but the API is mostly the same and thus the original Qt documentation is still valid.

### State of development

This version is suited to successfully build and run the command line version of my Oberon+ compiler on x86 Linux, Windows and macOS, as well as macOS M1; other Linux architectures.

The following features are available: 

- bytearrays, strings, unicode
- localization
- collections, implicit sharing
- date/time, time zones
- variants/metatypes
- codecs: utf, simple, latin
- io device abstraction
- file engine
- text and data streams
- regexp
- logging
- md5 and sha1 hash
- geometry, json, xml
- rcc (resource compiler)
- threads

### Planned or work-in-progress features

- [ ] core objects and events, moc
- [ ] core mimetypes
- [ ] plugin support
- [ ] QtNetwork
- [ ] QtXml

### Long term plan

- [ ] QtGui
- [ ] QtWidgets
- [ ] printing
- [ ] concurrent
- [ ] serial port

### No support planned

- qmake
- statemachine
- other than minimal codecs
- animation
- dbus
- sql
- svg
- nfc
- bluetooth
- multimedia
- web and browser stuff
- testlib
- scripting, quick stuff
- qml
- all not mentioned add-ons 
- ios, winrt, wince, android, blackberry, nacl, vxworks, haiku

### How to build the Oberon+ command line compiler version with LeanQt

1. Create a new directory; we call it the root directory here
1. Download https://github.com/rochus-keller/Oberon/archive/refs/heads/master.zip and unpack it to the root directory; rename the resulting directory to "Oberon".
1. Download https://github.com/rochus-keller/PeLib/archive/refs/heads/OBX.zip and unpack it to the root directory; rename the resulting directory to "PeLib".
1. Download https://github.com/rochus-keller/MonoTools/archive/refs/heads/master.zip and unpack it to the root directory; rename the resulting directory to "MonoTools".
1. Download https://github.com/rochus-keller/LeanQt/archive/refs/heads/master.zip and unpack it to the root directory; rename the resulting directory to "LeanQt".
1. Download https://github.com/rochus-keller/BUSY/archive/refs/heads/master.zip and unpack it to the root directory; rename the resulting directory to "build".
1. Open a command line in the build directory and type `cc *.c -O2 -lm -O2 -o lua` or `cl /O2 /MD /Fe:lua.exe *.c` depending on whether you are on a Unix or Windows machine; wait a few seconds until the Lua executable is built.
1. Now type `lua build.lua ../Oberon`; wait a few minutes until the OBXMC executable is built; you find it in the output subdirectory.

### Additional Credits

Copyright (C) 2016 by The Qt Company Ltd. 
Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
Copyright (C) 1992-2005 Trolltech AS.
KDAB, https://www.kdab.com/kdab-contributions-to-qt-5-0-part-1/
The KDE Community, https://community.kde.org/Frameworks/Epics/Contributions_to_Qt5.
And many individual Qt contributors around the world (I didn't find a contributors list so far; please post a link if you have one, relating to Qt 4.0 to 5.6).

### Support

If you need support or would like to post issues or feature requests please use the Github issue list at https://github.com/rochus-keller/LeanQt/issues or send an email to the author.

