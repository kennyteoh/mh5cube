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

#include "serialthread.h"
#include <QDebug>


SerialThread::SerialThread(QextSerialPort *port, QByteArray data, int numberOfFigures, QObject *parent) :
        QThread(parent)
{
    this->port = port;
    this->data = data;
    this->numberOfFigures = numberOfFigures;
}


void SerialThread::run() {

    qDebug() << "Programming in Thread: " << numberOfFigures << " Figures";
    emit percentageFinished(0); //Reset ProgressBar
    char c;
    long int out_time = 0;

    while(port->getChar(&c)); //Flush, the port->flush() function doesnt see

    this->msleep(100);
    port->write("#"); //Jump to Bootloader
    this->msleep(100);

    port->write(data.mid(0,3));

    this->msleep(100);

    QByteArray rest = data.mid(3); //Everything starting from index 3

    for(int i = 0; i < numberOfFigures; i++) {
        qDebug()<<"Programming Figure " <<i<< "of "<< numberOfFigures;
        qDebug()<<rest.mid(i*28,28);

        port->write(rest.mid(i*28,28));

        out_time = 0;
        c = 0;
        do{
            port->getChar(&c) ; //gets character, waits until port->timeout was exceeded 10 times
            out_time++;
            qDebug()<<"Char: " << c<< " Time: "<<out_time;
            if(out_time > 10) break; //after 10*timeout
        }
        while(c != '~');

        if(out_time > 10) {
            qDebug() << "Timeout for Figure" << i;
            qDebug() << "Programming failed, reset Cube and retry again";
            emit(programmingFailed());
            return;
        } else {
            int percentage = (int)(((float)(i+1)/numberOfFigures) * 100);
            emit percentageFinished(percentage);
        }
    }

    out_time = 0;

    do{
        port->getChar(&c) ;
        this->usleep(5);
        out_time ++;
        if(out_time > 10) break;
    }
    while(c != 'C');

    if(out_time > 10) {
            qDebug() << "Could not return to MainProgramm";
            qDebug() << "Reset Cube and retry again";
            emit(programmingFailed());
            return;
        }
    
    this->msleep(20);

    port->write("R"); //Back to Main Application
    qDebug() << "Everything sent." << endl;
    emit(programmingSuccessful());


}
