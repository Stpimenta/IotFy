import 'package:flutter/material.dart';
import 'package:iotfy_app/models/effects_led_strip_model.dart';
import 'package:iotfy_app/screens/strip_led/components/strip_led_effects_list.dart';

class StripLedEffects extends StatefulWidget {
  final String espId;
  const StripLedEffects({super.key, required this.espId});

  @override
  StripLedEffectsState createState() => StripLedEffectsState();
}

class StripLedEffectsState extends State<StripLedEffects> {
  final List<EffectsLedStripModel> stripLedEffectsList = effectsLedList;

  double brightSliderValue = 0;
  int brightSValue = 0;

  double velocitSliderValue = 0;
  int velocitValue = 0;

  @override
  Widget build(BuildContext context) {

    double height = MediaQuery.of(context).size.height;


    return Column(
      children: [
        Column(
          children: [
            SizedBox(
              height: height * 0.6,

              child: ListView(
                children: List.generate(

                  stripLedEffectsList.length,
                  (index) {
                    return Align(

                      alignment: Alignment.center,
                      child: Container(

                        margin: const EdgeInsets.only(top: 15),
                        child: ElevatedButton(
                        
                          onPressed: () {
                            print(stripLedEffectsList[index].code);
                          },

                          child: Text(stripLedEffectsList[index].name),
                        ),

                      ),
                    );
                  },
                ),
              ),
            ),

            SizedBox(
              width: 300,
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text('Brilho $brightSValue%', style: TextStyle(fontSize: 20),),
                      Slider(
                        min: 0,
                        max: 100,
                        value: brightSliderValue,
                        onChanged: (value) {
                          setState(() {
                            brightSliderValue = value.ceilToDouble();
                            brightSValue = value.ceil();
                          });
                        },
                        onChangeEnd: (value) {
                          print(brightSValue);
                        },
                      ),
                    ],
                  ),

                  Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text('Velocidade $brightSValue%', style: TextStyle(fontSize: 20),),
                      Slider(
                        min: 0,
                        max: 100,
                        value: velocitSliderValue,
                        onChanged: (value) {
                          setState(() {
                            velocitSliderValue = value.ceilToDouble();
                            velocitValue = value.ceil();
                          });
                        },
                        onChangeEnd: (value) {
                          print(velocitValue);
                        },
                      ),
                    ],
                  ),
                ],
              ),
            ),
          ],
        ),
      ],
    );
  }
}
