#include <TaskScheduler.h>
#include <Arduino.h>
#include "iostream"
#include "./hardware/wifi/wifi_hardware.h"
#include "./hardware/strip_led_hardware/strip_led_hardware.h"
#include "secret.h"
#include "./protocols/mqtt_protocols.h"
#include "./controller/mqtt_controller/mqtt_controller.h"
#include <ArduinoOTA.h>

//protocols
mqtt_protocols *mqttClient;  

//hardwares
wifi_hardware *wifi;
strip_led_hardware *stripLed;

//controllers
mqtt_controller *mqttController;

//scheduler
Scheduler scheduler;

//tasks
Task mqttTask(300, TASK_FOREVER, []() {
    if (!mqttClient->clientMqtt.connected()) {
        mqttClient->connect();
    }

    // It is necessary to receive messages.
    mqttClient->loop();
});

Task stripLedTask(30, TASK_FOREVER, []() {
    yield();
    stripLed->loop();
});

//functions
void messageCallback(std::string message) {
    mqttController->processMessage(message); 
}

//setup
void setup() {
    Serial.begin(9600);

    //setup hardware 
    wifi = new wifi_hardware(ssid, password, espid);
    stripLed = new strip_led_hardware();
    stripLed->begin();

    //setup protocols
    mqttClient = new mqtt_protocols(mqtt_broker, espid, messageCallback);
    mqttClient->setupMqtt();
  
    //setup controllers
    mqttController = new mqtt_controller(mqttClient, stripLed);

    //add tasks
    scheduler.addTask(mqttTask);
    scheduler.addTask(stripLedTask);
  
    //enable tasks
    mqttTask.enable();
    stripLedTask.enable();

    //Ota
    ArduinoOTA.begin();
}

void loop() {
    // Run scheduler
    scheduler.execute();
    ArduinoOTA.handle();
}
