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

#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include "qextserialport/qextserialport.h"
#include <QThread>

//! This SerialThread is launched by CubeCommunications to program the Qube
/*!
\param[in] *port - Pointer to a QextSerialPort Object
\param[in] data - QByteArray containing the Data (see MainWindow::prepareProgramming()
\param[in] *parent - optional Pointer to the Parent QObject
*/
class SerialThread : public QThread
{
    Q_OBJECT
public:

    QextSerialPort *port;
    QByteArray data;
    SerialThread(QextSerialPort *port, QByteArray data, int numberOfFigures, QObject *parent = 0);

signals:
    void percentageFinished(int);   //!< Emits the finished percentage, connected to CubeCommunication::programmingPercentage() Signal
    void programmingFailed();       //!< Emitted when programming failed, connected to CubeCommunication::programmingFailed() Signal
    void programmingSuccessful();   //!< Emitted when programming was successful, connected to CubeCommunication::programmingSuccessful() Signal

protected:
    virtual void run(); //!< used by CubeCommunication::startProgramming() to start the Thread

private:
    int numberOfFigures;    //!< holds the number of figures that are going to be programmed
};

#endif // SERIALTHREAD_H
