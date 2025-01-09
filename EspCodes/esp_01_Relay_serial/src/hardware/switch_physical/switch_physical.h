#ifndef SWITCH_PHYSICAL_H
#define SWITCH_PHYSICAL_H

#include <Arduino.h>

class SwitchPhysical {
  
  private:
    uint8_t gpioPin; 
    bool state;       
    void updateState();

  public:

    SwitchPhysical(uint8_t pin);
    bool getState();
};

#endif
