#include "MqttController.h"

#include <string.h>
#include "esp_system.h"

MqttController::MqttController(ParallelRelay* light1,
                               BasicRelay* light2,
                               MqttClient* mqtt,
                               StripLed* led)
{
    this->light1 = light1;
    this->light2 = light2;
    this->mqtt = mqtt;
    this->led = led;
}

void MqttController::processMessage(const char* message)
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
            light1->isOn() ? "LIGHT1_ON" : "LIGHT1_OFF"
        );
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
            light2->isOn() ? "LIGHT2_ON" : "LIGHT2_OFF"
        );
        return;
    }

    // =================================
    // LED STRIP (NOVO)
    // =================================

    if (strcmp(message, "LED_ON") == 0)
    {
        led->powerOn();
        mqtt->publishMessage("LED_ON");
        return;
    }

    if (strcmp(message, "LED_OFF") == 0)
    {
        led->powerOff();
        mqtt->publishMessage("LED_OFF");
        return;
    }

    if (strcmp(message, "LED_RAINBOW") == 0)
    {
        led->setEffect(StripLed::RAINBOW);
        mqtt->publishMessage("LED_RAINBOW");
        return;
    }

    if (strcmp(message, "LED_FADE") == 0)
    {
        led->setEffect(StripLed::FADE);
        mqtt->publishMessage("LED_FADE");
        return;
    }

    if (strcmp(message, "LED_STATE") == 0)
    {
        mqtt->publishMessage(
            led->isOn() ? "LED_ON" : "LED_OFF"
        );
        return;
    }

    // LED COLOR (ex: LED_COLOR:255,0,0)
    if (strncmp(message, "LED_COLOR:", 10) == 0)
    {
        int r, g, b;
        sscanf(message, "LED_COLOR:%d,%d,%d", &r, &g, &b);

        led->setColor(r, g, b);

        mqtt->publishMessage("LED_COLOR_OK");
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