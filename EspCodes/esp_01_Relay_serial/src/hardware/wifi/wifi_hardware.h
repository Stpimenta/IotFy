#ifndef WIFI_HARDWARE_H
#define WIFI_HARDWARE_H

#include <string>
#include <ESP8266WiFi.h>

class wifi_hardware
{
    private:
         std::string _ssid;
         std::string _passwd;
         std::string _id;
    public:
        wifi_hardware(std::string ssid, std::string passwd, std::string id);

};

#endif