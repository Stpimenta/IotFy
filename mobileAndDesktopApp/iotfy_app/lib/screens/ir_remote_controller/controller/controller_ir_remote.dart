import 'package:IotFy/services/client_mqtt_service.dart';

class ControllerIrRemote {
  final MQTTService _mqttService;

  // Parâmetro nomeado corrigido
  ControllerIrRemote({required MQTTService mqttService}) : _mqttService = mqttService;

  void sendIrCode(String espid, String code) {
    _mqttService.publishMessage(espid, 'ir/$code');
  }
}
