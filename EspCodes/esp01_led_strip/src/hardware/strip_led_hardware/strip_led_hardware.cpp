#include "strip_led_hardware.h"

strip_led_hardware::strip_led_hardware()
  : strip(NUM_LEDS, DATA_PIN, NEO_BRG + NEO_KHZ800) {  
  brightness = BRIGHTNESS;  
}

void strip_led_hardware::begin() {
  strip.begin();  
  strip.setBrightness(brightness); 
  strip.show(); 
  off();
}


void strip_led_hardware::setColor(uint8_t redValue, uint8_t greenValue, uint8_t blueValue) {
  red = redValue;
  green = greenValue;
  blue = blueValue;
}

void strip_led_hardware::setBrightness(uint8_t brightnessValue) {
  brightness = brightnessValue;  
  strip.setBrightness(brightness);  
  strip.show(); 
}

void strip_led_hardware::off() {

  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));  
  }
  strip.show(); 
  isOn = false;
}




void strip_led_hardware::loop() {
  if (!isOn) {
    strip.clear();  
    strip.show();
    return;
  }

  switch (currentEffect) {

    case SOLID_COLOR:
      for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, strip.Color(red, green, blue));
      }
      strip.show();
      break;

    case RAINBOW:
      rainbow();  
      break;

    case FADE:
      fade();  
      break;

    case THEATERCHASE:
      theaterChase();  
      break;

    case COMET:
      comet();  
      break;

    default:
      break;
  }
}



void strip_led_hardware::solidColor() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));  
  }
  strip.show();
}


void strip_led_hardware::rainbow() {
    static uint8_t hue = 0;  // Initial hue value
    uint8_t speed = 255 - velocity; // Speed controls the rate of color transitions

    // Loop through all LEDs and apply the rainbow effect with smooth transitions
    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t currentHue = (hue + (i * 256 / NUM_LEDS)) % 256;  // Smooth color transition
        strip.setPixelColor(i, strip.ColorHSV(currentHue * 256, 255, 255));  
    }

    // Update the LED strip
    strip.show();

    // Increment hue value and reset to 0 if it exceeds 255
    hue++;
    if (hue >= 255) {
        hue = 0;
    }

    // Delay based on speed (smaller velocity, faster transition)
    delay(speed);
}




void strip_led_hardware::fade() {
  static uint8_t fadeValue = 0;
  static int fadeDirection = 1;  

  fadeValue += fadeDirection;
  if (fadeValue == 0 || fadeValue == 255) {
    fadeDirection = -fadeDirection; 
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(
        (red * fadeValue) / 255,
        (green * fadeValue) / 255,
        (blue * fadeValue) / 255
    ));
  }
  strip.show();
  
  delay(255 - velocity);  
}


#include "strip_led_hardware.h"








void strip_led_hardware::theaterChase() {
    int chaseLength = 6;  // Length of the moving chase (can be adjusted)
    int speed = 100;      // Speed of the chase (lower value means faster)
    
    for (int i = 0; i < NUM_LEDS; i++) {
        // Turn off all LEDs
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }

    // Create the theater chase effect
    for (int j = 0; j < chaseLength; j++) {
        for (int i = 0; i < NUM_LEDS; i++) {
            // Light up LEDs in the pattern
            if ((i + j) % chaseLength == 0) {
                strip.setPixelColor(i, strip.Color(red, green, blue));  // Color of the chase
            }
        }
        strip.show();
        delay(255 - velocity); 
    }
}



void strip_led_hardware::comet() {
    static int cometPosition = 0;
    static int cometTailLength = 5;  // Length of the comet tail

    // Create comet tail
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i >= cometPosition && i < cometPosition + cometTailLength) {
            strip.setPixelColor(i, strip.Color(red, green, blue));  // Comet color
        } else {
            strip.setPixelColor(i, strip.Color(0, 0, 0));  // Off
        }
    }

    strip.show();

    cometPosition++;
    if (cometPosition >= NUM_LEDS) {
        cometPosition = 0;  // Reset comet position
    }

    delay(255 - velocity);  
}


void strip_led_hardware::turnOn() {

  isOn = true; 
  if(red == 0 && blue == 0 && green == 0)
  {
      setColor(0, 0, 255);    
      setEffect(SOLID_COLOR); 
  }           
     
}


std::string strip_led_hardware::getState() {
    std::string state = "State: " + std::string(isOn ? "ON" : "OFF")
                        + ", Color: R:" + std::to_string(static_cast<int>(red))
                        + " G:" + std::to_string(static_cast<int>(green))
                        + " B:" + std::to_string(static_cast<int>(blue))
                        + ", Brightness: " + std::to_string(static_cast<int>(brightness))
                        + ", Velocity: " + std::to_string(static_cast<int>(velocity))
                        + ", Effect: " + effectToString(currentEffect);  // Chama a função para converter enum em string

    return state;
}

void strip_led_hardware::setVelocity(uint8_t newVelocity) {
    // Ensure velocity is within the valid range (0 to 255)
    if (newVelocity >= 0 && newVelocity <= 255) {
        velocity = newVelocity;
    } 
}



void strip_led_hardware::setEffect(effects effect) {
  currentEffect = effect;  
}



std::string strip_led_hardware::effectToString(effects effect) {
    switch (effect) {
        case RAINBOW: return "RAINBOW";
        case FADE: return "FADE";
        case SOLID_COLOR: return "SOLID_COLOR";
        case THEATERCHASE: return "THEATERCHASE";
        case COMET: return "COMET";
        default: return "NONE";
    }
}



