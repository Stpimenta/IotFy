# Introdução
Agora um pouco mais maduro como desenvolvedor estou reconstruindo o meu projeto anterior HomeYX, agora rebatizado de "iotFy".
O projeto tem como objetivo dar continuidade aos meus estudos sobre programção e aproveitar para deixar minha casa mais moderna e integrada gastando pouco.


# Setup
- broker MQTT
- ESPs
- devices with relays led strip...


# MQTT Communication with ESPs

This project enables communication between ESP devices and Destop/Mobile. Each ESP has a unique ID (`espid`) and communicates via specific topics.

## **MQTT Topics**

- **Receiver Topic**: `espid/receiver` (ESP listens for messages here)
- **Sender Topic**: `espid/sender` (ESP sends responses here)

---

## **Relay Control**

You can control a relay connected to an ESP through MQTT messages.

### **Commands to Send**:
- **TURN_ON_RELAY**: Relay turns on, and ESP sends `"TURN_ON_RELAY"` back.
- **TURN_OFF_RELAY**: Relay turns off, and ESP sends `"TURN_OFF_RELAY"` back.
- **PULSE/{MS}**: Relay Pulse for x milissecond, and ESP sends `"{x} MS PULSE"` back.
- **RESTART_ESP**: ESP restarts, no message sent.
- **STATE**: ESP sends `"true"` if relay is on or `"false"` if relay is off.

### **Unrecognized Command**:
If an unrecognized command is received, ESP will send a list of available commands to the `espid/sender` topic.





