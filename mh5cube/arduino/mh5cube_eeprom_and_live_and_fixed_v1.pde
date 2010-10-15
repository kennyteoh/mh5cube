/*
  Author: Marcel Jager 
  Date  : August/september/october 2010
 
  Description:   Controlling a 5x5x5 ledcube with an arduino mega
       port 22 till 46 are for the individual leds 
       port 48 till 52 are for the layers

       All the leds are directly controlled by the Arduino Mega. 
       The layers are controlled by a Darlington Array ULN2803
 
       port 3 to read out the button via interrupt 1
       port 6 to light up the green led
       port 7 to light up the red led
       
       port 20 SDA en port 21 SCL 
       
   Based on code from instructables.com 4x4x4 cube
   4x4x4 LED Cube project By Christian Moen 2008 (chr@syntaks.org)
 */
#include <Wire.h>
#include <FlexiTimer2.h>

//Variables for keeping and showing the program mode 
const int buttonPin = 3;    //This pin will be HIGH when the button is pressed
const int ledGreen = 6 ;    //This pin will be HIGH in run mode and light the green led
const int ledRed = 7;       //This pin will be HIGH in program mode and light the red led
volatile int previousState = 0;        // The previous state of the button

const int MODE_OFF = 0;        // The mode of the program were no action is taken, only monitoring the button
const int MODE_PROGRAM = 1;    // The mode of the program were command are taken from the serial port to program and for example live demo the cube
const int MODE_RUN = 2;        // The mode of the program where no commands are taken only fixed effects and/or store images are shown.
volatile int programMode = 0;           // The current mode of the program. Can be toggle by pushing the button;

//Cube variables
const int START_PIN = 22;                      //First pin to control the leds in one layer
const int NUMBER_OF_LEDS = 25;
const int layerPins[] = { 48, 49, 50, 51, 52}; //The pins to control the layer

// *** Cube buffer ***
// The 3D image displayed on the cube is buffered in a 2d array 'cube'.
// The 1st dimension in this array is the Z axis of the cube.
// The 2nd dimension of the array is the Y axis.
// Each byte is a stripe of leds running along the X axis at the given  Z and Y coordinates.
// Only the 5 lower bits are used, since the cube is only 5x5x5.
// This buffer design was chosen to have code compatability with a 8x8x8 cube.
// "volatile" makes the variables reachable from within the interrupt functions
volatile byte cube[5][5];

// We sometimes want to draw into a temporary buffer so we can modify it before writing it to the cube buffer.
// e.g. invert, flip, reverse the cube..
volatile byte tmpcube[5][5];

// What layer the interrupt routine is currently showing.
volatile byte current_layer;

volatile int layer = 0;        //The current layer being used in the communication process
volatile int ledx = 0;
volatile int ledy = 0;

//int idleCounter = 0;
volatile int currentEffect = 0;
volatile boolean showEffects = false;
volatile boolean loopEffects = false;
volatile boolean showAllEffects = false;
volatile boolean showLiveMode = false;

volatile boolean buttonPressed = false;

volatile unsigned int numRows = 0;      //Counter of number of pictures to be programmed into the eeproms
volatile unsigned int pauseTime = 0;

volatile int currentImage = 0;

#define BOUNCE_DURATION 200   // define an appropriate bounce time in ms for your switches
volatile unsigned long bounceTime=0; // variable to hold ms count to debounce a pressed switch

void setup() {
  setupCube();

  //Start with empty cube
  fill(0x00);

  Wire.begin();  //Enable the i2c bus for all modes
  
  attachInterrupt(1, handleButtonRunMode, RISING);
}

void loop() {

  //Read state of button   
//  handleButton();

  //Handle current mode
  handleMode();
}

void handleButtonRunMode() {
// this is the interrupt handler for button presses
// it ignores presses that occur in intervals less then the bounce time
   if (abs(millis() - bounceTime) > BOUNCE_DURATION) {
      buttonPressed = true;

      //Change into a new mode
      int oldProgramMode = programMode;
      programMode++;
      if (programMode > MODE_RUN) {
          programMode = MODE_OFF; 
      }
      switchMode(oldProgramMode, programMode);

     bounceTime = millis();  // set whatever bounce time in ms is appropriate
   }
}


//Handle the state of the button to set the correct mode
void handleButton() {
  // read the state of the pushbutton value:
  int buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH ) {
    delay(200);
    if (buttonState == HIGH) {
      if (previousState != buttonState) {
        //Change into a new mode
        int oldProgramMode = programMode;
        programMode++;
        if (programMode > MODE_RUN) {
         programMode = MODE_OFF; 
        }
        switchMode(oldProgramMode, programMode);
        previousState = HIGH;
        delay(200);
      }
    }
  } else {
    previousState = LOW;
  }
}

//Handle the mode
void handleMode() {
  switch(programMode) {
    case MODE_OFF:
      handleModeOff(); 
      break;
    case MODE_PROGRAM:
      handleModeProgram();
      break;
    case MODE_RUN:
      handleModeRun(); 
      break;
    default:
      programMode = MODE_OFF;
  }
}

//Handle the mode off
void handleModeOff() {
  delay(250);
}

//Handle the run mode
void handleModeRun() {
  //showFixedEffects();
  
  if (numRows == 12345) {
    readNumRowsFromEeprom();
  }
  
  if (numRows > 1) {
    readFromEeprom(currentImage);
    currentImage = currentImage + 1;
    if (currentImage >= numRows) currentImage = 0;
    delay(pauseTime * 30);
  }
  
}

//Handle the program mode
void handleModeProgram() {
  showFixedEffects();
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    handleCommunication( Serial.read() );
  }
}

//Loop through the fixed effects
void showFixedEffects() {
  if (showEffects) {
    launch_effect(currentEffect);
    
    //For showing effects only once
    if (!loopEffects && !showAllEffects) {
      showEffects = false;
      fill(0x00);
      return;
    }
    
    if (showAllEffects) {
      currentEffect++;
      if (currentEffect == 3) currentEffect = 4;
    }
    
    //Wrap around if were in a loop
    if (currentEffect >= 13) {
      if (loopEffects) {
        currentEffect = 0;
      } else {
        if (showAllEffects) {
          //Show all effects only once
          showEffects = false;
          fill(0x00);
          return;
        }
      }
    }
  } 
}


//Setup ports for leds and layers
void setupCube() {
  int portNr = 0;
  for (portNr = START_PIN; portNr <= (START_PIN + NUMBER_OF_LEDS + 6) ; portNr++) {
    pinMode(portNr, OUTPUT);
  }
  current_layer = 0;
  
  // initialize the LED pins as an output:
  pinMode(ledGreen, OUTPUT);      
  pinMode(ledRed, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}


void multiplex_ledcube() {
  //Disable all layers while we are drawing a new layer
  disable_all_layers();

  //Draw current layer
  int port = START_PIN;
  for (int y = 0; y < 5; y++) {
    for (int x= 0; x < 5; x++) {
      //YES, I know digitalWrite and bitRead are slow,
      // but hey this is the Arduino style of doing things (and I'm lazy)
      digitalWrite(port, bitRead(cube[current_layer][y], x)); 
      port++;
    }
  }

  //Enable current layer
  digitalWrite(layerPins[current_layer], HIGH);

  if (current_layer++ >= 4) {
    current_layer = 0;
  }
}

void disable_all_layers() {
  digitalWrite(layerPins[0], LOW);
  digitalWrite(layerPins[1], LOW);
  digitalWrite(layerPins[2], LOW);
  digitalWrite(layerPins[3], LOW);
  digitalWrite(layerPins[4], LOW);
}

//handle serial communication protocol
void handleCommunication(int incomingByte) {
  int nrEffect = 0;
  
  // PC ask us if we are alive
  if (incomingByte == 't') {
    Serial.print('T');
  }
  
  //PC want to program cube-images in eeprom
  if (incomingByte == '#') {
    handleProgrammingEeprom();
  }
  
  //Show a fixed effect  
  if (incomingByte == 'z') {
    showEffects = true;
    fill(0x00);

    //Wait for the kind of effect to been shown
    while(!Serial.available()) {
      delay(250);
    }
    if (Serial.available()) {
      nrEffect = Serial.read();
    }
    /*
      0x00 Show all effects once
      0x10 Show all effect in loop
      0x01 thru 0x0C show the individual fixed effect once
      0x11 thru 0x1C show the individual fixed effect in loop 
    */
    loopEffects = bitRead(nrEffect,4);
    bitClear(nrEffect,4);
    
    if (nrEffect == 0) {
      currentEffect = 0;
      showAllEffects = true;
    } else if ((nrEffect > 0) && (nrEffect <= 14)) {
      currentEffect = nrEffect - 1;
      showAllEffects = false;
    }
  }

  // Stop the fixed effects
  if (incomingByte == 'Z') {
    showEffects = false;
    fill(0x00);
  }  

  //Clear the cube
  if (incomingByte == '$') {
    fill(0x00);
    currentEffect = 0;
  }

  //Enter the live-mode 
  if (incomingByte == 'l') {
    fill(0x00);
    showLiveMode = true;
  }
  
  //Leavte the live-mode
  if (incomingByte == 'L') {
    fill(0x00);
    showLiveMode = true;
  }
  
  if (incomingByte == '*' && showLiveMode) {
    processLiveMode();
  }
}




