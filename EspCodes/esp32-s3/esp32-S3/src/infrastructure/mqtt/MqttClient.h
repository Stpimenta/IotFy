#pragma once

#include "mqtt_client.h"

class MqttClient
{
public:
    MqttClient(const char* brokerUri,
               const char* espId);

    void init();
    void start();

    void publishMessage(const char* message);

    void publishMessageForOtherEsp(const char* user,
                                   const char* message);

    void setMessageCallback(void (*callback)(const char* message));

private:
    static void eventHandler(void* handler_args,
                             esp_event_base_t base,
                             int32_t event_id,
                             void* event_data);

    void handleEvent(esp_mqtt_event_handle_t event);

private:
    const char* brokerUri;
    const char* espId;

    char senderTopic[64];
    char receiverTopic[64];

    esp_mqtt_client_handle_t client = nullptr;

    void (*messageCallback)(const char* message) = nullptr;
};