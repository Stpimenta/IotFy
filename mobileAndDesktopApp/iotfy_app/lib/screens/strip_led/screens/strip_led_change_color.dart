import 'package:flutter/material.dart';
import 'package:flutter_circle_color_picker/flutter_circle_color_picker.dart';
import 'package:IotFy/screens/strip_led/controller/strip_led_controller.dart';
import 'package:IotFy/services/client_mqtt_service.dart';
import 'package:provider/provider.dart';

class StripLedChangeColor extends StatefulWidget {
  final String espId;
  const StripLedChangeColor({super.key, required this.espId});

  @override
  State<StripLedChangeColor> createState() => _StripLedChangeColorState();
}

class _StripLedChangeColorState extends State<StripLedChangeColor> {
  final CircleColorPickerController _controller = CircleColorPickerController();
  double sliderValue = 0;
  int brightnessValue = 0;

  @override
  void initState() {
    super.initState();
    final stripController = context.read<StripLedController>();


    sliderValue = (stripController.stripState.brightness.value * 100) / 255;
    brightnessValue = sliderValue.toInt();


    _controller.color = Color.fromRGBO(
      stripController.stripState.red.value,
      stripController.stripState.green.value,
      stripController.stripState.blue.value,
      1.0,
    );
  }

  @override
  Widget build(BuildContext context) {
    return Consumer<StripLedController>(
      builder: (context, stripController, child) {
     
        Color currentColor = Colors.white;

        return Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [
              CircleColorPicker(
                controller: _controller,
                onChanged: (color) {
                  setState(() {
                    currentColor = color;
                  });
                },
                onEnded: (color) {
                  int red = color.red;
                  int green = color.green;
                  int blue = color.blue;
                  stripController.setColor(red, green, blue, widget.espId);
                },
                colorCodeBuilder: (context, color) {
                  return const SizedBox();
                },
              ),
              Column(
                children: [
                  SizedBox(
                    width: 300,
                    child: Column(
                      children: [
                        Align(
                          alignment: Alignment.topLeft,
                          child: Text(
                            'brilho $brightnessValue%',
                            style: const TextStyle(fontSize: 20),
                          ),
                        ),
                        Slider(
                          min: 0,
                          max: 100,
                          value: sliderValue,
                          onChanged: (value) {
                            setState(() {
                              sliderValue = value;
                              brightnessValue = value.toInt();
                            });
                          },
                          onChangeEnd: (value) {
                            int valor255 = ((value * 255) / 100).toInt();
                            stripController.setBrightness(valor255, widget.espId);
                          },
                        ),
                      ],
                    ),
                  ),
                ],
              ),
            ],
          ),
        );
      },
    );
  }
}
