#include "./wifi_hardware.h"

wifi_hardware::wifi_hardware(std::string ssid, std::string passwd, std::string id) : _ssid(ssid), _passwd(passwd), _id(id)
{
    if (ssid.empty() || passwd.empty()) {
        Serial.println("Error: SSID and password cannot be empty!");
    }
    else
    {
        std::string wifi_message = "connecting -> ssid: " + _ssid + " passwd: " + _passwd;
        Serial.println(wifi_message.c_str());

        WiFi.hostname(_id.c_str());
        WiFi.begin(_ssid.c_str(), _passwd.c_str());

        // while (WiFi.status() != WL_CONNECTED)
        // {
        //     Serial.print(".");
        //     delay(5000);   
        //     yield(); 
        // }

        Serial.println("connected");
    }
}
