#include "LedStrip.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>

LedStrip::LedStrip(gpio_num_t pin, int count)
{
    _pin = pin;
    _count = count;
    _strip = nullptr;

    _effect = SOLID;
    _r = _g = _b = 0;
    _brightness = 100;
    _velocity = 50;
}

void LedStrip::begin()
{
    led_strip_config_t config = {};
    config.strip_gpio_num = _pin;
    config.max_leds = _count;
    config.led_pixel_format = LED_PIXEL_FORMAT_GRB;
    config.led_model = LED_MODEL_WS2812;
    config.flags.invert_out = false;

    led_strip_rmt_config_t rmt = {};
    rmt.resolution_hz = 10 * 1000 * 1000;
    rmt.flags.with_dma = false;

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&config, &rmt, &_strip));
}

void LedStrip::setEffect(Effect e) { _effect = e; }
void LedStrip::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    _r = r; _g = g; _b = b;
}

void LedStrip::setBrightness(uint8_t b)
{
    _brightness = b;
}

void LedStrip::setVelocity(uint8_t v)
{
    _velocity = v;
}

void LedStrip::start()
{
    xTaskCreate(taskWrapper, "led_task", 4096, this, 5, nullptr);
}

void LedStrip::taskWrapper(void *arg)
{
    ((LedStrip*)arg)->taskLoop();
}

static uint32_t wheel(int pos)
{
    pos = 255 - pos;

    if (pos < 85)
        return ((255 - pos * 3) << 16) | (0 << 8) | (pos * 3);

    if (pos < 170) {
        pos -= 85;
        return (0 << 16) | ((pos * 3) << 8) | (255 - pos * 3);
    }

    pos -= 170;
    return ((pos * 3) << 16) | ((255 - pos * 3) << 8) | 0;
}

void LedStrip::taskLoop()
{
    int hue = 0;

    while (1) {

        int delay_ms = 50 - (_velocity / 2);
        if (delay_ms < 5) delay_ms = 5;

        float br = _brightness / 100.0f;

        if (_effect == SOLID) {

            for (int i = 0; i < _count; i++) {
                led_strip_set_pixel(_strip, i,
                    _r * br,
                    _g * br,
                    _b * br
                );
            }
            led_strip_refresh(_strip);
        }

        else if (_effect == FADE) {

            static int dir = 1;
            static int val = 0;

            val += dir * 5;
            if (val >= 255) { val = 255; dir = -1; }
            if (val <= 0)   { val = 0; dir = 1; }

            for (int i = 0; i < _count; i++) {
                led_strip_set_pixel(_strip, i,
                    (_r * val / 255) * br,
                    (_g * val / 255) * br,
                    (_b * val / 255) * br
                );
            }
            led_strip_refresh(_strip);
        }

        else if (_effect == RAINBOW) {

            for (int i = 0; i < _count; i++) {
                int color = wheel((i * 256 / _count + hue) & 255);

                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;

                led_strip_set_pixel(_strip, i,
                    r * br,
                    g * br,
                    b * br
                );
            }

            led_strip_refresh(_strip);
            hue = (hue + 2) % 256;
        }

        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

LedStrip::State LedStrip::getState() const
{
    return State{
        _effect,
        _r,
        _g,
        _b,
        _brightness,
        _velocity
    };
}