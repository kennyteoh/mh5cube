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

#ifndef CUBECOMMUNICATION_H
#define CUBECOMMUNICATION_H

#include <QObject>
#include <QString>
#include <QBitArray>
#include <QByteArray>
#include <QComboBox>
#include <QDebug>
#include <QPushButton>

class QextSerialPort;

//! This class, CubeCommunication is used to interact with the Qube
/*
  It Uses the extern class QExtSerialPort for the platform-independent handling of a Serial Connection (http://qextserialport.sourceforge.net/)
  For Programming, a SerialThread is being launched.
*/

class CubeCommunication : public QObject
{
    Q_OBJECT
public:
    CubeCommunication(QObject * parent = 0, QComboBox * ComPortComboBox = 0);
    bool isConnected();
    bool isLiveMode();


public slots:
    void ConnectionToggle(bool state);
    void LiveModeToggle(bool state);
    void startProgramming(QByteArray data, int countRows);
    void updateLiveModeStates(QBitArray *states);
    void ShowFixedEffects(int nrEffect, bool looped);

private:
    QextSerialPort *serial;
    QComboBox* ComPortCombo; //!< Pointer to a QComboBox, which contains the different COMPorts
    int ConnectionOpen();
    int ConnectionClose();
    int ConnectionTest();
    int LiveModeEnter();
    int LiveModeLeave();
    QString currentPort;    //!< holds the current Opened Port
    bool connected;
    bool liveModeActive;

signals:
    void programmingPercentage(int percentage); //!< emits the finished Percentage to MainWindow, received by the SerialThread
    void programmingSuccessful();   //!<emitted when programming was successful, received by the SerialThread
    void programmingFailed();       //!<emitted when programming failed, received by the SerialThread
    void openingCOMPortSuccessful(QString COMPortName); //!<emitted when opening was successful
    void openingCOMPortFailed(QString COMPortName); //!<emitted when opening failed
    void findingCubeFailed(QString COMPortName); //!< emitted when COMPort could be opened, but no Qube is connected to it


};

#endif // CUBECOMMUNICATION_H
