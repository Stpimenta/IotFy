#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
public:
    Led(uint8_t pin);
    void setup();
    void setLedState(bool state);

private:
    uint8_t ledPin;
};

#endif 
