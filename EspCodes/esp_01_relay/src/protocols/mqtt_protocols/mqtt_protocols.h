#ifndef MQTT_PROTOCOLS_H
#define MQTT_PROTOCOLS_H
#include <string>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>



class mqtt_protocols

{
private:
    std::string _brokerAdress;
    std::string _espId;
    WiFiClient espClient;
    void (*_messageCallback)(std::string);
    

public:
    mqtt_protocols(std::string brokerAdress,std::string espId, void (*callback)(std::string));
    void setupMqtt ();
    void connect();
    void publishMessage(std::string);
    void loop();
    PubSubClient clientMqtt;
};

#endif 
