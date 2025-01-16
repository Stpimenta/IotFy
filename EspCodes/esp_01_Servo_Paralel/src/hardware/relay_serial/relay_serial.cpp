#include "relay_serial.h"

uint8_t relayOff[] = {0xA0, 0x01, 0x00, 0xA1};
uint8_t relayOn[] = {0xA0, 0x01, 0x01, 0xA2};

relay_serial::relay_serial() {
    state = false;
    turnOff();
}


void relay_serial::turnOn() {
  Serial.write(relayOn, 4);  
  state = true;         
}


void relay_serial::turnOff() {
  Serial.write(relayOff, 4); 
  state = false; 
}

void relay_serial::pulse(int time) {
  turnOn(); 
  delay(time);  
  turnOff(); 
}
