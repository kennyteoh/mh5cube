#include <Wire.h>

#define disk1 0x50 //Address of first 24LC256 eeprom chip
#define disk2 0x51 //Address of second 24LC56 eeprom chip

#define IMAGE_SIZE 26                              //The size of the image
#define IMAGES_NR_PER_EEPROM 1000                  //Number of images per eeprom stored 
#define MAX_NR_IMAGES IMAGES_NR_PER_EEPROM * 2     //The maximum number of images that can be stored in the eeprom

/*
 * Code taken from the article "Expanding the Arduino storage with an external I2C EEPROM chip (24LC256)": http://10kohms.com/arduino-external-eeprom-24lc256
 *  and code from Arduino Forum "24LC256 overwrite and read all sketches": http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1280095224
 * 
 * cube images are stored in an 26-byte sequence. 25 bytes of cube data, also used in the live mode and 1 byte of timing data.
 * 
 * This 24LC256 has a page size of 32 bytes. We can't "cross" this pageboundary. Meaning we can't sequentially store our image-date of 26 bytes.
 * Therefore eache image is stored in one page of 32 bytes.
 * 
 * One 24LC256 provide room for 256 / 8 * 1024 / 32 = 1024 images
 * but we have got two 24LC256 so there is room for 2 * 1024 = 2048 images!!
 * For now we store 1000 images in each chip.
 *
 * First entry is reserved for our data.
 * Layout first entry on eeprom 1:
 * byte  0   MSB of numrows
 * byte  1   LSB of numrows
 * 
 * Rest to be determined
 */

void handleProgrammingEeprom() {
  
  handleNumRows();
  if (numRows > 0) {
    writeNumRowsToEeprom();
  }
 
   
  for (int i = 0; i < numRows; i++) {
    //Toggle leds during programming
    if (i % 2 > 0) { 
      setRedLedOn(); 
    }  else { 
      setGreenLedOn(); 
    } 
    
    handleImageFromPC(i);
    Serial.print('~');    //Send OK-sign for this image
  }
  
  setRedLedOn();
  Serial.print('C');      //Send end of communication
  
  //Wait for 'R'
  waitForSerial();
  Serial.read();
}

/*
 * Handle first part of communication , the sending of the number of rows to be send from the PC
 * function wil set numRows to -1 if there was an error during communication.
 */
void handleNumRows() {
  unsigned int incomingByte;
  
  //Wait for '*'
  waitForSerial();
  incomingByte = Serial.read();
  if (incomingByte != '*') {
    Serial.print('C'); //End Communication with PC
    numRows = -1;
    return;
  }
  
  //Read NumRows LSB
  waitForSerial();
  incomingByte = Serial.read();
  numRows = incomingByte;
  
  //Read NumRows MSB
  waitForSerial();
  incomingByte = Serial.read();
  numRows += (incomingByte << 8);
}

/*
 * Handle one image send from the PC. One image has a size of 28 bytes.
 * layout of sent figure:
 *
 *      0    1 till 25   26             27 
 *     '*'     image    time (0..20)  '~'
 */
void handleImageFromPC(int imageNr) {
  unsigned int incomingByte;
  
  if (imageNr > MAX_NR_IMAGES) {
    return;
  }
  
  //Read data from PC
  byte imageData[26];
  
  //Receive '*'
  waitForSerial();
  incomingByte = Serial.read();
  
  if (incomingByte != '*') {
    return;
  }
  
  for (int i = 0; i < 26; i++) {
    waitForSerial();
    incomingByte = Serial.read();
    imageData[i] = incomingByte;
  }
  
  //Receive '~'
  waitForSerial();
  incomingByte = Serial.read();
  
  if (incomingByte != '~') {
    return;
  }

  storeToEeprom(imageNr, imageData);  
}

void storeToEeprom(int imageNr, byte *imageData) {
  //Determine which eeprom we're going to write to
  int deviceAddress = 0;
  unsigned int address = 0;
  if (imageNr <= IMAGES_NR_PER_EEPROM) {  //First 1000 on eeprom 1
    deviceAddress = disk1;
    //Address on eeprom 1 where image is to be stored
    address = (imageNr + 1) * 32;
  } else {
    deviceAddress = disk2;
    //Address on eeprom 2 where image is to be stored
    address = (imageNr - IMAGES_NR_PER_EEPROM + 1) * 32;
  }
  
  //Write data to eeprom
  Wire.beginTransmission(deviceAddress);
  Wire.send(highByte(address));    //MSB
  Wire.send(lowByte(address));    //LSB
  for (int i = 0; i < 26; i++) {
    Wire.send(imageData[i]);
  }
  Wire.endTransmission();
  
  delay(5);
}

void readFromEeprom(int imageNr) {
  //Determine which eeprom we're going to read to (copy of write routine)
  int deviceAddress = 0;
  unsigned int address = 0;
  if (imageNr <= IMAGES_NR_PER_EEPROM) {  //First 1000 on eeprom 1
    deviceAddress = disk1;
    //Address on eeprom 1 where image is stored
    address = (imageNr + 1) * 32;
  } else {
    deviceAddress = disk2;
    //Address on eeprom 2 where image is stored
    address = (imageNr - IMAGES_NR_PER_EEPROM + 1) * 32;
  }
  
  //Request data from eeprom
  Wire.beginTransmission(deviceAddress);
  Wire.send(highByte(address));    //MSB
  Wire.send(lowByte(address));    //LSB
  Wire.endTransmission();
  
  Wire.requestFrom(deviceAddress, IMAGE_SIZE);  //Request imagedata
  
  //Read data from eeprom into buffer
  byte buffer[IMAGE_SIZE];
  if (Wire.available()) { 
    for (int i = 0; i < IMAGE_SIZE; i++ ) {
        buffer[i] = Wire.receive();
    }
  } 
  
  //Convert image buffer data into 'real' cube data
  pauseTime = buffer[IMAGE_SIZE - 1];
  int c = 0;
  for (int z = 0; z < 5; z++) {
    for (int y = 4; y >= 0; y--) {
      cube[z][y] = buffer[c];
      c = c + 1;
    }
  }
}


/*
 * Write number of images to eeprom 1 in first two bytes
 */
void writeNumRowsToEeprom() {
  unsigned int address = 0;
  
  Wire.beginTransmission(disk1);
  Wire.send(highByte(address));    //MSB
  Wire.send(lowByte(address));    //LSB
  
  //Send the number of images
  Wire.send(highByte(numRows));
  Wire.send(lowByte(numRows));

  Wire.endTransmission();
  
  delay(5);
}

/*
 * Get number of images from eeprom 1 in first two bytes (MSB / LSB)
 */
void readNumRowsFromEeprom() {
  unsigned int address = 0;
  
  Wire.beginTransmission(disk1);
  Wire.send(highByte(address));    //MSB
  Wire.send(lowByte(address));    //LSB
  Wire.endTransmission();
  
  Wire.requestFrom(disk1, 2);  //Request two bytes
  
  if (Wire.available()) {
    numRows = ((unsigned int)Wire.receive()) << 8 ; //MSB
    numRows += Wire.receive();            //LSB
  } else {
    numRows = -1;
  }
}

void waitForSerial() {
    while(!Serial.available()) {
      delay(250);
    }
}


