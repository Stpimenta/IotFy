import 'package:IotFy/routes/routes.dart';
import 'package:IotFy/screens/strip_led/controller/strip_led_controller.dart';
import 'package:IotFy/services/client_mqtt_service.dart';
import 'package:IotFy/theme/theme.dart';
import 'package:flutter/material.dart';
import 'package:flutter_dotenv/flutter_dotenv.dart';

import 'package:IotFy/screens/ir_remote_controller/controller/controller_ir_remote.dart';



import 'package:provider/provider.dart';


void main() async{
  await dotenv.load(); // Carrega o arquivo .env

  runApp(
    MultiProvider(
      providers: [
        ChangeNotifierProvider(
          create: (_) => MQTTService(dotenv.env['BROKER'] as String)
            ..initialize()
        ),
        Provider<ControllerIrRemote>(
          create: (context) => ControllerIrRemote(
            mqttService: Provider.of<MQTTService>(context,listen: false)
          ),
        ),
        ChangeNotifierProvider<StripLedController>(
          create: (context) => StripLedController(
            mqttService: Provider.of<MQTTService>(context, listen: false),
          ),
        ),

      ],
      child: const MyApp(), // Widget raiz
    ),
  );
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'IotFy',
      theme: appThema,
      initialRoute: '/home',
      routes: appRoutes(context)
    );
  }
}
