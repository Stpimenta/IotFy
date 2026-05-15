#include "mqtt_protocols.h"

mqtt_protocols::mqtt_protocols(std::string brokerAdress, std::string espId, void (*callback)(std::string))
    : _brokerAdress(brokerAdress), _messageCallback(callback), _espId(espId) {
    clientMqtt.setClient(espClient);  
}

void mqtt_protocols::setupMqtt() {
    clientMqtt.setServer(_brokerAdress.c_str(), 1883);  //define server
    
    //recive message
    clientMqtt.setCallback([this](char* topic, uint8_t* payload, unsigned int length) {

        //convert payload
        std::string message(reinterpret_cast<char*>(payload), length);

        //call callback;
        _messageCallback(message);

    });
}

// connect broker
void mqtt_protocols::connect() {

    if (clientMqtt.connect(_espId.c_str())) {
        
        std::string subTopic = _espId + "/reciver";  
        clientMqtt.subscribe(subTopic.c_str());
        Serial.println("connected"); 
        Serial.println(_espId.c_str()); 

        
    } 

    else
    {
        Serial.println("connection mqtt fail");  // Substituído std::cout por Serial.println
    }
}

// publisher
void mqtt_protocols::publishMessage(std::string message) {
    if (clientMqtt.connected()) {
         std::string pubTopic = _espId + "/sender";
        clientMqtt.publish(pubTopic.c_str(), message.c_str());
    }
}

// process the message queue
void mqtt_protocols::loop() {
    clientMqtt.loop();  
}
