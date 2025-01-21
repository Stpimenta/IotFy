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

### **Unrecognized Command**:
If an unrecognized command is received, ESP will send a list of available commands to the `espid/sender` topic.

---

## **Relay Control**

You can control a relay connected to an ESP through MQTT messages.

### **Commands to Send**:
- **TURN_ON_RELAY**: Relay turns on, and ESP sends `"TURN_ON_RELAY"` back.
- **TURN_OFF_RELAY**: Relay turns off, and ESP sends `"TURN_OFF_RELAY"` back.
- **PULSE/{MS}**: Relay Pulse for x milissecond, and ESP sends `"{x} MS PULSE"` back.
- **RESTART_ESP**: ESP restarts, no message sent.
- **STATE**: ESP sends `"true"` if relay is on or `"false"` if relay is off.



## **Relay Control Servo and Serial with Parallel Switch**

A system that controls a relay and adds a simulated parallel switch using two ESP-01. One ESP controls the relay, and the other acts as a parallel switch with servo code.

### **How to Use**:
- **Main ESP (Relay Serial)**: Controls the relay and responds to commands **TURN_ON_RELAY**, **TURN_OFF_RELAY**, and **REVERSE_STATE**.
- **Secondary ESP (Servo)**: Functions as a parallel switch, reversing the relay state on the Main ESP.

### **Reason for Using GPIO 3 (RX)**:
The ESP-01 device has only one available GPIO, and when restarted, it does not block initialization when closed, which is GPIO 3 (RX).



# **IR Sender**

You can send IR codes using MQTT messages.

## **Commands to Send**:

- **SEND_IR/{CODE}**: Sends an IR code in hexadecimal format. The ESP responds with:  
  `"send ir code: {CODE}"`.

# **LED STRIP CONTROL**

You can control an LED strip connected to an ESP through MQTT messages.

## **COMMANDS TO SEND:**

- **ON**: Turns the LED strip on, and ESP sends `"ON"` back.
- **OFF**: Turns the LED strip off, and ESP sends `"OFF"` back.
- **SET_COLOR/{R}/{G}/{B}**: Set the LED strip color using RGB values. ESP sends `"Color set to R:{R} G:{G} B:{B}"` back.
- **SET_BRIGHTNESS/{VALUE}**: Set the LED strip brightness. ESP sends `"Brightness set to {VALUE}"` back, where the value is between 0 and 255.
- **RAINBOW**: Activates the rainbow effect on the LED strip, and ESP sends `"current effect: RAINBOW"` back.
- **FADE**: Activates the fade effect on the LED strip, and ESP sends `"current effect: FADE"` back.
- **SOLID_COLOR**: Activates the solid color effect on the LED strip, and ESP sends `"current effect: SOLID_COLOR"` back.
- **STATE**: ESP sends the current state of the LED strip, including ON/OFF status, color, brightness, and velocity.
- **WAVES**: Activates the waves effect on the LED strip, and ESP sends `"current effect: WAVES"` back.
- **THEATERCHASE**: Activates the theater chase effect on the LED strip, and ESP sends `"current effect: THEATERCHASE"` back.
- **COMET**: Activates the comet effect on the LED strip, and ESP sends `"current effect: COMET"` back.

## **STATE DESCRIPTION:**

The LED strip can be ON or OFF, and its color and brightness are adjustable.

- **Color**: The available colors are defined by the RGB values, where each value is between 0 and 255.
- **Brightness**: Adjustable between 0 (off) and 255 (maximum brightness).
- **Velocity**: Controls the speed of effects like rainbow and fade. Velocity ranges from 0 to 255, where higher values represent faster transitions.


