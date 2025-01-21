#ifndef MQTT_CONTROLLER
#define MQTT_CONTROLLER

#include <./protocols/mqtt_protocols.h>
#include <./controller/enums/enum_functions.h>



class mqtt_controller
{
    private:
       mqtt_protocols* _mqttBroker;
       enum_functions getMessageFunction(const std::string& message);  // Declarada corretamente aqui
    public:
        mqtt_controller(mqtt_protocols* mqttBroker);
        void processMessage(const std::string& message);
};

#endif