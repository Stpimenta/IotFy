#include "switch_physical.h"


SwitchPhysical::SwitchPhysical(uint8_t pin) {
  gpioPin = pin;  
  pinMode(gpioPin, INPUT_PULLUP); 
  digitalWrite(gpioPin, LOW); 
  state = false;  
}


void SwitchPhysical::updateState() {
  state = digitalRead(gpioPin);  
}

bool SwitchPhysical::getState() {
  updateState();
  return state;
}
