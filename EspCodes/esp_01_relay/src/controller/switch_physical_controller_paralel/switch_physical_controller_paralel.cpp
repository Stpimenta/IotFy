#include "switch_physical_controller_paralel.h"
#include "iostream"
SwitchPhysicalParalelController::SwitchPhysicalParalelController(SwitchPhysical* s1, SwitchPhysical* s2, Relay_esp *relay) {
  switch1 = s1;
  switch2 = s2;
  _relay = relay;
  relayState = false;           // Initially, relay is OFF
}

void SwitchPhysicalParalelController::update() {
  static bool lastSwitch1State = false;
  static bool lastSwitch2State = false;

  
  bool currentSwitch1State = switch1->getState();
  bool currentSwitch2State = switch2->getState();

 // Check if state of any switch has changed
  if (currentSwitch1State != lastSwitch1State || currentSwitch2State != lastSwitch2State) {
    // Toggle the relay state if any switch is toggled
    if (_relay->state) {
      _relay->turnOff();  // If the relay is on, turn it off
    } else {
      _relay->turnOn();   // If the relay is off, turn it on
    }
  }


  // Save current state for future comparisons
  lastSwitch1State = currentSwitch1State;
  lastSwitch2State = currentSwitch2State;


}
