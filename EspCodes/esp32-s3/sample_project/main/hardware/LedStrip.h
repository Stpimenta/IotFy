#pragma once

#include "led_strip.h"
#include "driver/gpio.h"

class LedStrip {
public:
    enum Effect {
        SOLID,
        FADE,
        RAINBOW
    };

    struct State {
        Effect effect;
        uint8_t r, g, b;
        uint8_t brightness;
        uint8_t velocity;
    };

    LedStrip(gpio_num_t pin, int count);

    void begin();

    void setEffect(Effect e);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setBrightness(uint8_t b);
    void setVelocity(uint8_t v);

    State getState() const;

    void start();

private:
    void taskLoop();

    gpio_num_t _pin;
    int _count;
    led_strip_handle_t _strip;

    Effect _effect;

    uint8_t _r, _g, _b;
    uint8_t _brightness;
    uint8_t _velocity;

    static void taskWrapper(void *arg);
};