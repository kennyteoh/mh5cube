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


// Specify the MSWindows naming scheme (COM1, COM2, ...)
#define _TTY_WIN_
#include "qextserialport/qextserialbase.h"
#include "qextserialport/qextserialport.h"
#include "qextserialport/qextserialenumerator.h"
#include "serialthread.h"

#include "cubecommunication.h"

//! Constructor for CubeCommunication
/*!
 This Constructor expects a QComboBox and fills it with the available Com-Ports
 \param[in] QObject* - Pointer to parent Object
 \param[in] QComboBox* - Pointer to the QQComboBox which manages the COM-Port selection
*/
CubeCommunication::CubeCommunication(QObject * parent, QComboBox* ComPortComboBox)
        :QObject(parent)
{
    connected = false;
    liveModeActive = false;
    ComPortCombo = ComPortComboBox;

    serial = new QextSerialPort;

    ComPortCombo->clear();
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();


    QStringList PortNames;
    for(int i = 0; i < ports.size(); i++) {
      PortNames << ports.at(i).portName.toLocal8Bit().constData(); /*<< ports.at(i).friendName.toLocal8Bit().constData();*/
      qDebug()<< ports.at(i).portName.toLocal8Bit().constData();
    }
    ComPortCombo->insertItems(0, PortNames);

}

//! Returns the Connection-State
bool CubeCommunication::isConnected() {
    return connected;
}

//! Returns the Connection-State
bool CubeCommunication::isLiveMode() {
    return liveModeActive;
}


/* public slots: */

//! Checks if user wants to connect or disconnect
void CubeCommunication::ConnectionToggle(bool state) {

    qDebug() << "ConnectionToggled";

    //Try to Connect
    if(state == true) {
        if(this->ConnectionOpen()) { //Could COM-Port be opened?

            if(ConnectionTest()==1) { //IS a Qube Connected to the Port?
                connected = true;
                ComPortCombo->setEnabled(false);
            }
            else {
                this->ConnectionClose();
                connected = false;
                QPushButton* PSender = (QPushButton*)QObject::sender();
                PSender->setChecked(false);
                emit findingCubeFailed(serial->portName());
            }
        }
        else {
            QPushButton* PSender = (QPushButton*)QObject::sender();
            PSender->setChecked(false);
            ComPortCombo->setEnabled(true);
            connected=false;
        }
    }
    //Disconnect
    else {
        this->ConnectionClose();
        ComPortCombo->setEnabled(true);
        connected=false;
    }
}

//! Switches to Live Mode / Normal Mode
void CubeCommunication::LiveModeToggle(bool state) {
    qDebug()<<"LiveModeToggle";

    if(state == true) {
        if(this->LiveModeEnter()) {
            qDebug("CubeCommunications: Live Mode Entered");
            liveModeActive=true;
        }
        else {
            QPushButton* PSender = (QPushButton*)QObject::sender();
            PSender->setChecked(false);
            liveModeActive=false;
        }
    }
    else {
        if(this->LiveModeLeave()) {
            qDebug("CubeCommunications: Live Mode Left");
            qDebug() << Q_FUNC_INFO;
            liveModeActive = false;
        }
    }
}

//! Tells the Cube to enter the FixedEffect
void CubeCommunication::ShowFixedEffects(int nrEffect, bool looped) {
    if(!isConnected()){
        return;
    }
    qDebug("ShowFixedEffects");

    char c; //Flush the serial input buffer
    while(this->serial->getChar(&c));

    serial->putChar('z');
    uchar effect = 0x00;
    if (looped) {
        effect = 0x10;
    }
    effect += nrEffect;
    serial ->putChar(effect);

}

//! Tells the Qube to enter the LiveMode
int CubeCommunication::LiveModeEnter() {
   if(!isConnected()) {
    return 0;
   }
   qDebug("LiveModeEnter");
   this->serial->putChar('l'); //Enter LiveMode

   char c; //Flush the serial input buffer
   while(this->serial->getChar(&c));

   return 1;
}

//! Tells the Qube to leave the LiveMode
int CubeCommunication::LiveModeLeave() {
   if(!isConnected()) {
    return 0;
   }
   qDebug("LiveModeLeave");
   this->serial->putChar('L'); //Leave LiveMode

   char c; //Flush the serial input buffer
   while(this->serial->getChar(&c));

   return 1;
}

//! Launches a new SerialThread for Programming the Qube
/*!
  A new SerialThread is created and startet at Low Priority.
  \param[in] data - QByteArray, containing the complete Data set (see MainWindow::prepareProgramming())
  \param[in] count - the number of Figures that are programmed
  \sa MainWindow::prepareProgramming()
*/
void CubeCommunication::startProgramming(QByteArray data, int count) {
    qDebug()<<"startProgramming " << count << "Figures";

    SerialThread *programmThread = new SerialThread(this->serial, data, count);
    programmThread->start(QThread::LowPriority);

    connect(programmThread, SIGNAL(percentageFinished(int)), this, SIGNAL(programmingPercentage(int)));
    connect(programmThread, SIGNAL(programmingSuccessful()), this, SIGNAL(programmingSuccessful()));
    connect(programmThread, SIGNAL(programmingFailed()), this, SIGNAL(programmingFailed()));
}

//! Sends the updated states to the Qube, if in LiveMode
/*!
  If the Qube has been connected, any changes made in the cubeWidget will be sent to the Qube and displayed in Real-Time
*/
void CubeCommunication::updateLiveModeStates(QBitArray *states) {

    if(!this->connected || !this->liveModeActive)
        return;

    QByteArray bytesFigure(27, '\0');
    bytesFigure[0] = '*';   //Start character

    int i = 0;
    for(int b = 1; b < 26; b++) {
        char Insertion = 0;
        Insertion += (int)states->at(++i)<<4;
        Insertion += (int)states->at(++i)<<3;
        Insertion += (int)states->at(++i)<<2;
        Insertion += (int)states->at(++i)<<1;
        Insertion += (int)states->at(++i);
        bytesFigure[b]=Insertion;
    }

    bytesFigure[26] = '~'; //End character
    serial->write(bytesFigure);

    char c; //Flush the serial input buffer
    while(this->serial->getChar(&c));

    qDebug()<<"updateLiveModeStates()";
}

/* private */

//! Opens the ComPort specified in ComPortCombo->currentText()
int CubeCommunication::ConnectionOpen() {
    qDebug()<<"ConnectionOpen";
    serial->setPortName(ComPortCombo->currentText().prepend("\\\\.\\"));
    serial->setBaudRate(BAUD19200);
    serial->setFlowControl(FLOW_OFF);
    serial->setParity(PAR_NONE);
    serial->setDataBits(DATA_8);
    serial->setStopBits(STOP_1);
    serial->setTimeout(50);

    if(serial->open(QIODevice::ReadWrite))
    {
            qDebug() << tr("Opening %1 successful").arg(serial->portName());
            serial->setBaudRate(BAUD19200);
            serial->setFlowControl(FLOW_OFF);
            serial->setParity(PAR_NONE);
            serial->setDataBits(DATA_8);
            serial->setStopBits(STOP_1);
            serial->setTimeout(50);
            emit(openingCOMPortSuccessful(serial->portName()));
            return 1;
    }
    else {
        emit(openingCOMPortFailed(serial->portName()));
        qDebug() << tr("Failed opening %1").arg(serial->portName());
        return 0;
    }
}

//! Checks if a Cube is connected to the openened COM-Port
/*!
  If a Qube5 is receives a 't', it responds with a 'T' character
*/
int CubeCommunication::ConnectionTest() {
    int maxRetries = 10;
    qDebug()<<"ConnectionTest";

    if(!serial->isOpen())
        return 0;

    char c; //Flush the serial input buffer
    //while(this->serial->getChar(&c));
    serial->flush();

    serial->putChar('t'); //Test Mode: send a 't' to the Cube, Cube has to reply with a 'T'

    qDebug("t has been send");
    int out_time = 0;
    c = 0;
    do {
            serial->getChar(&c) ; //Get Response
            if (c == 0) {
              qDebug("c was zero, maybe a glitch in the matrix?");
              serial->putChar('t');
            }
            out_time++;
            qDebug()<<" Character Received: " << c << " - Time: "<<out_time;
            if(out_time > maxRetries) break;
    }
    while(c != 'T');

    if (out_time > maxRetries) {
        qDebug()<< "Could not find a Cube at Port" << serial->portName();
        return -1; //Test failed
    } else {
        serial->putChar('$'); //Clear the cube
        return 1; //Cube is Connected
    }
    return 1;
}

//! Closes the Serial Connection
int CubeCommunication::ConnectionClose(){
    qDebug("Close COM PORT ");
    serial->close();
    return 1;
}
