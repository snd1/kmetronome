/***************************************************************************
 *   KMetronome - ALSA Sequencer based MIDI metronome                      *
 *   Copyright (C) 2005-2009 Pedro Lopez-Cabanillas <plcl@users.sf.net>    *
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

#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include <kmessagebox.h>
#include "kmetronome.h"

static const char description[] =
    I18N_NOOP("KDE MIDI metronome using ALSA sequencer");

static const char version[] = VERSION;

/*static KCmdLineOptions options[] =
{
//    { "+[URL]", I18N_NOOP( "Document to open." ), 0 },
    KCmdLineLastOption
};*/

int main(int argc, char **argv) {
	KAboutData about("kmetronome", 0, ki18n("KMetronome"), version, 
	                 ki18n(description), KAboutData::License_GPL,
	                 ki18n("(C) 2005-2008 Pedro Lopez-Cabanillas"), 
	                 KLocalizedString(),
	                 "http://kmetronome.sourceforge.net",
	                 "plcl@users.sourceforge.net");
    about.addAuthor( ki18n("Pedro Lopez-Cabanillas"), KLocalizedString(), 
                     "plcl@users.sourceforge.net");
	KCmdLineArgs::init(argc, argv, &about);
    //KCmdLineOptions options;
    //options.add("+[URL]", ki18n( "Document to open" ));
	//KCmdLineArgs::addCmdLineOptions( options );

	KApplication app;
	KMetronome *mainWin = 0;
	try {
    	if (app.isSessionRestored())
    	{
    		RESTORE(KMetronome);
    	}
    	else
    	{
    		// no session.. just start up normally
    		//KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    		mainWin = new KMetronome;
    		mainWin->show();
    		//args->clear();
    	}
    	return app.exec();
    } catch (SequencerError& ex) {
        QString errorstr = i18n("Fatal error from the ALSA sequencer. "
            "This usually happens when the kernel doesn't have ALSA support, "
            "or the device node (/dev/snd/seq) doesn't exists, "
            "or the kernel module (snd_seq) is not loaded. "
            "Please check your ALSA/MIDI configuration. Returned error was: %1")
            .arg(ex.qstrError());
        KMessageBox::error(0, errorstr, i18n("Error"));
    }
}
