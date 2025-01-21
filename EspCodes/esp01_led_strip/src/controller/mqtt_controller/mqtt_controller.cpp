#include "mqtt_controller.h"
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

mqtt_controller::mqtt_controller(mqtt_protocols* mqttBroker, strip_led_hardware* stripLED)
{
    _mqttBroker = mqttBroker;
    _stripLed = stripLED;
}


std::string toLowerCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}


enum_functions mqtt_controller::getMessageFunction(const std::string& message) {
    std::string lowerMessage = toLowerCase(message);

    if (lowerMessage == "restart_esp") return RESTART_ESP;
    if (lowerMessage == "is_alive") return IS_ALIVE;
    if (lowerMessage == "off") return F_OFF;
    if (lowerMessage.find("set_color") != std::string::npos) return F_SET_COLOR;
    if (lowerMessage.find("set_brightness") != std::string::npos) return F_SET_BRIGHTNESS;
    if (lowerMessage == "on") return F_ON;  
    if (lowerMessage == "rainbow") return F_RAINBOW; 
    if (lowerMessage == "fade") return F_FADE;  
    if (lowerMessage == "solid_color") return F_SOLID_COLOR;  
    if (lowerMessage == "state") return STATE;
    if (lowerMessage.find("velocity") != std::string::npos) return VELOCITY; 
    // if (lowerMessage == "waves") return F_WAVES;  
    if (lowerMessage == "theater_chase") return F_THEATERCHASE;  
    if (lowerMessage == "comet") return F_COMET;  
    if (lowerMessage == "?") return F_NONE;

    return F_NONE;
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

        case IS_ALIVE:
            _mqttBroker->publishMessage("yes");
            break;

        case F_OFF:
            _stripLed->off();
            _mqttBroker->publishMessage("OFF");
            break;

        case F_ON:
             _stripLed->turnOn();
             _mqttBroker->publishMessage("ON");
             break;

        case VELOCITY:
        {
            std::string velocityValueStr;
            int velocityValue;
            size_t delimiterPosition = message.find("/");

            if (delimiterPosition == std::string::npos)
            {
                _mqttBroker->publishMessage("INVALID ARGS - FORMAT SET_VELOCITY/VALUE");
                break;
            }

            velocityValueStr = message.substr(delimiterPosition + 1);

            try {
                velocityValue = std::stoi(velocityValueStr);
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

            if (velocityValue < 0 || velocityValue > 255) {
                _mqttBroker->publishMessage("INVALID VELOCITY VALUE - SHOULD BE BETWEEN 0 AND 255");
                break;
            }

            _stripLed->setVelocity(static_cast<uint8_t>(velocityValue));
            std::string responseMessage = "Velocity set to " + std::to_string(velocityValue);
            _mqttBroker->publishMessage(responseMessage);
        }
        break;

        
        case F_SET_COLOR:
        {
            std::string colorValuesStr;
            int redValue, greenValue, blueValue;
            size_t delimiterPosition = message.find("/");

            if (delimiterPosition == std::string::npos)
            {
                _mqttBroker->publishMessage("INVALID ARGS - FORMAT SET_COLOR/RED/GREEN/BLUE");
                break;
            }

            colorValuesStr = message.substr(delimiterPosition + 1);
            std::stringstream colorStream(colorValuesStr);

            // Extract  "/"
            if (!(colorStream >> redValue) || !(colorStream.ignore(1, '/') >> greenValue) || !(colorStream.ignore(1, '/') >> blueValue)) {
                _mqttBroker->publishMessage("INVALID ARGS - FORMAT SHOULD BE SET_COLOR/RED/GREEN/BLUE");
                break;
            }

            if (redValue < 0 || redValue > 255 || greenValue < 0 || greenValue > 255 || blueValue < 0 || blueValue > 255) {
                _mqttBroker->publishMessage("INVALID COLOR VALUES - SHOULD BE BETWEEN 0 AND 255");
                break;
            }

            _stripLed->setColor(redValue, greenValue, blueValue); 
            std::string responseMessage = "Color set to R:" + std::to_string(redValue) + " G:" + std::to_string(greenValue) + " B:" + std::to_string(blueValue);
            _mqttBroker->publishMessage(responseMessage);
        }
        break;

        case F_SET_BRIGHTNESS:
        {
            std::string brightnessValueStr;
            int brightnessValue;
            size_t delimiterPosition = message.find("/");

            if (delimiterPosition == std::string::npos)
            {
                _mqttBroker->publishMessage("INVALID ARGS - FORMAT SET_BRIGHTNESS/VALUE");
                break;
            }

            brightnessValueStr = message.substr(delimiterPosition + 1);

            try {
                brightnessValue = std::stoi(brightnessValueStr);
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

            if (brightnessValue < 0 || brightnessValue > 255) {
                _mqttBroker->publishMessage("INVALID BRIGHTNESS VALUE - SHOULD BE BETWEEN 0 AND 255");
                break;
            }

            _stripLed->setBrightness(brightnessValue);  
            std::string responseMessage = "Brightness set to " + std::to_string(brightnessValue);
            _mqttBroker->publishMessage(responseMessage);
        }
        break;

        case F_RAINBOW:
            _stripLed->setEffect(RAINBOW);
            _mqttBroker->publishMessage("current effect: RAINBOW");
            break;

        case F_FADE:
            _stripLed->setEffect(FADE);
            _mqttBroker->publishMessage("current effect: FADE");
            break;

        case F_SOLID_COLOR:
            _stripLed->setEffect(SOLID_COLOR);
            _mqttBroker->publishMessage("current effect: SOLID_COLOR");
            break;

        case F_THEATERCHASE:
            _stripLed->setEffect(THEATERCHASE);
            _mqttBroker->publishMessage("current effect: THEATERCHASE");
            break;

        case F_COMET:
            _stripLed->setEffect(COMET);
            _mqttBroker->publishMessage("current effect: COMET");
            break;
        
            
        case STATE:
            _mqttBroker->publishMessage(_stripLed->getState());  // Chama o método para publicar o estado
        break;

        default:
       
                std::string availableCommands = 
                    "Unrecognized command. Available commands:\n"
                    "IS_ALIVE - ESP sends 'yes'\n"
                    "RESTART_ESP - Restart the ESP\n"
                    "OFF - Turn off the LED strip\n"
                    "RAIWBOW - Activate Rainbow effect\n"
                    "VELOCITY - change effects color\n"
                    "COMET - Activate comet effect\n";
                   
                
                 std::string availableCommands2 = 
                    "FILLSOLID - Activate solid color effect\n"
                    "PERCORRE - Activate comet effect\n"
                    "SET_COLOR - Set LED strip color\n"
                    "SET_BRIGHTNESS - Set LED strip brightness\n"
                    "WAVES - Activate waves effect\n"
                    "THEATERCHASE - Activate theater chase effect\n"
                    "STATE - Get current state of the LED strip (ON/OFF, Color, Brightness)";
                

                _mqttBroker->publishMessage(availableCommands);
                _mqttBroker->publishMessage(availableCommands2);
            break;
    }


}


