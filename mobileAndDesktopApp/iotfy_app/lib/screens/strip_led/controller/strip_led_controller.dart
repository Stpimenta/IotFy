import 'package:flutter/material.dart';
import 'package:IotFy/screens/strip_led/model/strip_state_model.dart';
import 'package:IotFy/services/client_mqtt_service.dart';

class StripLedController extends ChangeNotifier {
  final MQTTService mqttService;
  late StripStateModel stripState;

  StripLedController({required this.mqttService}) {
    stripState = StripStateModel(
      red: 0,
      green: 0,
      blue: 0,
      brightness: 0,
      velocity: 0,
      isSolid: false,
      isOn: false,
    );
  }

  void setColor(int red, int green, int blue, String espId) {
    mqttService.publishMessage(espId, "set_color/$red/$green/$blue");
    stripState.red.value = red;
    stripState.green.value = green;
    stripState.blue.value = blue;
    notifyListeners(); // Notifica mudanças nas cores
  }

  void setBrightness(int brightness, String espId) {
    mqttService.publishMessage(espId, "set_brightness/$brightness");
    stripState.brightness.value = brightness;
    notifyListeners(); // Notifica mudanças no brilho
  }

  void setVelocity(int velocity, String espId) {
    mqttService.publishMessage(espId, "set_velocity/$velocity");
    stripState.velocity.value = velocity;
    notifyListeners(); // Notifica mudanças na velocidade
  }

  void setEffect(String effect, String espId) {
    mqttService.publishMessage(espId, effect);
    stripState.isSolid = effect.contains("SOLID");
    notifyListeners(); // Notifica mudanças no efeito
  }

  void powerOn(String espId) {
    mqttService.publishMessage(espId, "ON");
    stripState.isOn.value = true;
    notifyListeners(); // Notifica quando o power estiver ligado
  }

  void powerOff(String espId) {
    mqttService.publishMessage(espId, "OFF");
    stripState.isOn.value = false;
    notifyListeners(); // Notifica quando o power estiver desligado
  }

  void getState(String espId) {
    mqttService.publishMessage(espId, "state");
  }

  StripStateModel parseStripState(String input) {

    RegExp regExp = RegExp(
        r"State: (\w+), Color: R:(\d+) G:(\d+) B:(\d+), Brightness: (\d+), Velocity: (\d+), Effect: (\w+)");
    RegExpMatch? match = regExp.firstMatch(input);

    if (match != null) {
      bool isOn = match.group(1)! == "ON";
      int red = int.parse(match.group(2)!);
      int green = int.parse(match.group(3)!);
      int blue = int.parse(match.group(4)!);
      int brightness = int.parse(match.group(5)!);
      int velocity = int.parse(match.group(6)!);
      bool isSolid = match.group(7)! == "SOLID_COLOR";

      return StripStateModel(
        red: red,
        green: green,
        blue: blue,
        brightness: brightness,
        velocity: velocity,
        isSolid: isSolid,
        isOn: isOn,
      );
    } else {
      throw FormatException("String no formato inválido");
    }
  }

  void mqttCallback(String message) {

    if (message.contains("State")) {
      stripState = parseStripState(message);
      notifyListeners(); // Notifica mudanças no estado
    }

    if (message.contains("OFF")) {
      stripState.isOn.value = false;
      notifyListeners(); // Notifica quando o power for desligado
    }

    if (message.contains("ON")) {
      stripState.isOn.value = true;
      notifyListeners(); // Notifica quando o power for ligado
    }

    if (message.contains("Brightness set")) {
      RegExp regExp = RegExp(r"to (\d+)");
      RegExpMatch? match = regExp.firstMatch(message);
      if (match != null) {
        stripState.brightness.value = int.parse(match.group(1)!);
        notifyListeners(); // Notifica mudanças no brilho
      }
    }

    if (message.contains("Velocity set")) {
      RegExp regExp = RegExp(r"to (\d+)");
      RegExpMatch? match = regExp.firstMatch(message);
      if (match != null) {
        stripState.velocity.value = int.parse(match.group(1)!);
        notifyListeners(); // Notifica mudanças na velocidade
      }
    }
  }

  void registerCallback(String espId)
  {
    mqttService.subscribeToTopic(espId, mqttCallback);
    
  }

  void subscribeToTopic(String espId) {
    mqttService.subscribeToTopic(espId, mqttCallback);
  }
}
