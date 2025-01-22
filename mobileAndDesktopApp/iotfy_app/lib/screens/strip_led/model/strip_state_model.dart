import 'package:flutter/foundation.dart';

class StripStateModel {
  late ValueNotifier<int> red;
  late ValueNotifier<int> green;
  late ValueNotifier<int> blue;
  late ValueNotifier<int> brightness;
  late ValueNotifier<int> velocity;
  late bool isSolid;
  late ValueNotifier<bool> isOn;

  StripStateModel({
    required int red,
    required int green,
    required int blue,
    required int brightness,
    required int velocity,
    required this.isSolid,
    required bool isOn,
  })  : red = ValueNotifier<int>(red),
        green = ValueNotifier<int>(green),
        blue = ValueNotifier<int>(blue),
        brightness = ValueNotifier<int>(brightness),
        velocity = ValueNotifier<int>(velocity),
        isOn = ValueNotifier<bool>(isOn);
}
