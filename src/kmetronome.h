/***************************************************************************
 *   KMetronome - ALSA Sequencer based MIDI metronome                      *
 *   Copyright (C) 2005-2014 Pedro Lopez-Cabanillas <plcl@users.sf.net>    *
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

#ifndef KMETRONOME_H
#define KMETRONOME_H

#include <QMainWindow>
#include <QPointer>
#include <QTranslator>
#include "ui_kmetronome.h"

class SequencerAdapter;
class DrumGrid;
class DrumGridModel;
class Instrument;
class InstrumentList;
class QCloseEvent;

class KMetronome : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "net.sourceforge.kmetronome")

public:
    KMetronome(QWidget* parent=0);
    virtual ~KMetronome();

    void display(int, int);
    int getTempo() { return m_ui.m_tempo->value(); }
    int getBeatsBar() { return m_ui.m_beatsBar->value(); }
    int getFigure() { return m_ui.m_figure->currentIndex(); }
    void setBeatsBar(int newValue) { m_ui.m_beatsBar->setValue(newValue); }
    void setFigure(int newValue);
    void enableControls(bool e);
    void setPatterns(const QStringList& patterns);
    bool patternMode() { return m_patternMode; }
    QString getSelectedPattern();
    void setSelectedPattern(const QString& pattern);
    void closeEvent(QCloseEvent *event);

protected:
    virtual void mouseDoubleClickEvent ( QMouseEvent * e );

public Q_SLOTS:
    void about();
    void play();
    void stop();
    void cont();
    void setTempo(int newTempo);
    void setTimeSignature(int numerator, int denominator);

    void displayTempo(int);
    void displayWeakVelocity(int v) { m_ui.m_dial1->setValue(v); }
    void displayStrongVelocity(int v) { m_ui.m_dial2->setValue(v); }
    void displayVolume(int v) { m_ui. m_dial3->setValue(v); }
    void displayBalance(int v) { m_ui.m_dial4->setValue(v); }
    void displayFakeToolbar(bool b) { m_ui.m_fakeToolbar->setVisible(b); }
    void tempoComboChanged(int);

protected Q_SLOTS:
    void optionsPreferences();
    void tempoChanged(int);
    void beatsBarChanged(int);
    void rhythmFigureChanged(int);
    void weakVeloChanged(int);
    void strongVeloChanged(int);
    void volumeChanged(int);
    void balanceChanged(int);
    void toggle(bool checked);
    void updateDisplay(int, int);
    void editPatterns();
    void patternChanged(int);
    void updatePatterns();
    void exportPatterns();
    void importPatterns();

private:
    void setupAccel();
    void setupActions();
    void saveConfiguration();
    void readConfiguration();
    void readDrumGridPattern();
    void applyInstrumentSettings();
    void exportPatterns(const QString& path);
    void importPatterns(const QString& path);
    bool m_patternMode;
    Ui::KMetronomeWindow m_ui;

    SequencerAdapter* m_seq;
    QPointer<DrumGrid> m_drumgrid;
    InstrumentList* m_instrumentList;
    DrumGridModel* m_model;
    QString m_instrument;
    QString m_bank;
    QString m_program;
    QTranslator* m_trp;
    QTranslator* m_trq;
};

#endif // KMETRONOME_H
