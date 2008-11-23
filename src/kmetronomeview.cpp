/***************************************************************************
 *   KMetronome - ALSA Sequencer based MIDI metronome                      *
 *   Copyright (C) 2005-2008 Pedro Lopez-Cabanillas <plcl@users.sf.net>    *
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

#include <QLCDNumber>
#include <QMouseEvent>

#include <kapplication.h>
#include <kpushbutton.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kinputdialog.h>

#include "knob.h"
#include "classicstyle.h"
#include "kmetronomeview.h"
#include "defs.h"

KmetronomeView::KmetronomeView(QWidget *parent)
     : QWidget(parent), Ui::KmetronomeViewBase()
{
    setupUi(this);
    
    m_exitbtn->setIcon(KIcon("application-exit"));
    m_configbtn->setIcon(KIcon("configure"));
    m_playbtn->setIcon(KIcon("media-playback-start"));
    m_stopbtn->setIcon(KIcon("media-playback-stop"));

    m_dialStyle = new ClassicStyle();
    m_dialStyle->setParent(this);
    
    m_dial1->setStyle(m_dialStyle);
    m_dial2->setStyle(m_dialStyle);
    m_dial3->setStyle(m_dialStyle);
    m_dial4->setStyle(m_dialStyle);
    m_dial1->setRange(0, 127);
    m_dial2->setRange(0, 127);
    m_dial3->setRange(0, 127);
    m_dial4->setRange(0, 127);
    m_dial1->setDialMode(Knob::LinearMode);
    m_dial2->setDialMode(Knob::LinearMode);
    m_dial3->setDialMode(Knob::LinearMode);
    m_dial4->setDialMode(Knob::LinearMode);
    
    connect( m_exitbtn, SIGNAL(clicked()), kapp, SLOT(quit()) );
    connect( m_configbtn, SIGNAL(clicked()),
             parent, SLOT(optionsPreferences()) );
    connect( m_playbtn, SIGNAL(clicked()), parent, SLOT(play()) );
    connect( m_stopbtn, SIGNAL(clicked()), parent, SLOT(stop()) );
    connect( m_beatsBar, SIGNAL(valueChanged(int)), parent, SLOT(beatsBarChanged(int)) );
    connect( m_figure, SIGNAL(activated(int)), parent, SLOT(rhythmFigureChanged(int)) );
    connect( m_tempo, SIGNAL(valueChanged(int)), parent, SLOT(tempoChanged(int)) );

    connect( m_dial1, SIGNAL(valueChanged(int)), parent, SLOT(weakVeloChanged(int)) );
    connect( m_dial2, SIGNAL(valueChanged(int)), parent, SLOT(strongVeloChanged(int)) );
    connect( m_dial3, SIGNAL(valueChanged(int)), parent, SLOT(volumeChanged(int)) );
    connect( m_dial4, SIGNAL(valueChanged(int)), parent, SLOT(balanceChanged(int)) );
}

void KmetronomeView::display(int bar, int beat) 
{
    m_measureLCD->display(bar);
    m_beatLCD->display(beat);
}

void KmetronomeView::setFigure(int newValue)
{
    int ts_dd;
    int x = newValue;
    for(ts_dd = 0; x > 1; x /= 2)
        ++ts_dd;
    m_figure->setCurrentIndex(ts_dd);
}

void KmetronomeView::m_tempo_valueChanged(int newTempo)
{
    m_tempoLCD->display(newTempo);
}

void KmetronomeView::enableControls(bool e)
{
    m_playbtn->setEnabled(e);
    m_stopbtn->setEnabled(!e);
    m_configbtn->setEnabled(e);
    m_beatsBar->setEnabled(e);
    m_figure->setEnabled(e);
}

void KmetronomeView::mouseDoubleClickEvent(QMouseEvent *)
{
    bool ok = false;
    int newTempo = KInputDialog::getInteger( 
    					i18n("Tempo"), i18n("Enter new Tempo:"),
    					m_tempo->value(), TEMPO_MIN, TEMPO_MAX, 1, 10,
					    &ok, this );
    if (ok) {
    	m_tempo->setValue(newTempo);
    }
}
