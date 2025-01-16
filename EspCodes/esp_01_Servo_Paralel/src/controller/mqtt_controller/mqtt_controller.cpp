#include "mqtt_controller.h"
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

mqtt_controller::mqtt_controller(mqtt_protocols* mqttBroker)
{
    _mqttBroker = mqttBroker;
}


std::string toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}


enum_functions mqtt_controller::getMessageFunction(const std::string& message) {
    std::string lowerMessage = toLowerCase(message);

    if (lowerMessage == "restart_esp") return RESTART_ESP;
    if (lowerMessage == "is_alive") return IS_AlIVE;
    return NONE;
}

//run actions and call hardware
void mqtt_controller::processMessage(const std::string& message)
{
    enum_functions command = getMessageFunction(message);
   
    switch (command)
    {
        
        case RESTART_ESP:
            std::cout << "Reiniciando" << std::endl;
            ESP.restart();
            break;

        case IS_AlIVE:
            _mqttBroker->publishMessage("yes");
            break;

        default:
            std::cout << "Comando não reconhecido." << std::endl;
            std::string availableCommands = 
                "Unrecognized command. Available commands:\n"
                "TURN_ON_RELAY - Turn on the relay\n"
                "TURN_OFF_RELAY - Turn off the relay\n"
                "STATE - RETURNS RELAY STATE\n"
                "RESTART_ESP - Restart the ESP\n"
                "PRINT_MESSAGE - Display message via MQTT";
            _mqttBroker->publishMessage(availableCommands);
            break;
    }
}


