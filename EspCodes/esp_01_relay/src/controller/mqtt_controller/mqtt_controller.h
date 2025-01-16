#ifndef MQTT_CONTROLLER
#define MQTT_CONTROLLER

#include <./protocols/mqtt_protocols/mqtt_protocols.h>
#include <./controller/enums/enum_functions.h>
#include <./hardware/relay/relay_esp.h>
#include <sstream>
#include <Arduino.h>

class mqtt_controller
{
    private:
       mqtt_protocols* _mqttBroker;
       enum_functions getMessageFunction(const std::string& message);  
       Relay_esp *_relay;
    public:
        mqtt_controller(mqtt_protocols* mqttBroker, Relay_esp *relay);
        void processMessage(const std::string& message);
};

#endif