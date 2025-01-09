#include <TaskScheduler.h>
#include <Arduino.h>
#include "iostream"
#include "./hardware/wifi/wifi_hardware.h"
#include "secret.h"
#include "./protocols/mqtt_protocols.h"
#include "./controller/mqtt_controller/mqtt_controller.h"
#include "./hardware/relay_serial/relay_serial.h"
#include "./controller/switch_physical_controller/switch_physical_controller.h"
#include "./hardware/switch_physical/switch_physical.h"
#include <ArduinoOTA.h>

//protocols
mqtt_protocols *mqttClient;  

//hardwares
wifi_hardware *wifi;
relay_serial *relay;
SwitchPhysical *s1;


//controllers
mqtt_controller *mqttController;
SwitchPhysicalController *switchPhysicalController;

//scheduler
Scheduler scheduler;

//taks
Task mqttTask(300, TASK_FOREVER, []() {
    if(!mqttClient->clientMqtt.connected())
    {
        mqttClient->connect();
    }

    //It is necessary to receive messages.
    mqttClient->loop();
   
});

Task switchTask(100, TASK_FOREVER, []() {
    switchPhysicalController->update();
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
    s1 = new SwitchPhysical(3);
    relay = new relay_serial();

    //setup protocols
    mqttClient = new mqtt_protocols(mqtt_broker, espid, messageCallback);
    mqttClient->setupMqtt();
  
    //setup controllers
    mqttController = new mqtt_controller(mqttClient,relay);
    switchPhysicalController = new SwitchPhysicalController(s1,relay);

    // add tasks
    scheduler.addTask(mqttTask);
    scheduler.addTask(switchTask);
  
    //enable tasks
    mqttTask.enable();
    switchTask.enable();

    //Ota
    ArduinoOTA.begin();

}

void loop() {
    // run scheduler
    scheduler.execute();
    ArduinoOTA.handle();
}
