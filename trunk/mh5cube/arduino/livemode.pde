//Receive of live-mode data and filling internal cube-array
void processLiveMode() {
  for (int z = 0; z < 5; z++) {
    for (int y = 4; y >= 0; y--) {
      while(!Serial.available()) {
        delay(50);
      }
      cube[z][y] = Serial.read();
    }
  }
  
  while(!Serial.available()) {
    delay(50);
  }
  int endSign = Serial.read();
}
