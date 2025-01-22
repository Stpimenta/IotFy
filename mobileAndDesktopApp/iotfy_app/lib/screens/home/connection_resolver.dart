import 'package:flutter/material.dart';
import 'package:IotFy/screens/home/home_screen.dart';
import 'package:IotFy/screens/home/loading.dart';
import 'package:IotFy/services/client_mqtt_service.dart';
import 'package:provider/provider.dart';

class ConnectionResolver extends StatelessWidget {
  const ConnectionResolver({super.key});

  @override
  Widget build(BuildContext context) {
    return Consumer<MQTTService>(
      builder:(context, mqttService, child)
      {
        if(mqttService.isConnected.value)
        {
            return HomeScreen();
        }
        
        else
        {
          return Loading();
        }
      }
      
    );
  }
}