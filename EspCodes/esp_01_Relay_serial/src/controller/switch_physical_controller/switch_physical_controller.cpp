#include "switch_physical_controller.h"

SwitchPhysicalController::SwitchPhysicalController(SwitchPhysical* s1, relay_serial *relay, mqtt_protocols *mqttProtocols) {
  switch1 = s1;
  _relay = relay;
  _mqttProtocols = mqttProtocols;
}

void SwitchPhysicalController::update() {
  static bool lastSwitch1State = true;
  bool currentSwitch1State = switch1->getState();


 // Check if state of any switch has changed
  if (currentSwitch1State != lastSwitch1State) {
    // Toggle the relay state if any switch is toggled
    if (_relay->state) {
      _relay->turnOff();  // If the relay is on, turn it off
      _mqttProtocols->publishMessage("TURN_OFF_RELAY");
    } else {
      _relay->turnOn();   // If the relay is off, turn it on
      _mqttProtocols->publishMessage("TURN_ON_RELAY");
    }
  }


  // Save current state for future comparisons
  lastSwitch1State = currentSwitch1State;

}
