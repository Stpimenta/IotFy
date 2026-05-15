#include "ParallelRelay.h"

constexpr TickType_t debounceTicks = pdMS_TO_TICKS(200);

ParallelRelay::ParallelRelay(gpio_num_t relay1,
                             BasicRelay* relay2,
                             gpio_num_t sw1,
                             gpio_num_t sw2)
{
    relay1Pin = relay1;

    this->relay2 = relay2;

    sw1Pin = sw1;
    sw2Pin = sw2;

    state = false;

    lastSw1 = 1;
    lastSw2 = 1;

    lastToggleTick = 0;
}

void ParallelRelay::init()
{
    // relay 1
    gpio_reset_pin(relay1Pin);

    gpio_set_direction(
        relay1Pin,
        GPIO_MODE_OUTPUT
    );

    gpio_set_level(relay1Pin, 0);

    // switches
    gpio_reset_pin(sw1Pin);

    gpio_set_direction(
        sw1Pin,
        GPIO_MODE_INPUT
    );

    gpio_pullup_en(sw1Pin);

    gpio_reset_pin(sw2Pin);

    gpio_set_direction(
        sw2Pin,
        GPIO_MODE_INPUT
    );

    gpio_pullup_en(sw2Pin);
}

void ParallelRelay::loop()
{
    uint8_t sw1 = gpio_get_level(sw1Pin);
    uint8_t sw2 = gpio_get_level(sw2Pin);

    readAndProcess(sw1, lastSw1);
    readAndProcess(sw2, lastSw2);
}

void ParallelRelay::readAndProcess(uint8_t current,
                                   uint8_t& last)
{
    TickType_t now = xTaskGetTickCount();

    if (current != last)
    {
        last = current;

        if ((now - lastToggleTick) < debounceTicks)
        {
            return;
        }

        lastToggleTick = now;

        toggle();
    }
}

void ParallelRelay::toggle()
{
    state = !state;

    gpio_set_level(relay1Pin, state);

    if (relay2)
    {
        if (state)
        {
            relay2->powerOn();
        }
        else
        {
            relay2->powerOff();
        }
    }

    if (stateCallback)
    {
        stateCallback(state);
    }
}

void ParallelRelay::powerOn()
{
    state = true;

    gpio_set_level(relay1Pin, 1);
}

void ParallelRelay::powerOff()
{
    state = false;

    gpio_set_level(relay1Pin, 0);
}

bool ParallelRelay::isOn() const
{
    return state;
}

void ParallelRelay::setStateCallback(void (*callback)(bool state))
{
    stateCallback = callback;
}