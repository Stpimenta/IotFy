#include "ir_hardware.h"


IrHardware::IrHardware(int pin) : _pin(pin), irsend(pin) {
    pinMode(pin, OUTPUT);
}

void IrHardware::sendIr(const std::string& code) {

    unsigned long data = strtoul(code.c_str(), NULL, 16); 
    irsend.sendNEC(data, 32);

}