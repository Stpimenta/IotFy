#include "BasicRelay.h"

BasicRelay::BasicRelay(gpio_num_t gpio)
{
    pin = gpio;

    state = false;

    gpio_reset_pin(pin);

    gpio_set_direction(
        pin,
        GPIO_MODE_OUTPUT
    );

    powerOff();
}

void BasicRelay::powerOn()
{
    state = true;

    gpio_set_level(pin, 1);
}

void BasicRelay::powerOff()
{
    state = false;

    gpio_set_level(pin, 0);
}

void BasicRelay::toggle()
{
    if (state)
    {
        powerOff();
    }
    else
    {
        powerOn();
    }
}

bool BasicRelay::isOn() const
{
    return state;
}