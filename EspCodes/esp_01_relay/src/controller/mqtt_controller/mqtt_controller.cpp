#include "mqtt_controller.h"

mqtt_controller::mqtt_controller(mqtt_protocols* mqttBroker, Relay_esp *relay)
{
    _mqttBroker = mqttBroker;

    _relay = relay;
}

std::string toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

enum_functions mqtt_controller::getMessageFunction(const std::string& message) {
    std::string lowerMessage = toLowerCase(message);

    if (lowerMessage == "turn_on_relay") return TURN_ON_RELAY;
    if (lowerMessage == "turn_off_relay") return TURN_OFF_RELAY;
    if (lowerMessage.find("pulse") != std::string::npos) return PULSE;
    if (lowerMessage == "state") return STATE;
    if (lowerMessage == "restart_esp") return RESTART_ESP;
    // if (lowerMessage.find("update") != std::string::npos) return UPDATE;
    return NONE;
}

void mqtt_controller::processMessage(const std::string& message)
{
    enum_functions command = getMessageFunction(message);
   
    switch (command)
    {
        case TURN_ON_RELAY:
            _relay->turnOn();
            _mqttBroker->publishMessage("TURN_ON_RELAY");
            break;

        case TURN_OFF_RELAY:
            _relay->turnOff();
            _mqttBroker->publishMessage("TURN_OFF_RELAY");
            break;

        case PULSE:
            {
                std::string pulseDuration;
                int duration;
                size_t delimiterPosition = message.find("/");

                if(delimiterPosition ==  std::string::npos)
                {   
                    _mqttBroker->publishMessage("INVALID ARGS - FORMAT PULSE/MS");
                    break;
                }
                
                pulseDuration = message.substr(delimiterPosition + 1);
    

                try {
                    duration = std::stoi(pulseDuration);  
                } catch (const std::invalid_argument& e) {
                    _mqttBroker->publishMessage("INVALID ARGS - IT IS NAN");
                    break;
                } catch (const std::out_of_range& e) {
                    _mqttBroker->publishMessage("INVALID ARGS - OUT OF RANGE");
                    break;
                } catch (...) {
                    _mqttBroker->publishMessage("UNKNOWN ERROR");
                    break;
                }

                std::string responseMessage = pulseDuration + " MS PULSE";
                _mqttBroker->publishMessage(responseMessage);
                _relay->pulse(duration);
            }
            break;

        // case UPDATE:
        //     {
        //         std::string url;
        //         size_t delimiterPosition = message.find("/");

        //         if(delimiterPosition ==  std::string::npos)
        //         {   
        //             _mqttBroker->publishMessage("INVALID ARGS - FORMAT PULSE/MS");
        //             break;
        //         }
                
        //         url = message.substr(delimiterPosition + 1);

        //         _mqttBroker->publishMessage("start upload");
        //         Serial.printf("start upload\n");
        //         _ota->updateHTTP(url.c_str());
        //     }
        //     break;

        case STATE:
            if(_relay->state == true)
            {
                Serial.println("true");
                _mqttBroker->publishMessage("true");
            }

            if(_relay->state == false)
            {
                Serial.println("false");
                _mqttBroker->publishMessage("false");
            }
            break;
        
        case RESTART_ESP:
            Serial.println("Restarting");
            ESP.restart();
            break;

        default:
            Serial.println("Unrecognized command.");
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
