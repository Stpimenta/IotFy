#ifndef MQTT_CONTROLLER
#define MQTT_CONTROLLER

#include <./protocols/mqtt_protocols.h>
#include <./controller/enums/enum_functions.h>
#include <hardware/strip_led_hardware/strip_led_hardware.h>
#include <hardware/enum/effects_enum.h>


class mqtt_controller
{
    private:
       mqtt_protocols* _mqttBroker;
       enum_functions getMessageFunction(const std::string& message); 
       strip_led_hardware *_stripLed;
    //    effects  *_currentEffect;

    public:
        mqtt_controller(mqtt_protocols* mqttBroker, strip_led_hardware *_stripLed);
        void processMessage(const std::string& message);
};

#endif