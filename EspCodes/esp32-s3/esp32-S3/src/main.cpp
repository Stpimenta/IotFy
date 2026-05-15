#include "hardware/BasicRelay.h"
#include "hardware/ParallelRelay.h"
#include "hardware/StripLed.h"
#include "infrastructure/wifi/WifiManager.h"
#include "infrastructure/mqtt/MqttClient.h"
#include "controller/MqttController.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "secrets.h"
#include "nvs_flash.h"
#include <string>

//Two relays in the same switch allow you to turn it on and off, but still offer individual control on software.

BasicRelay rele2(GPIO_NUM_4);
ParallelRelay luz(GPIO_NUM_3, &rele2, GPIO_NUM_20, GPIO_NUM_21);
StripLed led(GPIO_NUM_6, 100);

WifiManager wifi(WIFI_SSID, WIFI_PASS, ESPID);

MqttClient mqtt(
    MQTT_BROKER,
    ESPID
);

MqttController controller(
    &luz,
    &rele2,
    &mqtt,
    &led
);

void onMessage(const char* message)
{
    printf("Recebido: %s\n", message);

    controller.processMessage(message);
}

void onLightState(bool state)
{
    if(state)
    {
        mqtt.publishMessage("LIGHT1_ON");
        mqtt.publishMessage("LIGHT2_ON");
    }else{
        mqtt.publishMessage("LIGHT1_OFF");
        mqtt.publishMessage("LIGHT2_OFF");
    }
}

extern "C" void app_main(void)
{
    

    nvs_flash_init();
    wifi.init();
    wifi.start();

    mqtt.setMessageCallback(onMessage);
    
    //callback for switch changes
    luz.setStateCallback(onLightState);

    mqtt.init();
    mqtt.start();
    
    luz.init();

    while (1)
    {
        // rele1.powerOn();
        // vTaskDelay(pdMS_TO_TICKS(1000));

        // rele1.powerOff();
        // vTaskDelay(pdMS_TO_TICKS(500));

        // rele2.powerOn();
        // vTaskDelay(pdMS_TO_TICKS(1000));

        // rele2.powerOff();
        luz.loop();
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}