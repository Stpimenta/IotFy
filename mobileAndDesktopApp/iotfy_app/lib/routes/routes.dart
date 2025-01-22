import 'package:flutter/material.dart';
import 'package:IotFy/screens/home/connection_resolver.dart';
import 'package:IotFy/screens/ir_remote_controller/ir_remote.dart';
import 'package:IotFy/screens/strip_led/strip_led.dart';


//{Map<String, Widget Function(BuildContext)> routes = const <String, WidgetBuilder>{}}

Map<String, WidgetBuilder>  appRoutes (BuildContext context)
{
    return{
        '/home':(context) => ConnectionResolver(),
        '/ir_controller':(context) => IrRemote(),
        '/strip_led':(context) => StripLed(),
    };
} 