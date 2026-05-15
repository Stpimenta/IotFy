#include "MqttController.h"

#include <string.h>
#include "esp_system.h"

MqttController::MqttController(ParallelRelay *light1,
                               BasicRelay *light2,
                               MqttClient *mqtt,
                               LedStrip *led)
{
    this->light1 = light1;
    this->light2 = light2;
    this->mqtt = mqtt;
    this->led = led;
}

void MqttController::processMessage(const char *message)
{
    // =================================
    // LIGHT 1
    // =================================

    if (strcmp(message, "LIGHT1_ON") == 0)
    {
        light1->powerOn();
        mqtt->publishMessage("LIGHT1_ON");
        return;
    }

    if (strcmp(message, "LIGHT1_OFF") == 0)
    {
        light1->powerOff();
        mqtt->publishMessage("LIGHT1_OFF");
        return;
    }

    if (strcmp(message, "LIGHT1_TOGGLE") == 0)
    {
        light1->toggle();
        mqtt->publishMessage("LIGHT1_TOGGLE");
        return;
    }

    if (strcmp(message, "LIGHT1_STATE") == 0)
    {
        mqtt->publishMessage(
            light1->isOn() ? "LIGHT1_ON" : "LIGHT1_OFF");
        return;
    }

    // =================================
    // LIGHT 2
    // =================================

    if (strcmp(message, "LIGHT2_ON") == 0)
    {
        light2->powerOn();
        mqtt->publishMessage("LIGHT2_ON");
        return;
    }

    if (strcmp(message, "LIGHT2_OFF") == 0)
    {
        light2->powerOff();
        mqtt->publishMessage("LIGHT2_OFF");
        return;
    }

    if (strcmp(message, "LIGHT2_STATE") == 0)
    {
        mqtt->publishMessage(
            light2->isOn() ? "LIGHT2_ON" : "LIGHT2_OFF");
        return;
    }

    // =================================
    // LED STRIP (NOVO)
    // =================================

    if (strcmp(message, "LED_ON") == 0)
    {
        led->setBrightness(100);

        auto s = led->getState();
        mqtt->publishMessage("LED_ON:255");
        return;
    }

    if (strcmp(message, "LED_OFF") == 0)
    {
        led->setBrightness(0);

        auto s = led->getState();
        mqtt->publishMessage("LED_OFF:0");
        return;
    }

    if (strcmp(message, "LED_RAINBOW") == 0)
    {
        led->setEffect(LedStrip::RAINBOW);

        mqtt->publishMessage("LED_RAINBOW");
        return;
    }

    if (strcmp(message, "LED_FADE") == 0)
    {
        led->setEffect(LedStrip::FADE);

        mqtt->publishMessage("LED_FADE");
        return;
    }

    if (strcmp(message, "LED_SOLID") == 0)
    {
        led->setEffect(LedStrip::SOLID);

        mqtt->publishMessage("LED_SOLID");
        return;
    }

    if (strncmp(message, "LED_COLOR:", 10) == 0)
    {
        int r, g, b;
        if (sscanf(message, "LED_COLOR:%d,%d,%d", &r, &g, &b) == 3)
        {
            led->setColor((uint8_t)r, (uint8_t)g, (uint8_t)b);

            auto s = led->getState();

            char buffer[64];
            snprintf(buffer, sizeof(buffer),
                     "LED_COLOR:%d,%d,%d",
                     s.r, s.g, s.b);

            mqtt->publishMessage(buffer);
        }
        return;
    }

    if (strncmp(message, "LED_BRIGHTNESS:", 15) == 0)
    {
        int b;
        if (sscanf(message, "LED_BRIGHTNESS:%d", &b) == 1)
        {
            if (b < 0)
                b = 0;
            if (b > 255)
                b = 255;

            led->setBrightness((uint8_t)b);

            auto s = led->getState();

            char buffer[64];
            snprintf(buffer, sizeof(buffer),
                     "LED_BRIGHTNESS:%d",
                     s.brightness);

            mqtt->publishMessage(buffer);
        }
        return;
    }

    if (strncmp(message, "LED_VELOCITY:", 13) == 0)
    {
        int v;
        if (sscanf(message, "LED_VELOCITY:%d", &v) == 1)
        {
            if (v < 0)
                v = 0;
            if (v > 100)
                v = 100;

            led->setVelocity((uint8_t)v);

            auto s = led->getState();

            char buffer[64];
            snprintf(buffer, sizeof(buffer),
                     "LED_VELOCITY:%d",
                     s.velocity);

            mqtt->publishMessage(buffer);
        }
        return;
    }

    if (strcmp(message, "LED_STATE") == 0)
    {
        auto s = led->getState();

        char buffer[128];
        snprintf(buffer, sizeof(buffer),
                 "LED_STATE:%s,R:%d,G:%d,B:%d,BRT:%d,VEL:%d",
                 (s.brightness == 0 ? "OFF" : "ON"),
                 s.r, s.g, s.b,
                 s.brightness,
                 s.velocity);

        mqtt->publishMessage(buffer);
        return;
    }

    // =================================
    // ESP
    // =================================

    if (strcmp(message, "RESTART_ESP") == 0)
    {
        mqtt->publishMessage("RESTART_ESP");
        esp_restart();
        return;
    }

    // =================================
    // UNKNOWN
    // =================================

    mqtt->publishMessage("UNKNOWN_COMMAND");
}