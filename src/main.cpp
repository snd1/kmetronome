/***************************************************************************
 *   KMetronome - ALSA Sequencer based MIDI metronome                      *
 *   Copyright (C) 2005-2021 Pedro Lopez-Cabanillas <plcl@users.sf.net>    *
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
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.*
 ***************************************************************************/

#include <QApplication>
#include <QCommandLineParser>
#include "kmetronome.h"

int main (int argc, char **argv)
{
    const QString QSTR_APPNAME("Drumstick Metronome");
    const QString QSTR_DOMAIN("kmetronome.sourceforge.net");
    const QString QSTR_DESCRIPTION("ALSA Sequencer based MIDI Metronome");
    const QString QSTR_VERSION(QT_STRINGIFY(VERSION));

    QCoreApplication::setOrganizationName(QSTR_DOMAIN);
    QCoreApplication::setOrganizationDomain(QSTR_DOMAIN);
    QCoreApplication::setApplicationName(QSTR_APPNAME);
    QCoreApplication::setApplicationVersion(QSTR_VERSION);
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QSTR_DESCRIPTION);
    auto helpOption = parser.addHelpOption();
    auto versionOption = parser.addVersionOption();
    parser.process(app);

    if (parser.isSet(versionOption) || parser.isSet(helpOption)) {
        return 0;
    }

    KMetronome mainWin;
    mainWin.show();
    return app.exec();
}
