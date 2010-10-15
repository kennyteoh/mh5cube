/*
# This file is part of the Qube5-Editor.
#
# Qube5-Editor allows you to create figures and animations for the LED-Qube5.
# For more information about the LED-Qube5 and this program, see <http://www.qube-solutions.de>
# Copyright (C) 2009 Christian Strobel
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

#ifndef CORE_H
#define CORE_H

#define VERSION     0x00000001  //Used for verifying the Data-Format of Loaded Files
#define MAGICNUMBER 0x12345678

#define WINDOW_TITLE "MH5CubeEditor"
#define DIMENSION 5 //Dimension of the cube
#define NUM_ITEMS DIMENSION*DIMENSION*DIMENSION //Total Number of Items(LEDs)

#define DEFAULT_TIME 10 //Every figure has this default time

#define MAX_ALLOWED_FIGURES 2000 //Limited to 1000 Figures with ATMega32

#define glError() { \
        GLenum err = glGetError(); \
        if (err != GL_NO_ERROR) { \
                qDebug()<< "glError in File:" << (char*) __FILE__ << "Line " << (int) __LINE__ << ":" << (char*) gluErrorString(err); \
                err = glGetError(); \
        } \
        else { \
               /*qDebug()<< "no glError in Line:" << (char*) __FILE__ << "Line " << (int) __LINE__ << "!"; */  \
        } \
}

struct GLSettings
{
    QColor ColorBGDay;
    QColor ColorBGNight;
    QColor ColorLEDOn;
    QColor ColorLEDOff;

    QColor DefaultColorBGDay;
    QColor DefaultColorBGNight;
    QColor DefaultColorLEDOn;
    QColor DefaultColorLEDOff;
};


#endif // CORE_H
