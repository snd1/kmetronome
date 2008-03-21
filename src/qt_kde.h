/***************************************************************************
 *   KMetronome - ALSA Sequencer based MIDI metronome                      *
 *   Copyright (C) 2005-2008 Pedro Lopez-Cabanillas                        *
 *   <plcl@users.sourceforge.net>                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,            *
 *   MA 02110-1301, USA                                                    *
 ***************************************************************************/

#ifndef QT_KDE_H_
#define QT_KDE_H_

// Standard C++ library
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <exception>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <strstream>
#include <utility>
#include <vector>

// QT3 headers

// Common headers, or used by sources generated by moc
#include <qmap.h> 
#include <qglobal.h>
#include <private/qucomextra_p.h> 
#include <qmetaobject.h>
#include <qobjectdefs.h>
#include <qsignalslotimp.h>
#include <qstyle.h>

// Headers used by KDE3
#include <qaccel.h>
#include <qapplication.h>
#include <qbitmap.h>
#include <qbrush.h>
#include <qbuffer.h>
#include <qbuttongroup.h>
#include <qbutton.h>
#include <qcanvas.h>
#include <qcheckbox.h>
#include <qcolor.h>
#include <qcombobox.h>
#include <qcstring.h>
#include <qcursor.h>
#include <qdatastream.h>
#include <qdatetime.h>
#include <qdialog.h>
#include <qdict.h>
#include <qdir.h>
#include <qdom.h>
#include <qdragobject.h>
#include <qdrawutil.h>
#include <qevent.h>
#include <qeventloop.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qfont.h>
#include <qfontinfo.h>
#include <qfontmetrics.h>
#include <qframe.h>
#include <qgarray.h>
#include <qgrid.h>
#include <qgroupbox.h>
#include <qguardedptr.h>
#include <qhbox.h>
#include <qheader.h>
#include <qiconset.h>
#include <qimage.h>
#include <qinputdialog.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qlistview.h>
#include <qmemarray.h>
#include <qmutex.h>
#include <qobject.h>
#include <qobjectlist.h>
#include <qpaintdevicemetrics.h>
#include <qpainter.h>
#include <qpalette.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qpointarray.h>
#include <qpoint.h>
#include <qpopupmenu.h>
#include <qprinter.h>
#include <qprogressdialog.h>
#include <qptrdict.h>
#include <qptrlist.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qrect.h>
#include <qregexp.h>
#include <qregion.h>
#include <qscrollbar.h>
#include <qscrollview.h>
#include <qsessionmanager.h>
#include <qsignalmapper.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qslider.h>
#include <qsocketnotifier.h>
#include <qspinbox.h>
#include <qsplitter.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qstrlist.h>
#include <qtable.h>
#include <qtabwidget.h>
#include <qtextcodec.h>
#include <qtextedit.h>
#include <qtextstream.h>
#include <qthread.h>
#include <qtimer.h>
#include <qtoolbutton.h>
#include <qtooltip.h>
#include <qvalidator.h>
#include <qvaluelist.h>
#include <qvaluevector.h>
#include <qvariant.h>
#include <qvbox.h>
#include <qvgroupbox.h>
#include <qwhatsthis.h>
#include <qwidget.h>
#include <qwidgetstack.h>
#include <qwmatrix.h>
#include <qxml.h>

// KDE3 headers
#include <kaboutdata.h>
#include <kaccel.h>
#include <kactioncollection.h>
#include <kaction.h>
#include <kapp.h>
#include <kapplication.h>
#include <karrowbutton.h>
#include <kcmdlineargs.h>
#include <kcolordialog.h>
#include <kcombobox.h>
#include <kcommand.h>
#include <kcompletion.h>
#include <kconfig.h>
#include <kcursor.h>
#include <kdcopactionproxy.h>
#include <kdebug.h>
#include <kdeversion.h>
#include <kdialogbase.h>
#include <kdialog.h>
#include <kdiskfreesp.h>
#include <kdockwidget.h>
#include <kedittoolbar.h>
#include <kfiledialog.h>
#include <kfile.h>
#include <kfilterdev.h>
#include <kfontrequester.h>
#include <kglobal.h>
#include <kglobalsettings.h>
#include <kiconloader.h>
#include <kinputdialog.h>
#include <kio/netaccess.h>
#include <kkeydialog.h>
#include <kled.h>
#include <klineeditdlg.h>
#include <klineedit.h>
#include <klistview.h>
#include <klocale.h>
#include <kmainwindow.h>
#include <kmessagebox.h>
#include <kmimetype.h>
#include <kpixmapeffect.h>
#include <kpopupmenu.h>
#include <kprinter.h>
#include <kprocess.h>
#include <kprogress.h>
#include <kpushbutton.h>
#include <ksqueezedtextlabel.h>
#include <kstandarddirs.h>
#include <kstatusbar.h>
#include <kstdaccel.h>
#include <kstdaction.h>
#include <kstddirs.h>
#include <ktabwidget.h>
#include <ktempfile.h>
#include <ktip.h>
#include <ktoolbar.h>
#include <kuniqueapplication.h>
#include <kurl.h>
#include <kxmlguiclient.h>
#include <kxmlguifactory.h>

#endif /*QT_KDE_H_*/
