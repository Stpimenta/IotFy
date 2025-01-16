#ifndef SWITCH_PHYSICAL_CONTROLLER_H
#define SWITCH_PHYSICAL_CONTROLLER_H

#include "./hardware/switch_physical/switch_physical.h"
#include "./hardware/relay/relay_esp.h"
#include <Arduino.h>

class SwitchPhysicalController {
  private:
    SwitchPhysical* switch1;
    bool relayState;
    Relay_esp * _relay;
  public:
    SwitchPhysicalController(SwitchPhysical* s1,Relay_esp *relay);
    void update();
};

#endif
