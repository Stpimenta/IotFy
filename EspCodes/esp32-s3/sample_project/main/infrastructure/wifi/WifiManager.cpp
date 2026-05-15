#include "WifiManager.h"

#include <string.h>

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"

WifiManager::WifiManager(const char* ssid,
                         const char* password,
                         const char* hostname)
{
    this->ssid = ssid;
    this->password = password;
    this->hostname = hostname;
}

void WifiManager::init()
{
    esp_netif_init();

    esp_event_loop_create_default();

    esp_netif_t* netif = esp_netif_create_default_wifi_sta();

    if (hostname)
    {
        esp_netif_set_hostname(netif, hostname);
    }

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&cfg);

    esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &WifiManager::eventHandler,
        this,
        nullptr
    );

    esp_event_handler_instance_register(
        IP_EVENT,
        IP_EVENT_STA_GOT_IP,
        &WifiManager::eventHandler,
        this,
        nullptr
    );

    wifi_config_t wifi_config = {};

    strncpy(
        (char*)wifi_config.sta.ssid,
        ssid,
        sizeof(wifi_config.sta.ssid)
    );

    strncpy(
        (char*)wifi_config.sta.password,
        password,
        sizeof(wifi_config.sta.password)
    );

    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    esp_wifi_set_mode(WIFI_MODE_STA);

    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
}

void WifiManager::start()
{
    esp_wifi_start();
}

void WifiManager::eventHandler(void* arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data)
{
    if (event_base == WIFI_EVENT)
    {
        if (event_id == WIFI_EVENT_STA_START ||
            event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            esp_wifi_connect();
        }
    }
}