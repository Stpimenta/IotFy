#include "mqtt_protocols.h"


mqtt_protocols::mqtt_protocols(std::string brokerAdress,std::string espId,void (*callback)(std::string))
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
    } 

    else
    {
        std::cout << "connection mqtt fail" << std::endl;  
    }
        
    
}

// publisher
void mqtt_protocols::publishMessage(std::string message) {
    if (clientMqtt.connected()) {
         std::string pubTopic = _espId + "/sender";
        clientMqtt.publish(pubTopic.c_str(), message.c_str());
    }
}

//reconnect
// void mqtt_protocols::reconnect() {
    
//     while (!clientMqtt.connected()) {
//         std::cout << ("Attempting MQTT connection...") << std::endl;

//         // Tenta se conectar ao broker MQTT
//         if (clientMqtt.connect(_espId.c_str())) {
//             clientMqtt.subscribe(_brokerTopic.c_str());
//         } else {
//             std::cout << ("fail") << std::endl;
//             std::cout << clientMqtt.state() << std::endl;
//             std::cout << ("Try again in 5 seconds") << std::endl;
//             delay(5000);
//             yield();  
//         }
//     }
// }

// process the message queue
void mqtt_protocols::loop() {
    clientMqtt.loop();  
}
