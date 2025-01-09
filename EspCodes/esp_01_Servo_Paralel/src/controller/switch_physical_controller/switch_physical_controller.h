#ifndef SWITCH_PHYSICAL_CONTROLLER_H
#define SWITCH_PHYSICAL_CONTROLLER_H

#include "./hardware/switch_physical/switch_physical.h"
#include "./hardware/relay_virtual/relay_virtual.h"
#include <Arduino.h>

class SwitchPhysicalController {
  private:
    SwitchPhysical* switch1;
    bool relayState;
    relay_virtual * _relay;
  public:
    SwitchPhysicalController(SwitchPhysical* s1,relay_virtual *relay);
    void update();
};

#endif
