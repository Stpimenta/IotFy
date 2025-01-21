#ifndef SWITCH_PHYSICAL_CONTROLLER_H
#define SWITCH_PHYSICAL_CONTROLLER_H

#include "./hardware/switch_physical/switch_physical.h"
#include "./hardware/relay_serial/relay_serial.h"
#include "protocols/mqtt_protocols.h"
#include <Arduino.h>

class SwitchPhysicalController {
  private:
    SwitchPhysical* switch1;
    bool relayState;
    relay_serial * _relay;
    mqtt_protocols * _mqttProtocols;

  public:
    SwitchPhysicalController(SwitchPhysical* s1, relay_serial *relay, mqtt_protocols *mqttProtocols);
    void update();
};

#endif
