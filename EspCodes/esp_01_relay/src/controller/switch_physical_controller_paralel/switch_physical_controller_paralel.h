#ifndef SWITCH_PHYSICAL_CONTROLLER_PARALEL_H
#define SWITCH_PHYSICAL_CONTROLLER_PARALEL_H

#include "./hardware/switch_physical/switch_physical.h"
#include "./hardware/relay/relay_esp.h"
#include <Arduino.h>

class SwitchPhysicalParalelController {
  private:
    SwitchPhysical* switch1;
    SwitchPhysical* switch2;
    bool relayState;
    Relay_esp* _relay;
  public:
    SwitchPhysicalParalelController(SwitchPhysical* s1, SwitchPhysical* s2, Relay_esp *relay);
    void update();
};

#endif
