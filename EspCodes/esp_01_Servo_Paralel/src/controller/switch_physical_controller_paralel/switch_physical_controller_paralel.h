#ifndef SWITCH_PHYSICAL_CONTROLLER_PARALEL_H
#define SWITCH_PHYSICAL_CONTROLLER_PARALEL_H

#include "./hardware/switch_physical/switch_physical.h"
#include "./hardware/relay_serial/relay_serial.h"
#include <Arduino.h>

class SwitchPhysicalParalelController {
  private:
    SwitchPhysical* switch1;
    SwitchPhysical* switch2;
    bool relayState;
    relay_serial * _relay;
  public:
    SwitchPhysicalParalelController(SwitchPhysical* s1, SwitchPhysical* s2, relay_serial *relay);
    void update();
};

#endif
