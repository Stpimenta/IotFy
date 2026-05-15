#pragma once

#include "esp_event.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

class WifiManager
{
private:
    const char* ssid;
    const char* password;
    const char* hostname;

    EventGroupHandle_t eventGroup;
    int retryCount;

    static void eventHandler(void* arg,
                             esp_event_base_t event_base,
                             int32_t event_id,
                             void* event_data);

    void connect();

public:
    WifiManager(const char* ssid,
                const char* password,
                const char* hostname);

    void init();
    void start();
};