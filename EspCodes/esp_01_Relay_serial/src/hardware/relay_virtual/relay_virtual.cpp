#include "relay_virtual.h"


relay_virtual::relay_virtual(mqtt_protocols *mqttBroker, std::string espRelay) {
    _mqttBroker = mqttBroker;
}


void relay_virtual::turnOn() {
  _mqttBroker->publishMessageForOtherEsp(_espRelay,"TURN_ON_RELAY");
  state = true;         
}


void relay_virtual::turnOff() {
  _mqttBroker->publishMessageForOtherEsp(_espRelay,"TURN_OFF_RELAY"); 
  state = false; 
}

void relay_virtual::pulse(int time) {
  turnOn(); 
  delay(time);  
  turnOff(); 
}
