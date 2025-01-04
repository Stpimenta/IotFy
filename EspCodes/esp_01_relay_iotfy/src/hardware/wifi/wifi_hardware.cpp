#include "./wifi_hardware.h"
#include "iostream"
#include <ESP8266WiFi.h>


wifi_hardware :: wifi_hardware(std::string ssid, std::string passwd ):_ssid(ssid), _passwd(passwd)
{
    if (ssid.empty() || passwd.empty()) {
        std::cerr << "Error: SSID and password cannot be empty!" << std::endl;
    }

    else
    {
        std::string wifi_message = "connecting -> ssid: " + _ssid + " passwd: " + _passwd;
        std::cout << wifi_message << std::endl;

        WiFi.hostname("ESP-TESTE");
        WiFi.begin(_ssid.c_str(), _passwd.c_str());

        while (WiFi.status () != WL_CONNECTED)
        {
            std::cout << "." << std::endl;  
            delay(5000);   
            yield(); 
        }

        std::cout << "connected" << std::endl;
    }
}