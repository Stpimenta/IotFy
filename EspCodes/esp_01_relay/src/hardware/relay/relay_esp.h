#ifndef RELAY_ESP
#define RELAY_ESP

#include <Arduino.h>

class Relay_esp
{
    private:

    public:
    Relay_esp();
    void turnOn();
    void turnOff();
    void pulse(int time);
    bool state = false;
};


#endif 
