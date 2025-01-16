import 'package:flutter/material.dart';
import 'package:iotfy_app/screens/home/widgets_components/reconnect_modal.dart';
import 'package:iotfy_app/services/client_mqtt_service.dart';
import 'package:provider/provider.dart';

class Loading extends StatelessWidget {
  const Loading({super.key});

  @override
  Widget build(BuildContext context) {
    return Consumer<MQTTService>(builder: (context, mqttService, child) {
        if(!mqttService.maxReconnectAttempsNot.value)
        {
            return Scaffold(
              body: Center(
                // Centraliza o conteúdo na tela inteira
                child: SizedBox(
                  height: 300,
                  child: Column(
                    mainAxisAlignment:
                        MainAxisAlignment.spaceAround, // Alinha verticalmente
                    crossAxisAlignment:
                        CrossAxisAlignment.center, // Alinha horizontalmente
                    children: [
                      Image.asset(
                        'assets/logo.png',
                        height: 150,
                      ),
                      CircularProgressIndicator(),
                    ],
                  ),
                ),
              ),
            );
        } 
        else
        { 
          return ReconnectModal();
        } 
    });
  }
}