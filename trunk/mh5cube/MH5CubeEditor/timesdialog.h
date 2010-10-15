/*
# This file is part of the Qube5-Editor.
#
# Qube5-Editor allows you to create figures and animations for the LED-Qube5.
# For more information about the LED-Qube5 and this program, see <http://www.qube-solutions.de>
# Copyright (C) 2009-2010 Christian Strobel
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TIMESDIALOG_H
#define TIMESDIALOG_H

#include <QtGui/QDialog>
#include <QtDebug>

namespace Ui {
    class TimesDialog;
}

class TimesDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(TimesDialog)
public:
    explicit TimesDialog(QWidget *parent = 0);
    virtual ~TimesDialog();

public slots:
    void spinBoxChanged(int newTime);
    void applyTimes(); //called by apply-Button

signals:
    void setTimes(int newTime); //emitted in applyTimes-Routine
    void increaseTime(); //emitted by plus-Button
    void decreaseTime(); //emitted by minus-Button


protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::TimesDialog *m_ui;

    int newTime;

};

#endif // TIMESDIALOG_H
