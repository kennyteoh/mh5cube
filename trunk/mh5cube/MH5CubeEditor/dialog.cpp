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

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent, CubeWidgetGL *cubeWidgetPreview, CubeWidgetGL *cubeWidget) :
    QDialog(parent),
    m_ui(new Ui::Dialog)
{
    m_ui->setupUi(this);
    connect(this->m_ui->pushButtonColorLEDOn    , SIGNAL(clicked()), this, SLOT(changeColorLEDOn()));
    connect(this->m_ui->pushButtonColorLEDOff   , SIGNAL(clicked()), this, SLOT(changeColorLEDOff()));
    connect(this->m_ui->pushButtonColorBGDay    , SIGNAL(clicked()), this, SLOT(changeColorBGDay()));
    connect(this->m_ui->pushButtonColorBGNight  , SIGNAL(clicked()), this, SLOT(changeColorBGNight()));
    connect(this->m_ui->pushButtonDefaultColors, SIGNAL(clicked()), this, SLOT(defaultColors()));

    connect(this->m_ui->pushButton_NightMode, SIGNAL(toggled(bool)), cubeWidgetPreview, SLOT(toggleNightMode(bool)));
    connect(this->m_ui->pushButton_Perspective, SIGNAL(toggled(bool)), cubeWidgetPreview, SLOT(togglePerspective(bool)));
    connect(this->m_ui->pushButton_Reset, SIGNAL(clicked()), cubeWidgetPreview, SLOT(resetRotation()));

    this->m_ui->gridLayout_2->addWidget(cubeWidgetPreview,0,0,3,1,Qt::AlignJustify);
    this->m_ui->tabWidget->removeTab(1); //Remove Preview Tab (Not fully ready yet)


}

Dialog::~Dialog()
{
    delete m_ui;
}

void Dialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dialog::updateLabelColor(QLabel* label, QColor newColor) {
    QPalette pal = label->palette();
    pal.setColor(label->backgroundRole(), newColor);
    label->setPalette(pal);
    label->setAutoFillBackground(true);
}


//----------------------------------------------------------------

void Dialog::changeColorLEDOn() {
    QColor newColor = QColorDialog::getColor();
    tempSettingsCube.ColorLEDOn = newColor;
    updateLabelColor(this->m_ui->labelColorLEDOn, newColor);
    emit settingsChangedCube(tempSettingsCube);
    emit settingsChangedCubePreview(tempSettingsCube);
}

void Dialog::changeColorLEDOff() {
    QColor newColor = QColorDialog::getColor();
    tempSettingsCube.ColorLEDOff = newColor;
    updateLabelColor(this->m_ui->labelColorLEDOff, newColor);
    emit settingsChangedCube(tempSettingsCube);
    emit settingsChangedCubePreview(tempSettingsCube);
}

void Dialog::changeColorBGDay() {
    QColor newColor = QColorDialog::getColor();
    tempSettingsCube.ColorBGDay = newColor;
    updateLabelColor(this->m_ui->labelColorBGDay, newColor);
    emit settingsChangedCube(tempSettingsCube);
    emit settingsChangedCubePreview(tempSettingsCube);
}

void Dialog::changeColorBGNight() {
    QColor newColor = QColorDialog::getColor();
    tempSettingsCube.ColorBGNight = newColor;
    updateLabelColor(this->m_ui->labelColorBGNight, newColor);
    emit settingsChangedCube(tempSettingsCube);
    emit settingsChangedCubePreview(tempSettingsCube);
}

void Dialog::defaultColors() {
    tempSettingsCube.ColorBGDay = tempSettingsCube.DefaultColorBGDay;
    tempSettingsCube.ColorBGNight = tempSettingsCube.DefaultColorBGNight;
    tempSettingsCube.ColorLEDOn = tempSettingsCube.DefaultColorLEDOn;
    tempSettingsCube.ColorLEDOff = tempSettingsCube.DefaultColorLEDOff;
    emit(settingsChangedCube(tempSettingsCube)); //Update Colors in cubeWidgetGL

    tempSettingsCubePreview.ColorBGDay  = tempSettingsCubePreview.DefaultColorBGDay;
    tempSettingsCubePreview.ColorBGNight = tempSettingsCubePreview.DefaultColorBGNight;
    tempSettingsCubePreview.ColorLEDOn  = tempSettingsCubePreview.DefaultColorLEDOn;
    tempSettingsCubePreview.ColorLEDOff = tempSettingsCubePreview.DefaultColorLEDOff;
    emit(settingsChangedCubePreview(tempSettingsCubePreview)); //Update Colors in cubeWidgetPreview

    this->getGLSettingsCube(tempSettingsCube); //Update Color-Preview in this Dialog
    this->getGLSettingsCube(tempSettingsCubePreview);

}
//----------------------------------------------------------------


//Holt Kopie der Aktuellen Settings rein
void Dialog::getGLSettingsCube(GLSettings settings) {
    updateLabelColor(this->m_ui->labelColorLEDOn, settings.ColorLEDOn);
    updateLabelColor(this->m_ui->labelColorLEDOff, settings.ColorLEDOff);
    updateLabelColor(this->m_ui->labelColorBGDay, settings.ColorBGDay);
    updateLabelColor(this->m_ui->labelColorBGNight, settings.ColorBGNight);
    tempSettingsCube = settings;
}

//Holt Kopie der Aktuellen Settings rein
void Dialog::getGLSettingsCubePreview(GLSettings settings) {
    tempSettingsCubePreview = settings;
}


