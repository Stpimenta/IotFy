#include <TaskScheduler.h>
#include <Arduino.h>
#include "iostream"
#include "./hardware/wifi/wifi_hardware.h"
#include "secret.h"
#include "./protocols/mqtt_protocols.h"
#include "./controller/mqtt_controller/mqtt_controller.h"
#include "hardware/ir_hardware/ir_hardware.h"
#include <ArduinoOTA.h>

//protocols
mqtt_protocols *mqttClient;  

//hardwares
wifi_hardware *wifi;
IrHardware * irHardware;

//controllers
mqtt_controller *mqttController;


//scheduler
Scheduler scheduler;

//taks
Task mqttTask(500, TASK_FOREVER, []() {
    if(!mqttClient->clientMqtt.connected())
    {
        mqttClient->connect();
    }

    //It is necessary to receive messages.
    mqttClient->loop();
   
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

    //ir gpio 0
    irHardware = new IrHardware(0);


    //setup protocols
    mqttClient = new mqtt_protocols(mqtt_broker, espid, messageCallback);
    mqttClient->setupMqtt();

  
    //setup controllers
    mqttController = new mqtt_controller(mqttClient, irHardware);

    // add tasks
    scheduler.addTask(mqttTask);

  
    //enable tasks
    mqttTask.enable();


    //Ota
    ArduinoOTA.begin();

}

void loop() {
    // run scheduler
    scheduler.execute();
    ArduinoOTA.handle();
}
