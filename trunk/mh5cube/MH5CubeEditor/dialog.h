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

#ifndef DIALOG_H
#define DIALOG_H
#include <QtGui>
#include <QtGui/QDialog>
#include <QtGui/QColorDialog>
#include "core.h"
#include "cubewidgetgl.h"
#include <QtDebug>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(Dialog)
public:
    explicit Dialog(QWidget *parent = 0, CubeWidgetGL *cubeWidgetPreview = 0, CubeWidgetGL *cubeWidget = 0);
    virtual ~Dialog();

public slots:
    void changeColorLEDOn();
    void changeColorLEDOff();
    void changeColorBGDay();
    void changeColorBGNight();
    void defaultColors();


    void getGLSettingsCube(GLSettings settings); //Called by Mainwindow, so get current settings
    void getGLSettingsCubePreview(GLSettings settings); //Called by Mainwindow, so get current settings

signals:
    void settingsChangedCube(GLSettings newSettings);
    void settingsChangedCubePreview(GLSettings newSettings);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Dialog *m_ui;
    GLSettings tempSettingsCube;
    GLSettings tempSettingsCubePreview;
    void updateLabelColor(QLabel*, QColor);
};

#endif // DIALOG_H
