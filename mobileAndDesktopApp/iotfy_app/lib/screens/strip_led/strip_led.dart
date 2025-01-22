import 'package:flutter/material.dart';
import 'package:IotFy/models/nav_to_strip_led_model.dart';
import 'package:IotFy/screens/strip_led/screens/strip_led_change_color.dart';
import 'package:IotFy/screens/strip_led/screens/strip_led_effects.dart';

class StripLed extends StatefulWidget {
  const StripLed({super.key});

  @override
  State<StripLed> createState() => _StripLedState();
}

class _StripLedState extends State<StripLed> {

  int index = 0;

  void navToIndex(int value)
  {
    setState(() {
       index = value;
    });
  }

  @override
  Widget build(BuildContext context) {
    final NavToStripLedModel args = ModalRoute.of(context)?.settings.arguments as NavToStripLedModel;

    List<Widget> screens= [
      StripLedChangeColor(espId: args.espId,),
      StripLedEffects(espId: args.espId,),
    ];
    
    
    return Scaffold(
      appBar: AppBar(title: Text('Led strip')),

      body: IndexedStack(
        index: index,
        children: screens,
      ),

      bottomNavigationBar: BottomNavigationBar(
        currentIndex: index,
        onTap: navToIndex,
        selectedItemColor: const Color.fromARGB(255, 227, 228, 230), 
        unselectedItemColor: const Color.fromARGB(151, 163, 163, 163), 
        type: BottomNavigationBarType.fixed,
        items: [
          BottomNavigationBarItem(icon: Icon(Icons.color_lens), label: 'change color'),
          BottomNavigationBarItem(icon: Icon(Icons.gradient), label: 'effects')
        ]
      ),

    );
  }
}