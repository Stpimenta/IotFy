#include "switch_physical_controller.h"

SwitchPhysicalController::SwitchPhysicalController(SwitchPhysical* s1, Relay_esp *relay, mqtt_protocols *mqttProtocols) {
  switch1 = s1;
  _relay = relay;
  relayState = false; 
  _mqttProtocol = mqttProtocols;          // Initially, relay is OFF
}

void SwitchPhysicalController::update() {
  static bool lastSwitch1State = false;


  
  bool currentSwitch1State = switch1->getState();


 // Check if state of any switch has changed
  if (currentSwitch1State != lastSwitch1State) {
    // Toggle the relay state if any switch is toggled
    if (_relay->state) {
      _relay->turnOff();  // If the relay is on, turn it off
      _mqttProtocol->publishMessage("TURN_OFF_RELAY");
      
    } else {
      _relay->turnOn();
      _mqttProtocol->publishMessage("TURN_ON_RELAY");   // If the relay is off, turn it on
    }
  }


  // Save current state for future comparisons
  lastSwitch1State = currentSwitch1State;

}
