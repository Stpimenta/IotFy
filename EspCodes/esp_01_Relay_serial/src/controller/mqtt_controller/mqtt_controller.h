#ifndef MQTT_CONTROLLER
#define MQTT_CONTROLLER

#include <./protocols/mqtt_protocols.h>
#include <./controller/enums/enum_functions.h>
#include <./hardware/relay_serial/relay_serial.h>
#include <sstream>
#include <Arduino.h>

class mqtt_controller
{
    private:
       mqtt_protocols* _mqttBroker;
       enum_functions getMessageFunction(const std::string& message);  
       relay_serial *_relay;
    public:
        mqtt_controller(mqtt_protocols* mqttBroker, relay_serial *relay);
        void processMessage(const std::string& message);
};

#endif