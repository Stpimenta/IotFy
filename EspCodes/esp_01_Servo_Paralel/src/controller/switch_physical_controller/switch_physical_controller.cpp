#include "switch_physical_controller.h"

SwitchPhysicalController::SwitchPhysicalController(SwitchPhysical* s1, relay_virtual *relay) {
  switch1 = s1;
  _relay = relay;
}

void SwitchPhysicalController::update() {
    static bool lastSwitch1State = true;

    bool currentSwitch1State = switch1->getState();

    if (currentSwitch1State != lastSwitch1State) {
        
        _relay->paralel();
        // Atualiza o estado anterior somente após a ação
        lastSwitch1State = currentSwitch1State;
    }
}




