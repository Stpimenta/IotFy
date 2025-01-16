import 'package:flutter/material.dart';
import 'package:iotfy_app/models/remote_button_model.dart';


class ButtonsProjector {

  final RemoteButtonModel power = RemoteButtonModel(
    icon: Icon(Icons.power_settings_new, color: Colors.white, size: 35),
    code: 'BD807F',
  );

  final RemoteButtonModel mute = RemoteButtonModel(
    icon: Icon(Icons.volume_off, color: Colors.white, size: 35),
    code: 'BD56A9',
  );

  final RemoteButtonModel up = RemoteButtonModel(
    icon: Icon(Icons.arrow_upward, color: Colors.white, size: 35),
    code: 'BDD02F',
  );

  final RemoteButtonModel down = RemoteButtonModel(
    icon: Icon(Icons.arrow_downward, color: Colors.white, size: 35),
    code: 'BDF00F',
  );

  final RemoteButtonModel left = RemoteButtonModel(
    icon: Icon(Icons.arrow_back, color: Colors.white, size: 35),
    code: 'BD926D',
  );

  final RemoteButtonModel right = RemoteButtonModel(
    icon: Icon(Icons.arrow_forward, color: Colors.white, size: 35),
    code: 'BD52AD',
  );

  final RemoteButtonModel enter = RemoteButtonModel(
    icon: Icon(Icons.radio_button_checked, color: Colors.white, size: 35),
    code: 'BDB04F',
  );

  final RemoteButtonModel returnBtn = RemoteButtonModel(
    icon: Icon(Icons.arrow_back_ios, color: Colors.white, size: 35),
    code: 'BD2AD5',
  );

  final RemoteButtonModel menu = RemoteButtonModel(
    icon: Icon(Icons.menu, color: Colors.white, size: 35),
    code: 'BD50AF',
  );

  final RemoteButtonModel input = RemoteButtonModel(
    icon: Icon(Icons.input, color: Colors.white, size: 35),
    code: 'BD20DF',
  );

  final RemoteButtonModel volDown = RemoteButtonModel(
    icon: Icon(Icons.volume_down, color: Colors.white, size: 35),
    code: 'BD08F7',
  );

  final RemoteButtonModel volUp = RemoteButtonModel(
    icon: Icon(Icons.volume_up, color: Colors.white, size: 35),
    code: 'BD30CF',
  );

  final RemoteButtonModel hdmi1 = RemoteButtonModel(
    icon: Icon(Icons.settings_input_hdmi, color: Colors.white, size: 35),
    code: '1FEA05F',
  );

  final RemoteButtonModel hdmi2 = RemoteButtonModel(
    icon: Icon(Icons.settings_input_hdmi, color: Colors.white, size: 35),
    code: '1FEE01F',
  );

  final RemoteButtonModel hdmi3 = RemoteButtonModel(
    icon: Icon(Icons.settings_input_hdmi, color: Colors.white, size: 35),
    code: '1FE10EF',
  );

  

}