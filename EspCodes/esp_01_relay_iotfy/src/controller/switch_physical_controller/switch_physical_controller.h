#ifndef SWITCH_PHYSICAL_CONTROLLER_H
#define SWITCH_PHYSICAL_CONTROLLER_H

#include "./hardware/switch_physical/switch_physical.h"
#include "./hardware/relay_serial/relay_serial.h"
#include <Arduino.h>

class SwitchPhysicalController {
  private:
    SwitchPhysical* switch1;
    SwitchPhysical* switch2;
    bool relayState;
    relay_serial * _relay;
  public:
    SwitchPhysicalController(SwitchPhysical* s1, SwitchPhysical* s2, relay_serial *relay);
    void update();
};

#endif
