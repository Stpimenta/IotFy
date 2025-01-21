#ifndef SWITCH_PHYSICAL_CONTROLLER_H
#define SWITCH_PHYSICAL_CONTROLLER_H

#include "./hardware/switch_physical/switch_physical.h"
#include "./hardware/relay/relay_esp.h"
#include "./protocols/mqtt_protocols/mqtt_protocols.h"
#include <Arduino.h>

class SwitchPhysicalController {
  private:
    SwitchPhysical* switch1;
    mqtt_protocols * _mqttProtocol;
    bool relayState;
    Relay_esp * _relay;
  public:
    SwitchPhysicalController(SwitchPhysical* s1,Relay_esp *relay, mqtt_protocols *mqttProtocol);
    void update();
};

#endif
