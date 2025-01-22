import 'package:flutter/material.dart';
import 'package:IotFy/screens/strip_led/controller/strip_led_controller.dart';
import 'package:provider/provider.dart';
import 'package:IotFy/screens/strip_led/components/strip_led_effects_list.dart';

class StripLedEffects extends StatefulWidget {
  final String espId;
  const StripLedEffects({super.key, required this.espId});

  @override
  StripLedEffectsState createState() => StripLedEffectsState();
}

class StripLedEffectsState extends State<StripLedEffects> {
  double brightSliderValue = 0;
  double velocitSliderValue = 0;
  int brightSValue = 0;
  int velocitValue = 0;

  @override
  void initState() {
    super.initState();
    final stripController = context.read<StripLedController>();

    // Inicializando os sliders com os valores do controlador
    brightSliderValue = (stripController.stripState.brightness.value * 100) / 255;
    velocitSliderValue = (stripController.stripState.velocity.value * 100) / 255;
    brightSValue = brightSliderValue.toInt();
    velocitValue = velocitSliderValue.toInt();
  }

  @override
  Widget build(BuildContext context) {
    final stripLedEffectsList = effectsLedList;

    return Consumer<StripLedController>(
      builder: (context, stripController, child) {
        return Column(
          children: [
            SizedBox(
              height: MediaQuery.of(context).size.height * 0.6,
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
                            stripController.setEffect(stripLedEffectsList[index].code,widget.espId);
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
                  // Controle de Brilho
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text('Brilho $brightSValue%', style: TextStyle(fontSize: 20)),
                      Slider(
                        min: 0,
                        max: 100,
                        value: brightSliderValue,
                        onChanged: (value) {
                          setState(() {
                            brightSliderValue = value;
                            brightSValue = value.toInt();
                          });
                        },
                        onChangeEnd: (value) {
                          int valor255 = ((value * 255) / 100).toInt();
                          stripController.setBrightness(valor255, widget.espId);
                        },
                      ),
                    ],
                  ),
                  // Controle de Velocidade
                  Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text('Velocidade $velocitValue%', style: TextStyle(fontSize: 20)),
                      Slider(
                        min: 0,
                        max: 100,
                        value: velocitSliderValue,
                        onChanged: (value) {
                          setState(() {
                            velocitSliderValue = value;
                            velocitValue = value.toInt();
                          });
                        },
                        onChangeEnd: (value) {
                          int valor255 = ((value * 255) / 100).toInt();
                          stripController.setVelocity(valor255, widget.espId);
                        },
                      ),
                    ],
                  ),
                ],
              ),
            ),
          ],
        );
      },
    );
  }
}
