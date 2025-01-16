#ifndef RELAY_VIRTUAL
#define RELAY_VIRTUAL

#include <Arduino.h>
#include <protocols/mqtt_protocols.h>
class relay_virtual
{
    private:
    mqtt_protocols *_mqttBroker;
    std::string _espRelay;

    public:
    relay_virtual(mqtt_protocols *mqttBroker, std::string espRelay);
    void turnOn();
    void turnOff();
    void pulse(int time);
    bool state = false;
};


#endif 
