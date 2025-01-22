import 'package:flutter/material.dart';
import 'package:IotFy/services/client_mqtt_service.dart';
import 'package:provider/provider.dart';

class ReconnectModal extends StatelessWidget {
  const ReconnectModal({super.key});

  @override
  Widget build(BuildContext context) {
    final mqttService  = Provider.of<MQTTService>(context);

    return Scaffold(
              body: Center(
                // Centraliza o conteúdo na tela inteira
                child: SizedBox(
                  height: 100,
                  child: Column(
                    mainAxisAlignment:
                        MainAxisAlignment.spaceAround, // Alinha verticalmente
                    crossAxisAlignment:
                        CrossAxisAlignment.center, // Alinha horizontalmente
                    children: [
                      Text("maximum attempts to reconnect"),
                      ElevatedButton(
                        onPressed: (){
                          mqttService.connect();
                          mqttService.resetAttempConnect();
                        }, 
                        child: Text("try again")
                      )
                    ],
                  ),
                ),
              ),
            );
  }
}