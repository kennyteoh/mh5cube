#include "SerialPort.h"

// Specify the MSWindows naming scheme (COM1, COM2, ...)
#define _TTY_WIN_
#include "qextserialport/qextserialbase.h"
#include "qextserialport/qextserialport.h"

#include <QString>


SerialPort::SerialPort(QWidget *parent) : QDialog(parent)
{
        setupUi(this);

        serial = new QextSerialPort("COM4");

    /*
        port->setBaudRate(BAUD9600);
        port->setFlowControl(FLOW_OFF);
        port->setParity(PAR_NONE);
        port->setDataBits(DATA_8);
        port->setStopBits(STOP_1);

        if(port->open(QIODevice::ReadWrite))
        {
                qDebug("okay geht");
               port->write("test");
                //timer->start();
                //emit(portOpened());
        }
        else qDebug("geht net");*/


}


void SerialPort::on_openButton_clicked()
{
	// Make sure things are clear
        serial->close();
        emit(portClosed());
	
	// read in all the settings and open the port
        serial->setPortName("COM4");//choosePort->currentText());
	switch(chooseBaudRate->currentIndex())
	{
		case 0:
			serial->setBaudRate(BAUD9600);
			break;
		case 1:
			serial->setBaudRate(BAUD19200);
			break;
		case 2:
			serial->setBaudRate(BAUD38400);
			break;
		case 3:
			serial->setBaudRate(BAUD57600);
			break;
		case 4:
			serial->setBaudRate(BAUD115200);
	}
	serial->setDataBits( (DataBitsType)(chooseDataBits->currentIndex()) );
	serial->setParity( (ParityType)(chooseParity->currentIndex()) );
	serial->setStopBits( (StopBitsType)(chooseStopBits->currentIndex()) );
	serial->setFlowControl( (FlowType)(chooseFlowControl->currentIndex()) );
        serial->setTimeout(100);

        if(serial->open(QIODevice::ReadWrite))
	{
                timer->start();
		emit(portOpened());
                serial->setBaudRate(BAUD9600);
               this->send(8, "test123");
        }
}

void SerialPort::closePort()
{
	serial->close();
	emit(portClosed());
}

void SerialPort::send(int count, char *bytes)
{
        //serial->write(
        //serial->writeData("Test", 5);
        serial->write(bytes);
	serial->flush();
}

// read in up to count bytes
// return the number of bytes read
int SerialPort::receive(int count, char *bytes)
{
        return 1;
//	return serial->readData(bytes, count);
}

void SerialPort::checkPort()
{
	if(serial->bytesAvailable()>0)
	{
		emit(dataReady());
	}
}

