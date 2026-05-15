#pragma once

#include <stdint.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

#include "BasicRelay.h"

class ParallelRelay
{
public:
    ParallelRelay(gpio_num_t relay1,
                  BasicRelay* relay2,
                  gpio_num_t sw1,
                  gpio_num_t sw2);

    void init();

    void loop();

    void powerOn();
    void powerOff();
    void toggle();

    bool isOn() const;

    void setStateCallback(void (*callback)(bool state));

private:
    void readAndProcess(uint8_t current,
                        uint8_t& last);

private:
    gpio_num_t relay1Pin;

    BasicRelay* relay2;

    gpio_num_t sw1Pin;
    gpio_num_t sw2Pin;

    bool state;

    uint8_t lastSw1;
    uint8_t lastSw2;

    TickType_t lastToggleTick;

    void (*stateCallback)(bool state) = nullptr;
};