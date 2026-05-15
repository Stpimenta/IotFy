#pragma once

#include <stdint.h>
#include <driver/gpio.h>
#include <driver/rmt_tx.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class StripLed
{
public:
    enum Effect
    {
        NONE,
        RAINBOW,
        FADE
    };

    StripLed(gpio_num_t pin, uint16_t count);

    void init();
    void startTask();

    void loop();

    void powerOn();
    void powerOff();

    bool isOn() const;

    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setBrightness(uint8_t b); // 0–100
    void setEffect(Effect e);

private:
    void sendFrame();
    void applyRainbow();
    void applyFade();

    static void taskHandler(void* arg);

private:
    gpio_num_t pin;
    uint16_t count;

    bool state;
    uint8_t brightness;

    Effect effect;
    uint8_t hue;

    uint8_t* pixels;

    rmt_channel_handle_t tx_channel = nullptr;
    TaskHandle_t taskHandle = nullptr;
};