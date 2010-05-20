/*
    KMetronome - ALSA Sequencer based MIDI metronome
    Copyright (C) 2006-2010, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "drumgrid.h"
#include "drumgridmodel.h"
#include "sequenceradapter.h"
#include "ui_drumgrid.h"

#include <qmath.h>
#include <QtGui/QInputDialog>
#include <QtGui/QShortcut>
#include <QtGui/QToolTip>
#include <QtCore/QSignalMapper>
#include <QtCore/QSettings>
#include <KDE/KConfigGroup>
#include <KDE/KIcon>
#include <KDE/KDebug>
#include <drumstick.h>

DrumGrid::DrumGrid(QWidget *parent)
    : KDialog(parent),
    m_ui(new Ui::DrumGrid),
    m_seq(NULL),
    m_model(NULL),
    m_figure(16)
{
    QWidget *widget = new QWidget(this);
    m_ui->setupUi(widget);
    setMainWidget( widget );
    setCaption( i18n("Pattern Editor") );
    setFixedWidth( 700 );
    m_ui->startButton->setIcon(KIcon("media-playback-start"));
    m_ui->stopButton->setIcon(KIcon("media-playback-stop"));
    m_ui->saveButton->setIcon(KIcon("document-save"));
    m_ui->deleteButton->setIcon(KIcon("edit-delete"));
    m_ui->addButton->setIcon(KIcon("list-add"));
    m_ui->removeButton->setIcon(KIcon("list-remove"));

    m_ui->tempoSlider->setMaximum(TEMPO_MAX);
    m_ui->tempoSlider->setMinimum(TEMPO_MIN);
    connect( m_ui->startButton, SIGNAL(clicked()), SLOT(play()));
    connect( m_ui->stopButton, SIGNAL(clicked()), SLOT(stop()));
    connect( m_ui->tempoSlider, SIGNAL(valueChanged(int)), SLOT(tempoChange(int)));
    connect( m_ui->gridColumns, SIGNAL(valueChanged(int)), SLOT(gridColumns(int)));
    connect( m_ui->patternCombo, SIGNAL(activated(int)), SLOT(patternChanged(int)));
    connect( m_ui->saveButton, SIGNAL(clicked()), SLOT(savePattern()));
    connect( m_ui->deleteButton, SIGNAL(clicked()), SLOT(removePattern()));

    m_model = new DrumGridModel(this);
    m_model->fillSampleData();
    m_ui->tableView->setModel(m_model);
    connect ( this, SIGNAL(signalUpdate(int,int)), SLOT(updateDisplay(int,int)) );

    m_mapper = new QSignalMapper(this);
    addShortcut(QKeySequence("f"), "f");
    addShortcut(QKeySequence("p"), "p");
    addShortcut(QKeySequence("1"), "1");
    addShortcut(QKeySequence("2"), "2");
    addShortcut(QKeySequence("3"), "3");
    addShortcut(QKeySequence("4"), "4");
    addShortcut(QKeySequence("5"), "5");
    addShortcut(QKeySequence("6"), "6");
    addShortcut(QKeySequence("7"), "7");
    addShortcut(QKeySequence("8"), "8");
    addShortcut(QKeySequence("9"), "9");
    addShortcut(QKeySequence("0"), QString());
    addShortcut(QKeySequence::Delete, QString());
    connect( m_mapper, SIGNAL(mapped(QString)), SLOT(shortcutPressed(QString)));
    connect ( m_ui->tableView, SIGNAL(doubleClicked(const QModelIndex&)),
              m_model, SLOT(changeCell(const QModelIndex &)) );
}

DrumGrid::~DrumGrid()
{
    foreach(QShortcut* s, m_shortcuts)
        delete s;
    delete m_ui;
}

void DrumGrid::updateView()
{
    m_ui->tableView->resizeColumnsToContents();
    m_ui->tableView->resizeRowsToContents();
}

void DrumGrid::play()
{
    m_seq->metronome_set_tempo();
    m_seq->metronome_start();
}

void DrumGrid::stop()
{
    m_seq->metronome_stop();
}

void DrumGrid::tempoChange(int newTempo)
{
    m_seq->setBpm(newTempo);
    m_seq->metronome_set_tempo();
    updateTempo(newTempo);
}

void DrumGrid::updateTempo(int newTempo)
{
    QString tip = QString::number(newTempo);
    m_ui->tempoSlider->setToolTip(tip);
    m_ui->tempoLabel->setNum(newTempo);
    QToolTip::showText(QCursor::pos(), tip, this);
}

void DrumGrid::gridColumns(int columns)
{
    m_model->updatePatternColumns(columns);
    updateView();
}

void DrumGrid::shortcutPressed(const QString& value)
{
    QModelIndex index = m_ui->tableView->currentIndex();
    m_model->changeCell(index, value);
}

void DrumGrid::addShortcut(const QKeySequence& key, const QString& value)
{
    QShortcut* shortcut = new QShortcut(key, m_ui->tableView);
    connect (shortcut, SIGNAL(activated()), m_mapper, SLOT(map()));
    m_mapper->setMapping(shortcut, value);
    m_shortcuts.append(shortcut);
}

void DrumGrid::readPattern()
{
    KConfigGroup config = KGlobal::config()->group(QSTR_PATTERN+m_currentPattern);
    QStringList keys = config.keyList();
    //kDebug() << m_currentPattern << keys;
    if (!keys.empty()) {
        keys.sort();
        m_model->clearPattern();
        foreach(const QString& key, keys) {
            QStringList row = config.readEntry(key, QStringList());
            //kDebug() << key << row;
            m_model->addPatternData(key.toInt(), row);
        }
        m_model->endOfPattern();
    }
}

void DrumGrid::readPattern(const QString& name)
{
    m_currentPattern = name;
    readPattern();
}

void DrumGrid::writePattern()
{
    KConfigGroup config = KGlobal::config()->group(QSTR_PATTERN+m_currentPattern);
    for(int r = 0; r < m_model->rowCount(); ++r) {
        config.writeEntry( m_model->patternKey(r),
                           m_model->patternData(r) );
    }
    config.sync();
}

void DrumGrid::writePattern(const QString& name)
{
    m_currentPattern = name;
    writePattern();
}

void DrumGrid::removePattern(const QString& name)
{
    KGlobal::config()->deleteGroup(QSTR_PATTERN+name);
    KGlobal::config()->sync();
}

QStringList DrumGrid::patterns()
{
    QStringList lst;
    int n = QSTR_PATTERN.size();
    foreach(const QString& name, KGlobal::config()->groupList()) {
        if (name.startsWith(QSTR_PATTERN))
            lst += name.mid(n);
    }
    return lst;
}

void DrumGrid::patternChanged(int /*idx*/)
{
    readPattern(m_ui->patternCombo->currentText());
}

void DrumGrid::savePattern()
{
    writePattern(m_ui->patternCombo->currentText());
}

void DrumGrid::removePattern()
{
    int idx = m_ui->patternCombo->currentIndex();
    QString tmpPattern = m_ui->patternCombo->currentText();
    m_ui->patternCombo->removeItem(idx);
    removePattern(tmpPattern);
    m_currentPattern.clear();
    m_model->clearPattern();
    if (m_ui->patternCombo->count() > 0)
        m_ui->patternCombo->setCurrentItem(0);
}

void DrumGrid::selectPattern(const QString& name)
{
    m_currentPattern = name;
}

void DrumGrid::showEvent(QShowEvent* /*event*/)
{
    m_ui->tempoSlider->setValue(m_seq->getBpm());
    updateTempo(m_seq->getBpm());
    m_seq->setPatternMode(true);
    m_ui->patternCombo->clear();
    m_ui->patternCombo->addItems(patterns());
    if (!m_currentPattern.isEmpty())
        m_ui->patternCombo->setCurrentItem(m_currentPattern);
    updateView();
}

void DrumGrid::done(int r)
{
    kDebug() << r;
    stop();
    m_seq->setPatternMode(false);
    if (r == QDialog::Accepted && !m_currentPattern.isEmpty())
        writePattern();
    QDialog::done(r);
}

void DrumGrid::updateDisplay(int /*bar*/, int beat)
{
    m_ui->tableView->selectColumn(beat-1);
}

void DrumGrid::setSequencer(SequencerAdapter* seq)
{
    m_seq = seq;
    connect( m_seq, SIGNAL(signalUpdate(int,int)),
             SLOT(updateDisplay(int,int)), Qt::QueuedConnection);
    m_seq->setModel(m_model);
}
