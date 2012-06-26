#ifndef QT_BOOTSTRAPPED
/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

// Palm -->

/* Enable WebOS specific code */
#ifndef QT_WEBOS
#define QT_WEBOS
#endif

/* Compiler features */
#ifndef QT_NO_EXCEPTIONS
#define QT_NO_EXCEPTIONS
#endif

/*#ifndef QT_NO_DYNAMIC_CAST
#define QT_NO_DYNAMIC_CAST
#endif
*/

/* Dialogs */
#ifndef QT_NO_COLORDIALOG
#  define QT_NO_COLORDIALOG
#endif
#ifndef QT_NO_ERRORMESSAGE
#  define QT_NO_ERRORMESSAGE
#endif
#ifndef QT_NO_FILEDIALOG
#  define QT_NO_FILEDIALOG
#endif
#ifndef QT_NO_FONTDIALOG
#  define QT_NO_FONTDIALOG
#endif
#ifndef QT_NO_INPUTDIALOG
#  define QT_NO_INPUTDIALOG
#endif
#ifndef QT_NO_MESSAGEBOX
#  define QT_NO_MESSAGEBOX
#endif
#ifndef QT_NO_PRINTDIALOG
#  define QT_NO_PRINTDIALOG
#endif
#ifndef QT_NO_PRINTPREVIEWDIALOG
#  define QT_NO_PRINTPREVIEWDIALOG
#endif
#ifndef QT_NO_PROGRESSDIALOG
#  define QT_NO_PROGRESSDIALOG
#endif
#ifndef QT_NO_TABDIALOG
#  define QT_NO_TABDIALOG
#endif
#ifndef QT_NO_WIZARD
#  define QT_NO_WIZARD
#endif

/* File I/O */
#ifndef QT_NO_DOM
#  define QT_NO_DOM
#endif

/* Fonts */
#ifndef QT_NO_QWS_QPF
#  define QT_NO_QWS_QPF
#endif
#ifndef QT_NO_QWS_QPF2
#  define QT_NO_QWS_QPF2
#endif

/* Gui */
#ifndef QT_NO_SOFTKEYMANAGER
#  define QT_NO_SOFTKEYMANAGER
#endif

/* Images */
#ifndef QT_NO_IMAGEFORMAT_PPM
#  define QT_NO_IMAGEFORMAT_PPM
#endif
#ifndef QT_NO_IMAGEFORMAT_XBM
#  define QT_NO_IMAGEFORMAT_XBM
#endif
#ifdef QT_NO_IMAGEFORMAT_XPM
#  undef QT_NO_IMAGEFORMAT_XPM
#endif
#ifndef QT_NO_IMAGE_TEXT
#  define QT_NO_IMAGE_TEXT
#endif
#ifndef QT_NO_MOVIE
#  define QT_NO_MOVIE
#endif

/* ItemViews */
#ifndef QT_NO_ITEMVIEWS
#  define QT_NO_ITEMVIEWS
#endif
#ifndef QT_NO_DATAWIDGETMAPPER
#  define QT_NO_DATAWIDGETMAPPER
#endif
#ifndef QT_NO_DIRMODEL
#  define QT_NO_DIRMODEL
#endif
#ifndef QT_NO_LISTVIEW
#  define QT_NO_LISTVIEW
#endif
#ifndef QT_NO_COLUMNVIEW
#  define QT_NO_COLUMNVIEW
#endif
#ifndef QT_NO_PROXYMODEL
#  define QT_NO_PROXYMODEL
#endif
#ifndef QT_NO_SORTFILTERPROXYMODEL
#  define QT_NO_SORTFILTERPROXYMODEL
#endif
#ifndef QT_NO_STANDARDITEMMODEL
#  define QT_NO_STANDARDITEMMODEL
#endif
#ifndef QT_NO_STRINGLISTMODEL
#  define QT_NO_STRINGLISTMODEL
#endif
#ifndef QT_NO_TABLEVIEW
#  define QT_NO_TABLEVIEW
#endif
#ifndef QT_NO_TREEVIEW
#  define QT_NO_TREEVIEW
#endif

/* Kernel */
/*#ifndef QT_NO_CLIPBOARD
#  define QT_NO_CLIPBOARD
#endif*/
#ifndef QT_NO_CSSPARSER
#  define QT_NO_CSSPARSER
#endif
#ifndef QT_NO_CURSOR
#  define QT_NO_CURSOR
#endif
#ifndef QT_NO_SESSIONMANAGER
#  define QT_NO_SESSIONMANAGER
#endif
#ifndef QT_NO_SOUND
#  define QT_NO_SOUND
#endif
#ifndef QT_NO_TABLETEVENT
#  define QT_NO_TABLETEVENT
#endif
#ifndef QT_NO_TEXTHTMLPARSER
#  define QT_NO_TEXTHTMLPARSER
#endif
#ifdef QT_NO_WHEELEVENT
#  undef QT_NO_WHEELEVENT
#endif

/* Networking */
//#ifndef QT_NO_COP
//#  define QT_NO_COP
//#endif
//#ifndef QT_NO_NETWORKPROXY
//#  define QT_NO_NETWORKPROXY
//#endif
//#ifndef QT_NO_SOCKS5
//#  define QT_NO_SOCKS5
//#endif
//#ifndef QT_NO_UDPSOCKET
//#  define QT_NO_UDPSOCKET
//#endif
#ifndef QT_NO_FTP
#  define QT_NO_FTP
#endif

/* Painting */
#ifndef QT_NO_PICTURE
#  define QT_NO_PICTURE
#endif
#ifndef QT_NO_PRINTER
#  define QT_NO_PRINTER
#endif
#ifndef QT_NO_CUPS
#  define QT_NO_CUPS
#endif

/* Phonon */
#ifndef QT_NO_PHONON_ABSTRACTMEDIASTREAM
#  define QT_NO_PHONON_ABSTRACTMEDIASTREAM
#endif
#ifndef QT_NO_PHONON_AUDIOCAPTURE
#  define QT_NO_PHONON_AUDIOCAPTURE
#endif
#ifndef QT_NO_PHONON_EFFECT
#  define QT_NO_PHONON_EFFECT
#endif
#ifndef QT_NO_PHONON_MEDIACONTROLLER
#  define QT_NO_PHONON_MEDIACONTROLLER
#endif
#ifndef QT_NO_PHONON_OBJECTDESCRIPTIONMODEL
#  define QT_NO_PHONON_OBJECTDESCRIPTIONMODEL
#endif
#ifndef QT_NO_PHONON_PLATFORMPLUGIN
#  define QT_NO_PHONON_PLATFORMPLUGIN
#endif
#ifndef QT_NO_PHONON_SEEKSLIDER
#  define QT_NO_PHONON_SEEKSLIDER
#endif
#ifndef QT_NO_PHONON_SETTINGSGROUP
#  define QT_NO_PHONON_SETTINGSGROUP
#endif
#ifndef QT_NO_PHONON_VIDEO
#  define QT_NO_PHONON_VIDEO
#endif
#ifndef QT_NO_PHONON_VOLUMESLIDER
#  define QT_NO_PHONON_VOLUMESLIDER
#endif

/* Qt for Embedded Linux */
#ifndef QT_NO_QWSEMBEDWIDGET
#  define QT_NO_QWSEMBEDWIDGET
#endif
#ifndef QT_NO_QWS_ALPHA_CURSOR
#  define QT_NO_QWS_ALPHA_CURSOR
#endif
#ifndef QT_NO_QWS_DECORATION_DEFAULT
#  define QT_NO_QWS_DECORATION_DEFAULT
#endif
#ifndef QT_NO_QWS_MULTIPROCESS
#  define QT_NO_QWS_MULTIPROCESS
#endif
#ifndef QT_NO_QWS_TRANSFORMED
#  define QT_NO_QWS_TRANSFORMED
#endif
#ifndef QT_NO_QWS_VNC
#  define QT_NO_QWS_VNC
#endif

/* SVG */
#ifndef QT_NO_SVG
#  define QT_NO_SVG
#endif
#ifndef QT_NO_GRAPHICSSVGITEM
#  define QT_NO_GRAPHICSSVGITEM
#endif
#ifndef QT_NO_SVGGENERATOR
#  define QT_NO_SVGGENERATOR
#endif
#ifndef QT_NO_SVGRENDERER
#  define QT_NO_SVGRENDERER
#endif
#ifndef QT_NO_SVGWIDGET
#  define QT_NO_SVGWIDGET
#endif
/* Styles */
#ifndef QT_NO_STYLE_MOTIF
#  define QT_NO_STYLE_MOTIF
#endif

/* Utilities */
#ifndef QT_NO_ACCESSIBILITY
#  define QT_NO_ACCESSIBILITY
#endif
#ifndef QT_NO_COMPLETER
#  define QT_NO_COMPLETER
#endif
#ifndef QT_NO_DESKTOPSERVICES
#  define QT_NO_DESKTOPSERVICES
#endif
#ifdef QT_NO_SCRIPT
#error QT Declarative requires QT Script, disabled by QT_NO_SCRIPT
#endif
#ifndef QT_NO_SYSTEMTRAYICON
#  define QT_NO_SYSTEMTRAYICON
#endif
#ifndef QT_NO_UNDOCOMMAND
#  define QT_NO_UNDOCOMMAND
#endif
#ifndef QT_NO_UNDOGROUP
#  define QT_NO_UNDOGROUP
#endif
#ifndef QT_NO_UNDOSTACK
#  define QT_NO_UNDOSTACK
#endif
#ifndef QT_NO_UNDOVIEW
#  define QT_NO_UNDOVIEW
#endif

/* Widgets */
#ifndef QT_NO_GROUPBOX
#  define QT_NO_GROUPBOX
#endif
#ifndef QT_NO_BUTTONGROUP
#  define QT_NO_BUTTONGROUP
#endif
#ifndef QT_NO_LCDNUMBER
#  define QT_NO_LCDNUMBER
#endif
#ifndef QT_NO_LINEEDIT
// required for QDeclarative #  define QT_NO_LINEEDIT
#endif
#ifndef QT_NO_COMBOBOX
#  define QT_NO_COMBOBOX
#endif
#ifndef QT_NO_FONTCOMBOBOX
#  define QT_NO_FONTCOMBOBOX
#endif
#ifndef QT_NO_SPINBOX
#  define QT_NO_SPINBOX
#endif
#ifndef QT_NO_CALENDARWIDGET
#  define QT_NO_CALENDARWIDGET
#endif
#ifndef QT_NO_DATETIMEEDIT
#  define QT_NO_DATETIMEEDIT
#endif
#ifndef QT_NO_LISTWIDGET
#  define QT_NO_LISTWIDGET
#endif
#ifndef QT_NO_MENU
#  define QT_NO_MENU
#endif
#ifndef QT_NO_CONTEXTMENU
#  define QT_NO_CONTEXTMENU
#endif
#ifndef QT_NO_MAINWINDOW
#  define QT_NO_MAINWINDOW
#endif
#ifndef QT_NO_DOCKWIDGET
#  define QT_NO_DOCKWIDGET
#endif
#ifndef QT_NO_TOOLBAR
#  define QT_NO_TOOLBAR
#endif
#ifndef QT_NO_MENUBAR
#  define QT_NO_MENUBAR
#endif
#ifndef QT_NO_WORKSPACE
#  define QT_NO_WORKSPACE
#endif
#ifndef QT_NO_PROGRESSBAR
#  define QT_NO_PROGRESSBAR
#endif
#ifndef QT_NO_RESIZEHANDLER
#  define QT_NO_RESIZEHANDLER
#endif
#ifndef QT_NO_RUBBERBAND
#  define QT_NO_RUBBERBAND
#endif
#ifndef QT_NO_SPLITTER
#  define QT_NO_SPLITTER
#endif
/*#ifndef QT_NO_SIGNALMAPPER
#  define QT_NO_SIGNALMAPPER
#endif*/
#ifndef QT_NO_SIZEGRIP
#  define QT_NO_SIZEGRIP
#endif
#ifndef QT_NO_DIAL
#  define QT_NO_DIAL
#endif
#ifndef QT_NO_PRINTPREVIEWWIDGET
#  define QT_NO_PRINTPREVIEWWIDGET
#endif
#ifndef QT_NO_MDIAREA
#  define QT_NO_MDIAREA
#endif
#ifndef QT_NO_TEXTEDIT
#  define QT_NO_TEXTEDIT
#endif
#ifndef QT_NO_SYNTAXHIGHLIGHTER
#  define QT_NO_SYNTAXHIGHLIGHTER
#endif
#ifndef QT_NO_TEXTBROWSER
#  define QT_NO_TEXTBROWSER
#endif
#ifndef QT_NO_SPINWIDGET
#  define QT_NO_SPINWIDGET
#endif
#ifndef QT_NO_SPLASHSCREEN
#  define QT_NO_SPLASHSCREEN
#endif
#ifndef QT_NO_STACKEDWIDGET
#  define QT_NO_STACKEDWIDGET
#endif
#ifndef QT_NO_TABWIDGET
#  define QT_NO_TABWIDGET
#endif
#ifndef QT_NO_STATUSBAR
#  define QT_NO_STATUSBAR
#endif
#ifndef QT_NO_STATUSTIP
#  define QT_NO_STATUSTIP
#endif
#ifndef QT_NO_TABLEWIDGET
#  define QT_NO_TABLEWIDGET
#endif
#ifndef QT_NO_TOOLBUTTON
#  define QT_NO_TOOLBUTTON
#endif
#ifndef QT_NO_TABBAR
#  define QT_NO_TABBAR
#endif
#ifndef QT_NO_TOOLBOX
#  define QT_NO_TOOLBOX
#endif
#ifndef QT_NO_WHATSTHIS
#  define QT_NO_WHATSTHIS
#endif
#ifndef QT_NO_TOOLTIP
#  define QT_NO_TOOLTIP
#endif
#ifndef QT_NO_TREEWIDGET
#  define QT_NO_TREEWIDGET
#endif
#ifndef QT_NO_VALIDATOR
#  define QT_NO_VALIDATOR
#endif

#ifndef QT_NO_IDENTITYPROXYMODEL
#define QT_NO_IDENTITYPROXYMODEL
#endif

/* Windows */
#ifndef QT_NO_WIN_ACTIVEQT
#  define QT_NO_WIN_ACTIVEQT
#endif

// Desktop specific flags
#if !defined(PALM_DEVICE)
#undef QT_NO_IMAGEFORMAT_XPM
#undef QT_NO_CURSOR
#undef QT_NO_WHEELEVENT
#undef QT_NO_LINEEDIT
#endif

// <-- Palm
#endif

/* Qt Edition */
#ifndef QT_EDITION
#  define QT_EDITION QT_EDITION_OPENSOURCE
#endif

/* Machine byte-order */
#define Q_BIG_ENDIAN 4321
#define Q_LITTLE_ENDIAN 1234
#define QT_BUILD_KEY "arm linux g++"
#define QT_BUILD_KEY_COMPAT3 "armv6 linux g++"

#ifdef QT_BOOTSTRAPPED
#define Q_BYTE_ORDER Q_LITTLE_ENDIAN
#else
#define Q_BYTE_ORDER Q_LITTLE_ENDIAN
#endif
/* Machine Architecture */
#ifndef QT_BOOTSTRAPPED
# define QT_ARCH_ARM
#else
# define QT_ARCH_I386
#endif
/* Compile time features */
#define QT_LARGEFILE_SUPPORT 64
#define QT_POINTER_SIZE 4

#ifndef QT_BOOTSTRAPPED

#if defined(QT_NO_ACCESSIBILITY) && defined(QT_ACCESSIBILITY)
# undef QT_NO_ACCESSIBILITY
#elif !defined(QT_NO_ACCESSIBILITY) && !defined(QT_ACCESSIBILITY)
# define QT_NO_ACCESSIBILITY
#endif

#if defined(QT_NO_ALSA) && defined(QT_ALSA)
# undef QT_NO_ALSA
#elif !defined(QT_NO_ALSA) && !defined(QT_ALSA)
# define QT_NO_ALSA
#endif

#if defined(QT_NO_CUPS) && defined(QT_CUPS)
# undef QT_NO_CUPS
#elif !defined(QT_NO_CUPS) && !defined(QT_CUPS)
# define QT_NO_CUPS
#endif

#if defined(QT_NO_DBUS) && defined(QT_DBUS)
# undef QT_NO_DBUS
#elif !defined(QT_NO_DBUS) && !defined(QT_DBUS)
# define QT_NO_DBUS
#endif

#if defined(QT_NO_EGL) && defined(QT_EGL)
# undef QT_NO_EGL
#elif !defined(QT_NO_EGL) && !defined(QT_EGL)
# define QT_NO_EGL
#endif

#if defined(QT_NO_EXCEPTIONS) && defined(QT_EXCEPTIONS)
# undef QT_NO_EXCEPTIONS
#elif !defined(QT_NO_EXCEPTIONS) && !defined(QT_EXCEPTIONS)
# define QT_NO_EXCEPTIONS
#endif

#if defined(QT_NO_GSTREAMER) && defined(QT_GSTREAMER)
# undef QT_NO_GSTREAMER
#elif !defined(QT_NO_GSTREAMER) && !defined(QT_GSTREAMER)
# define QT_NO_GSTREAMER
#endif

#if defined(QT_NO_GUI) && defined(QT_GUI)
# undef QT_NO_GUI
#elif !defined(QT_NO_GUI) && !defined(QT_GUI)
# define QT_NO_GUI
#endif

#if defined(QT_NO_ICD) && defined(QT_ICD)
# undef QT_NO_ICD
#elif !defined(QT_NO_ICD) && !defined(QT_ICD)
# define QT_NO_ICD
#endif

#if defined(QT_NO_ICONV) && defined(QT_ICONV)
# undef QT_NO_ICONV
#elif !defined(QT_NO_ICONV) && !defined(QT_ICONV)
# define QT_NO_ICONV
#endif

#if defined(QT_NO_IMAGEFORMAT_JPEG) && defined(QT_IMAGEFORMAT_JPEG)
# undef QT_NO_IMAGEFORMAT_JPEG
#elif !defined(QT_NO_IMAGEFORMAT_JPEG) && !defined(QT_IMAGEFORMAT_JPEG)
# define QT_NO_IMAGEFORMAT_JPEG
#endif

#if defined(QT_NO_IMAGEFORMAT_MNG) && defined(QT_IMAGEFORMAT_MNG)
# undef QT_NO_IMAGEFORMAT_MNG
#elif !defined(QT_NO_IMAGEFORMAT_MNG) && !defined(QT_IMAGEFORMAT_MNG)
# define QT_NO_IMAGEFORMAT_MNG
#endif

#if defined(QT_NO_IMAGEFORMAT_TIFF) && defined(QT_IMAGEFORMAT_TIFF)
# undef QT_NO_IMAGEFORMAT_TIFF
#elif !defined(QT_NO_IMAGEFORMAT_TIFF) && !defined(QT_IMAGEFORMAT_TIFF)
# define QT_NO_IMAGEFORMAT_TIFF
#endif

#if defined(QT_NO_MULTIMEDIA) && defined(QT_MULTIMEDIA)
# undef QT_NO_MULTIMEDIA
#elif !defined(QT_NO_MULTIMEDIA) && !defined(QT_MULTIMEDIA)
# define QT_NO_MULTIMEDIA
#endif

#if defined(QT_NO_NAS) && defined(QT_NAS)
# undef QT_NO_NAS
#elif !defined(QT_NO_NAS) && !defined(QT_NAS)
# define QT_NO_NAS
#endif

#if defined(QT_NO_NIS) && defined(QT_NIS)
# undef QT_NO_NIS
#elif !defined(QT_NO_NIS) && !defined(QT_NIS)
# define QT_NO_NIS
#endif

#if defined(QT_NO_OPENSSL) && defined(QT_OPENSSL)
# undef QT_NO_OPENSSL
#elif !defined(QT_NO_OPENSSL) && !defined(QT_OPENSSL)
# define QT_NO_OPENSSL
#endif

#if defined(QT_NO_OPENVG) && defined(QT_OPENVG)
# undef QT_NO_OPENVG
#elif !defined(QT_NO_OPENVG) && !defined(QT_OPENVG)
# define QT_NO_OPENVG
#endif

#if defined(QT_NO_PHONON) && defined(QT_PHONON)
# undef QT_NO_PHONON
#elif !defined(QT_NO_PHONON) && !defined(QT_PHONON)
# define QT_NO_PHONON
#endif

#if defined(QT_NO_PULSEAUDIO) && defined(QT_PULSEAUDIO)
# undef QT_NO_PULSEAUDIO
#elif !defined(QT_NO_PULSEAUDIO) && !defined(QT_PULSEAUDIO)
# define QT_NO_PULSEAUDIO
#endif

#if defined(QT_NO_QWS_QPF) && defined(QT_QWS_QPF)
# undef QT_NO_QWS_QPF
#elif !defined(QT_NO_QWS_QPF) && !defined(QT_QWS_QPF)
# define QT_NO_QWS_QPF
#endif

#if defined(QT_NO_QWS_QPF2) && defined(QT_QWS_QPF2)
# undef QT_NO_QWS_QPF2
#elif !defined(QT_NO_QWS_QPF2) && !defined(QT_QWS_QPF2)
# define QT_NO_QWS_QPF2
#endif

#if defined(QT_NO_S60) && defined(QT_S60)
# undef QT_NO_S60
#elif !defined(QT_NO_S60) && !defined(QT_S60)
# define QT_NO_S60
#endif

#if defined(QT_NO_SCRIPTTOOLS) && defined(QT_SCRIPTTOOLS)
# undef QT_NO_SCRIPTTOOLS
#elif !defined(QT_NO_SCRIPTTOOLS) && !defined(QT_SCRIPTTOOLS)
# define QT_NO_SCRIPTTOOLS
#endif

#if defined(QT_NO_STYLE_GTK) && defined(QT_STYLE_GTK)
# undef QT_NO_STYLE_GTK
#elif !defined(QT_NO_STYLE_GTK) && !defined(QT_STYLE_GTK)
# define QT_NO_STYLE_GTK
#endif

#if defined(QT_NO_STYLE_S60) && defined(QT_STYLE_S60)
# undef QT_NO_STYLE_S60
#elif !defined(QT_NO_STYLE_S60) && !defined(QT_STYLE_S60)
# define QT_NO_STYLE_S60
#endif

#if defined(QT_NO_SVG) && defined(QT_SVG)
# undef QT_NO_SVG
#elif !defined(QT_NO_SVG) && !defined(QT_SVG)
# define QT_NO_SVG
#endif

#if defined(QT_NO_SXE) && defined(QT_SXE)
# undef QT_NO_SXE
#elif !defined(QT_NO_SXE) && !defined(QT_SXE)
# define QT_NO_SXE
#endif

#if defined(QT_NO_WEBKIT) && defined(QT_WEBKIT)
# undef QT_NO_WEBKIT
#elif !defined(QT_NO_WEBKIT) && !defined(QT_WEBKIT)
# define QT_NO_WEBKIT
#endif

#if defined(QT_NO_XMLPATTERNS) && defined(QT_XMLPATTERNS)
# undef QT_NO_XMLPATTERNS
#elif !defined(QT_NO_XMLPATTERNS) && !defined(QT_XMLPATTERNS)
# define QT_NO_XMLPATTERNS
#endif

#if defined(QT_OPENGL_ES) && defined(QT_NO_OPENGL_ES)
# undef QT_OPENGL_ES
#elif !defined(QT_OPENGL_ES) && !defined(QT_NO_OPENGL_ES)
# define QT_OPENGL_ES
#endif

#if defined(QT_OPENGL_ES_2) && defined(QT_NO_OPENGL_ES_2)
# undef QT_OPENGL_ES_2
#elif !defined(QT_OPENGL_ES_2) && !defined(QT_NO_OPENGL_ES_2)
# define QT_OPENGL_ES_2
#endif

#if defined(QT_RUNTIME_XCURSOR) && defined(QT_NO_RUNTIME_XCURSOR)
# undef QT_RUNTIME_XCURSOR
#elif !defined(QT_RUNTIME_XCURSOR) && !defined(QT_NO_RUNTIME_XCURSOR)
# define QT_RUNTIME_XCURSOR
#endif

#if defined(QT_RUNTIME_XFIXES) && defined(QT_NO_RUNTIME_XFIXES)
# undef QT_RUNTIME_XFIXES
#elif !defined(QT_RUNTIME_XFIXES) && !defined(QT_NO_RUNTIME_XFIXES)
# define QT_RUNTIME_XFIXES
#endif

#if defined(QT_RUNTIME_XINERAMA) && defined(QT_NO_RUNTIME_XINERAMA)
# undef QT_RUNTIME_XINERAMA
#elif !defined(QT_RUNTIME_XINERAMA) && !defined(QT_NO_RUNTIME_XINERAMA)
# define QT_RUNTIME_XINERAMA
#endif

#if defined(QT_RUNTIME_XINPUT) && defined(QT_NO_RUNTIME_XINPUT)
# undef QT_RUNTIME_XINPUT
#elif !defined(QT_RUNTIME_XINPUT) && !defined(QT_NO_RUNTIME_XINPUT)
# define QT_RUNTIME_XINPUT
#endif

#if defined(QT_RUNTIME_XRANDR) && defined(QT_NO_RUNTIME_XRANDR)
# undef QT_RUNTIME_XRANDR
#elif !defined(QT_RUNTIME_XRANDR) && !defined(QT_NO_RUNTIME_XRANDR)
# define QT_RUNTIME_XRANDR
#endif

#if defined(QT_USE_MATH_H_FLOATS) && defined(QT_NO_USE_MATH_H_FLOATS)
# undef QT_USE_MATH_H_FLOATS
#elif !defined(QT_USE_MATH_H_FLOATS) && !defined(QT_NO_USE_MATH_H_FLOATS)
# define QT_USE_MATH_H_FLOATS
#endif

#ifndef Q_WS_QPA
# define Q_WS_QPA
#endif

#endif // QT_BOOTSTRAPPED

#define QT_VISIBILITY_AVAILABLE

