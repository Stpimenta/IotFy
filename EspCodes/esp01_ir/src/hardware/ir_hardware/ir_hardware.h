#ifndef IR_HARDWARE
#define IR_HARDWARE

#include <IRsend.h> // Inclua a biblioteca necessária para IRsend
#include <string>
#include <Arduino.h>

class IrHardware {

    private:

        int _pin;        
        IRsend irsend;  

    public:
 
        IrHardware(int pin);
        void sendIr(const std::string& code); 
           
};

#endif


// #ifndef WIFI_HARDWARE_H
// #define WIFI_HARDWARE_H

// #include <string>
// #include <ESP8266WiFi.h>

// class wifi_hardware
// {
//     private:
//          std::string _ssid;
//          std::string _passwd;
//          std::string _id;
//     public:
//         wifi_hardware(std::string ssid, std::string passwd, std::string id);

// };

// #endif