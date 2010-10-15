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

#include "timesdialog.h"
#include "ui_timesdialog.h"

TimesDialog::TimesDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::TimesDialog)
{
    m_ui->setupUi(this);

    this->newTime = this->m_ui->spinBox->value();

    connect(this->m_ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBoxChanged(int)));
    connect(this->m_ui->pushButton_apply, SIGNAL(clicked()), this, SLOT(applyTimes()));
    connect(this->m_ui->pushButton_plus, SIGNAL(clicked()), this, SIGNAL(increaseTime()));
    connect(this->m_ui->pushButton_minus, SIGNAL(clicked()), this, SIGNAL(decreaseTime()));


}

TimesDialog::~TimesDialog()
{
    delete m_ui;
}

void TimesDialog::spinBoxChanged(int newTime) {
    qDebug()<<"SpinChanged to "<< newTime;
    this->newTime = newTime;
}

void TimesDialog::applyTimes() {
    qDebug()<<"SetAllTimes to "<< newTime;
    emit(this->setTimes(this->newTime));
}


void TimesDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
