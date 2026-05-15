#include "MqttClient.h"

#include <stdio.h>
#include <string.h>

#include "esp_log.h"

static const char* TAG = "MQTT";

MqttClient::MqttClient(const char* brokerUri,
                       const char* espId)
{
    this->brokerUri = brokerUri;
    this->espId = espId;

    snprintf(senderTopic,
             sizeof(senderTopic),
             "%s/sender",
             espId);

    snprintf(receiverTopic,
             sizeof(receiverTopic),
             "%s/reciver",
             espId);
}

void MqttClient::init()
{
    esp_mqtt_client_config_t cfg = {};

    cfg.broker.address.uri = brokerUri;

    client = esp_mqtt_client_init(&cfg);

    esp_mqtt_client_register_event(
        client,
        MQTT_EVENT_ANY,
        &MqttClient::eventHandler,
        this
    );
}

void MqttClient::start()
{
    esp_mqtt_client_start(client);
}

void MqttClient::publishMessage(const char* message)
{
    if (!client) return;

    esp_mqtt_client_publish(
        client,
        senderTopic,
        message,
        0,
        1,
        0
    );
}

void MqttClient::publishMessageForOtherEsp(const char* user,
                                           const char* message)
{
    if (!client) return;

    char topic[64];

    snprintf(topic,
             sizeof(topic),
             "%s/reciver",
             user);

    esp_mqtt_client_publish(
        client,
        topic,
        message,
        0,
        1,
        0
    );
}

void MqttClient::setMessageCallback(void (*callback)(const char*))
{
    this->messageCallback = callback;
}

void MqttClient::eventHandler(void* handler_args,
                              esp_event_base_t base,
                              int32_t event_id,
                              void* event_data)
{
    MqttClient* self = static_cast<MqttClient*>(handler_args);

    self->handleEvent((esp_mqtt_event_handle_t) event_data);
}

void MqttClient::handleEvent(esp_mqtt_event_handle_t event)
{
    switch (event->event_id)
    {
        case MQTT_EVENT_CONNECTED:
        {
            ESP_LOGI(TAG, "MQTT conectado");

            esp_mqtt_client_subscribe(
                client,
                receiverTopic,
                1
            );

            break;
        }

        case MQTT_EVENT_DISCONNECTED:
        {
            ESP_LOGW(TAG, "MQTT desconectado");
            break;
        }

        case MQTT_EVENT_DATA:
        {
            static char message[128];

            int len = event->data_len;

            if (len >= sizeof(message))
            {
                len = sizeof(message) - 1;
            }

            memcpy(message, event->data, len);

            message[len] = '\0';

            if (messageCallback)
            {
                messageCallback(message);
            }

            break;
        }

        default:
            break;
    }
}