import 'package:flutter/material.dart';
import 'package:IotFy/screens/strip_led/model/strip_state_model.dart';
import 'package:IotFy/services/client_mqtt_service.dart';

class StripLedController extends ChangeNotifier {
  final MQTTService mqttService;

  late StripStateModel stripState;

  StripLedController({
    required this.mqttService,
  }) {
    stripState = StripStateModel(
      red: 255,
      green: 255,
      blue: 255,
      brightness: 0,
      velocity: 50,
      isSolid: true,
      isOn: false,
    );
  }

  // =========================================================
  // COMMANDS
  // =========================================================

  void powerOn(String espId) {
    mqttService.publishMessage(
      espId,
      "LED_ON",
    );
  }

  void powerOff(String espId) {
    mqttService.publishMessage(
      espId,
      "LED_OFF",
    );
  }

  void setSolid(String espId) {
    mqttService.publishMessage(
      espId,
      "LED_SOLID",
    );
  }

  void setFade(String espId) {
    mqttService.publishMessage(
      espId,
      "LED_FADE",
    );
  }

  void setRainbow(String espId) {
    mqttService.publishMessage(
      espId,
      "LED_RAINBOW",
    );
  }

  void setColor(
    int red,
    int green,
    int blue,
    String espId,
  ) {
    mqttService.publishMessage(
      espId,
      "LED_COLOR:$red,$green,$blue",
    );
  }

  void setBrightness(
    int brightness,
    String espId,
  ) {
    mqttService.publishMessage(
      espId,
      "LED_BRIGHTNESS:$brightness",
    );
  }

  void setVelocity(
    int velocity,
    String espId,
  ) {
    mqttService.publishMessage(
      espId,
      "LED_VELOCITY:$velocity",
    );
  }

  void getState(String espId) {
    mqttService.publishMessage(
      espId,
      "LED_STATE",
    );
  }

  // =========================================================
  // MQTT CALLBACK
  // =========================================================

  void mqttCallback(String message) {

    // -------------------------
    // LED_ON:255
    // -------------------------
    if (message.startsWith("LED_ON")) {
      stripState.isOn.value = true;

      final parts = message.split(":");

      if (parts.length > 1) {
        stripState.brightness.value =
            int.tryParse(parts[1]) ?? 255;
      }

      notifyListeners();
      return;
    }

    // -------------------------
    // LED_OFF:0
    // -------------------------
    if (message.startsWith("LED_OFF")) {
      stripState.isOn.value = false;
      stripState.brightness.value = 0;

      notifyListeners();
      return;
    }

    // -------------------------
    // LED_SOLID
    // -------------------------
    if (message == "LED_SOLID") {
      stripState.isSolid = true;
      notifyListeners();
      return;
    }

    // -------------------------
    // LED_FADE
    // -------------------------
    if (message == "LED_FADE") {
      stripState.isSolid = false;
      notifyListeners();
      return;
    }

    // -------------------------
    // LED_RAINBOW
    // -------------------------
    if (message == "LED_RAINBOW") {
      stripState.isSolid = false;
      notifyListeners();
      return;
    }

    // -------------------------
    // LED_COLOR:r,g,b
    // -------------------------
    if (message.startsWith("LED_COLOR:")) {

      final raw =
          message.replaceFirst("LED_COLOR:", "");

      final rgb = raw.split(",");

      if (rgb.length == 3) {

        stripState.red.value =
            int.tryParse(rgb[0]) ?? 0;

        stripState.green.value =
            int.tryParse(rgb[1]) ?? 0;

        stripState.blue.value =
            int.tryParse(rgb[2]) ?? 0;

        notifyListeners();
      }

      return;
    }

    // -------------------------
    // LED_BRIGHTNESS:x
    // -------------------------
    if (message.startsWith("LED_BRIGHTNESS:")) {

      final raw =
          message.replaceFirst(
              "LED_BRIGHTNESS:",
              "");

      stripState.brightness.value =
          int.tryParse(raw) ?? 0;

      stripState.isOn.value =
          stripState.brightness.value > 0;

      notifyListeners();
      return;
    }

    // -------------------------
    // LED_VELOCITY:x
    // -------------------------
    if (message.startsWith("LED_VELOCITY:")) {

      final raw =
          message.replaceFirst(
              "LED_VELOCITY:",
              "");

      stripState.velocity.value =
          int.tryParse(raw) ?? 0;

      notifyListeners();
      return;
    }

    // -------------------------
    // FULL STATE
    // LED_STATE:ON,R:255,G:0,B:0,BRT:100,VEL:50
    // -------------------------
    if (message.startsWith("LED_STATE:")) {

      final raw =
          message.replaceFirst("LED_STATE:", "");

      final parts = raw.split(",");

      for (final part in parts) {

        if (part == "ON") {
          stripState.isOn.value = true;
        }

        if (part == "OFF") {
          stripState.isOn.value = false;
        }

        if (part.startsWith("R:")) {
          stripState.red.value =
              int.tryParse(
                part.replaceFirst("R:", ""),
              ) ??
              0;
        }

        if (part.startsWith("G:")) {
          stripState.green.value =
              int.tryParse(
                part.replaceFirst("G:", ""),
              ) ??
              0;
        }

        if (part.startsWith("B:")) {
          stripState.blue.value =
              int.tryParse(
                part.replaceFirst("B:", ""),
              ) ??
              0;
        }

        if (part.startsWith("BRT:")) {
          stripState.brightness.value =
              int.tryParse(
                part.replaceFirst("BRT:", ""),
              ) ??
              0;
        }

        if (part.startsWith("VEL:")) {
          stripState.velocity.value =
              int.tryParse(
                part.replaceFirst("VEL:", ""),
              ) ??
              0;
        }
      }

      notifyListeners();
    }
  }

  // =========================================================
  // MQTT REGISTER
  // =========================================================

  void registerCallback(String espId) {
    mqttService.subscribeToTopic(
      espId,
      mqttCallback,
    );
  }
}