import 'package:flutter/material.dart';
import 'package:IotFy/models/remote_button_model.dart';


class ButtonsHaroku {
  
  final RemoteButtonModel back = RemoteButtonModel(
    icon: Icon(Icons.arrow_back, size: 35, color: Colors.white),
    code: '57436798',
  );

  final RemoteButtonModel home = RemoteButtonModel(
    icon: Icon(Icons.home, size: 35, color: Colors.white),
    code: '5743C13E',
  );

  final RemoteButtonModel up = RemoteButtonModel(
    icon: Icon(Icons.arrow_upward, size: 35, color: Colors.white),
    code: '57439867',
  );

  final RemoteButtonModel down = RemoteButtonModel(
    icon: Icon(Icons.arrow_downward, size: 35, color: Colors.white),
    code: '5743CC33',
  );

  final RemoteButtonModel left = RemoteButtonModel(
    icon: Icon(Icons.arrow_back, size: 35, color: Colors.white),
    code: '57437887',
  );

  final RemoteButtonModel right = RemoteButtonModel(
    icon: Icon(Icons.arrow_forward, size: 35, color: Colors.white),
    code: '5743B44B',
  );

  final RemoteButtonModel enter = RemoteButtonModel(
    icon: Icon(Icons.check, size: 35, color: Colors.white),
    code: '574355AA',
  );

  final RemoteButtonModel returnBtn = RemoteButtonModel(
    icon: Icon(Icons.arrow_back_ios, size: 35, color: Colors.white),
    code: '57431FE0',
  );

  final RemoteButtonModel asterisk = RemoteButtonModel(
    icon: Icon(Icons.star, size: 35, color: Colors.white),
    code: '57438778',
  );

  final RemoteButtonModel advancedLeft = RemoteButtonModel(
    icon: Icon(Icons.chevron_left, size: 35, color: Colors.white),
    code: '57432CD3',
  );

  final RemoteButtonModel play = RemoteButtonModel(
    icon: Icon(Icons.play_arrow, size: 35, color: Colors.white),
    code: '574332CD',
  );

  final RemoteButtonModel advancedRight = RemoteButtonModel(
    icon: Icon(Icons.chevron_right, size: 35, color: Colors.white),
    code: '5743AA55',
  );


}