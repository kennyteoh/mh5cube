# This file is part of the Qube5-Editor.
# Qube5-Editor allows you to create figures and animations for the LED-Qube5.
# For more information about the LED-Qube5 and this program, see <http://www.qube-solutions.de>
# Copyright (C) 2009 Christian Strobel
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
QT += opengl
TARGET = MH5CubeEditor
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    cubewidgetgl.cpp \
    cubepreviewdelegate.cpp \
    cubepreview.cpp \
    serialthread.cpp \
    cubecommunication.cpp \
    dialog.cpp \
    timesdialog.cpp
HEADERS += mainwindow.h \
    cubewidgetgl.h \
    core.h \
    cubepreviewdelegate.h \
    cubepreview.h \
    serialthread.h \
    cubecommunication.h \
    dialog.h \
    timesdialog.h
FORMS += mainwindow.ui \
    dialog.ui \
    timesdialog.ui
DEPENDPATH += qextserialport
INCLUDEPATH += qextserialport
CONFIG( debug, debug|release ):LIBS += -Lqextserialport/build \
    -lqextserialportd
else:LIBS += -Lqextserialport/build \
    -lqextserialport
RESOURCES += RessourceIconsV2.qrc
RC_FILE = qubeicon.rc
