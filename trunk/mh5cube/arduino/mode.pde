void beginModeProgram() {
  currentEffect = 0;
  showEffects = false;
  loopEffects = false;
  showAllEffects = false;
  showLiveMode = false;

  fill(0x00);

  // initialize serial communication at 19200 baud, this is the max speed our virtual Windows 7 instance can handle.
  Serial.begin(19200);
  
  //Setup interrupt to be called each 2 ms. 
  // This give us a refreshrate of 100Hz (1000 / 2 = 500 / 5 layers = 100) 
  FlexiTimer2::set(2, multiplex_ledcube); 
  FlexiTimer2::start();
  fill(0x00);
}

void endModeProgram() {
  //Close serial communication
  Serial.end();
  
  FlexiTimer2::stop();
  fill(0x00);
  disable_all_layers();
}

void beginModeRun() {
  showEffects = true;
  currentEffect = 0;
  showAllEffects = true;
  
  buttonPressed = false;
  
  //Prepare the eeprom data to read the number of rows
  numRows = 12345;
  currentImage = 0;

  //Setup interrupt to be called each 2 ms. 
  // This give us a refreshrate of 100Hz (1000 / 2 = 500 / 5 layers = 100) 
  FlexiTimer2::set(2, multiplex_ledcube); 
  FlexiTimer2::start();
  fill(0x00);
  
  //Attach an interrupt onto the button 
//  attachInterrupt(1, handleButtonRunMode, FALLING);
}

void endModeRun() {
//  detachInterrupt(1);
  
  FlexiTimer2::stop();
  fill(0x00);
  disable_all_layers();
  
  buttonPressed = false;
}


void switchMode(int oldProgramMode, int newProgramMode) {
  if (oldProgramMode == MODE_PROGRAM) {
    endModeProgram();
  } else if (oldProgramMode == MODE_RUN) {
    endModeRun();
  }
  
  if (newProgramMode == MODE_PROGRAM) {
    beginModeProgram();
  } else if (newProgramMode == MODE_RUN) {
    beginModeRun();
  }
  
  setModeLed(newProgramMode);
}

void setModeLed(int programMode) {
  switch (programMode) {
    case MODE_OFF: 
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, LOW);
      break;
    case MODE_PROGRAM:
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledGreen, LOW);  
      break;
    case MODE_RUN: 
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, LOW); 
      break;
    default:
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, HIGH);
  };
}

void setRedLedOn() {
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);  
}

void setGreenLedOn() {
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW); 
}
