#ifndef OPENSERIAL
#define OPENSERIAL

#include <QTimer>
class QextSerialPort;

class SerialPort : public QDialog
{
	Q_OBJECT
	
        public:
		SerialPort(QWidget *parent=0);
                int receive(int count, char *bytes);

	private:
		QextSerialPort *serial;
                QTimer *timer;

	private slots:
                void on_openButton_clicked();
	
	public slots:
		void closePort();
		void send(int count, char *bytes);
		void checkPort();

	signals:
		void portOpened();
		void portClosed();
                void dataReady();


};

#endif

