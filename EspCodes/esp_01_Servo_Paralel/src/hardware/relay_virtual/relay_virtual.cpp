#include "relay_virtual.h"


relay_virtual::relay_virtual(mqtt_protocols *mqttBroker, std::string espRelay) {
    _mqttBroker = mqttBroker;
    state = false;
    _espRelay = espRelay;
}


void relay_virtual::turnOn() {
    state = true; // Corrigido para definir o estado como "ligado"
    _mqttBroker->publishMessageForOtherEsp(_espRelay,"TURN_ON_RELAY");
}

void relay_virtual::turnOff() {
    state = false;
    _mqttBroker->publishMessageForOtherEsp(_espRelay,"TURN_OFF_RELAY");
}

void relay_virtual::paralel() {
    _mqttBroker->publishMessageForOtherEsp(_espRelay,"REVERSE_STATE");
}

void relay_virtual::pulse(int time) {
  turnOn(); 
  delay(time);  
  turnOff(); 
}
