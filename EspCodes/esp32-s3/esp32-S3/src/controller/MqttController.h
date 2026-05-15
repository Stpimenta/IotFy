#pragma once

#include "hardware/ParallelRelay.h"
#include "hardware/BasicRelay.h"
#include "infrastructure/mqtt/MqttClient.h"
#include "hardware/StripLed.h"

class MqttController
{
public:
    MqttController(ParallelRelay* light1,
                   BasicRelay* light2,
                   MqttClient* mqtt,
                   StripLed* led);

    void processMessage(const char* message);

private:
    ParallelRelay* light1;
    BasicRelay* light2;
    MqttClient* mqtt;
    StripLed* led;
};