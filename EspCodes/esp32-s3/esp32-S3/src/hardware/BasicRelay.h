#pragma once

#include "driver/gpio.h"

class BasicRelay
{
public:
    BasicRelay(gpio_num_t gpio);

    void powerOn();

    void powerOff();

    void toggle();

    bool isOn() const;

private:
    gpio_num_t pin;

    bool state;
};