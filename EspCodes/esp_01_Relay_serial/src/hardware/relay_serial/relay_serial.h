#ifndef RELAY_SERIAL
#define RELAY_SERIAL

#include <Arduino.h>

class relay_serial
{
    private:

    public:
    relay_serial();
    void turnOn();
    void turnOff();
    void reverse_state();
    void pulse(int time);
    bool state = false;
};


#endif 
