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


## **Relay Control Servo and Serial with Parallel Switch**

A system that controls a relay and adds a simulated parallel switch using two ESP-01. One ESP controls the relay, and the other acts as a parallel switch with servo code.

### **How to Use**:
- **Main ESP (Relay Serial)**: Controls the relay and responds to commands **TURN_ON_RELAY**, **TURN_OFF_RELAY**, and **REVERSE_STATE**.
- **Secondary ESP (Servo)**: Functions as a parallel switch, reversing the relay state on the Main ESP.

### **Reason for Using GPIO 3 (RX)**:
The ESP-01 device has only one available GPIO, and when restarted, it does not block initialization when closed, which is GPIO 3 (RX).






