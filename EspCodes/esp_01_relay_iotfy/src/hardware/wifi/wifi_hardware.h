#ifndef WIFI_HARDWARE_H
#define WIFI_HARDWARE_H

#include <string>
class wifi_hardware
{
    private:
         std::string _ssid;
         std::string _passwd;

    public:
        wifi_hardware(std::string ssid, std::string passwd );

};

#endif