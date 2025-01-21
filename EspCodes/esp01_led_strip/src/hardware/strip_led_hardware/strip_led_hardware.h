#ifndef STRIP_LED_HARDWARE_H
#define STRIP_LED_HARDWARE_H

#include <Adafruit_NeoPixel.h>
#include <hardware/enum/effects_enum.h>
#include <string>
#define DATA_PIN    0               
#define NUM_LEDS    100         
#define BRIGHTNESS  180             
#define COLOR_ORDER NEO_GRB        


class strip_led_hardware {
private:
    Adafruit_NeoPixel strip;           
    uint8_t brightness;               
    uint8_t red, green, blue = 0;
    effects currentEffect;
    bool isOn = false;
    uint8_t velocity = 200;  
    std::string effectToString(effects effect); 

public:
    strip_led_hardware();         
    void begin();                      
    void setColor(uint8_t red, uint8_t green, uint8_t blue);  
    void setBrightness(uint8_t brightnessValue);  
    void off();
    void turnOn(); 
    std::string getState();  
    
    void setEffect(effects effect);
    void setVelocity(uint8_t newVelocity);                   
    void loop();   


    void rainbow();                              
    void fade();  
    void solidColor();
          
    void theaterChase();     
    void comet();        
             
};

#endif
