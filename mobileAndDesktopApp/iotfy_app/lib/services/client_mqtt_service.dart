
import 'package:flutter/material.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';
// import 'package:flutter_dotenv/flutter_dotenv.dart';

class MQTTService extends ChangeNotifier {

  late MqttServerClient client;
  late String broker;
  final String clientId = DateTime.now().toString();
  final Map<String, Function(String)> _listeners = {}; // Topic Manager
  ValueNotifier<bool> isConnected = ValueNotifier(false);
  ValueNotifier<bool> maxReconnectAttempsNot = ValueNotifier(false);
  int _reconnectAttemps = 0;
  final int _maxReconnectAttemps = 3;

  MQTTService (String urlBroker)
  {
     broker = urlBroker;
  }


  // Initializes the MQTT connection and message listening
  Future<void> initialize() async {
    await connect();
    _listenToMessages();
  }

  // Method to connect to the MQTT broker
  Future<void> connect() async {
    client = MqttServerClient(broker, clientId);
    client.port = 1883;
    client.keepAlivePeriod = 60;
    client.onConnected = onConnected;
    client.onDisconnected = onDisconnected;

    final connMessage = MqttConnectMessage()
        .withClientIdentifier(clientId)
        .startClean()
        .withWillTopic('willtopic')
        .withWillMessage('client disconnected')
        .withWillQos(MqttQos.atMostOnce);

    client.connectionMessage = connMessage;

    try 
    {
      // print('Connecting to MQTT broker...');
      await client.connect();
    } 
    
    catch (e) 
    {
      // print('Error: $e');
      client.disconnect();
    }

  }

  // Callback functions
  void onConnected() {
    //print('Connected to broker');
    isConnected.value = true;
    notifyListeners(); 
    _listenToMessages();
  }

  void onDisconnected() {
    isConnected.value = false;
    notifyListeners(); 
    _toReconnect();
  }

  // Subscribe to a specific topic and register a callback function
  void subscribeToTopic(String espid, Function(String) callback) {
    client.subscribe('$espid/sender', MqttQos.atMostOnce);
    String topic = '$espid/sender';
    _listeners[topic] = callback;

  }

  // Listen to received messages and notify listeners
  void _listenToMessages() {

    client.updates?.listen((List<MqttReceivedMessage<MqttMessage>>? updates) {
      for (var update in updates!) {
        final topic = update.topic;
        final recMessage = update.payload as MqttPublishMessage;
        final message = MqttPublishPayload.bytesToStringAsString(recMessage.payload.message);
        //print('Message received on topic $topic: $message');
        
        //callback
        _callBackListeners(topic, message);
      }
    });
  }

  //notify listeners 
  void _callBackListeners(String topic, String message) {
    
    final callback = _listeners[topic];
    callback?.call(message); // Chama a função associada ao tópico
    
  }

  // Remove listeners 
  void removeListenersForTopic(String topic) {
    _listeners.remove('$topic/sender');
    //print('Listeners removed for topic: $topic');
  }


  void publishMessage(String espid, String message)
  {
    if (client.connectionStatus?.state == MqttConnectionState.connected) {
      final builder = MqttClientPayloadBuilder();
      builder.addString(message);

      // Envia a mensagem com QOS 1 (ensuring delivery)
      client.publishMessage('$espid/reciver', MqttQos.atMostOnce, builder.payload!);
      //print('Message sent to topic: $espid/reciver');
    } 
  }

  Future <void> _toReconnect () async
  {
     _reconnectAttemps ++;

     if(_reconnectAttemps >= _maxReconnectAttemps)
     {
        maxReconnectAttempsNot.value = true;
        notifyListeners();
        return;
     }

     else
     {
        await Future.delayed(Duration(seconds: 5));
        connect();
        return;
     }
  }


  //try reconect again
  void resetAttempConnect()
  {
     _reconnectAttemps = 0;
     maxReconnectAttempsNot.value = false;
     notifyListeners();
  }

}



// Example usage (uncomment for testing)
// void main() async {
//   final mqttService = MQTTService('192.168.1.201', 'esp01_luz_quarto');

//   // Initialize the MQTT service
//   await mqttService.initialize();

//   // Component 1: Subscribe to the 'home/living_room' topic and provide a specific callback
//   mqttService.subscribeToTopic('home/living_room', (message) {
//     print('Living Room: $message');
//     if (message.contains('turn_on')) {
//       print('Turn on the light in the living room.');
//     } else if (message.contains('turn_off')) {
//       print('Turn off the light in the living room.');
//     }
//   });

//   // Component 2: Subscribe to the 'home/kitchen' topic with another callback
//   mqttService.subscribeToTopic('home/kitchen', (message) {
//     print('Kitchen: $message');
//     if (message.contains('turn_on')) {
//       print('Turn on the light in the kitchen.');
//     } else if (message.contains('turn_off')) {
//       print('Turn off the light in the kitchen.');
//     }
//   });
// }
