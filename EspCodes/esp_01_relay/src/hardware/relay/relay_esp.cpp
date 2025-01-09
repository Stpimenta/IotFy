#include "relay_esp.h"


#define Rele 0

Relay_esp::Relay_esp() {
    state = false;
    pinMode(Rele,OUTPUT);
    turnOff();
}


void Relay_esp::turnOn() {
  digitalWrite(Rele, LOW);
  state = true;         
}


void Relay_esp::turnOff() {
  digitalWrite(Rele, HIGH);
  state = false; 
}

void Relay_esp::pulse(int time) {
  turnOn(); 
  delay(time);  
  turnOff(); 
}
