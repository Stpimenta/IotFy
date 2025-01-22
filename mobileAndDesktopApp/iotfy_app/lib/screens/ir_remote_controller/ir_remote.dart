import 'package:flutter/material.dart';
import 'package:IotFy/models/nav_to_projector_controller_model.dart';
import 'package:IotFy/screens/ir_remote_controller/components/controllers_remote_view/haroku_controller%20copy.dart';
import 'package:IotFy/screens/ir_remote_controller/components/controllers_remote_view/projector_controller.dart';


class IrRemote extends StatelessWidget {
  const IrRemote({super.key});
  
  @override
  Widget build(BuildContext context) 
  {
    final NavToProjectorControllerModel args = ModalRoute.of(context)?.settings.arguments as NavToProjectorControllerModel;

    if(args.controllerName.contains('projector'))
    { 
      return ProjectorController(espId: args.espId,title: args.title,);
    }

    if(args.controllerName.contains('haroku'))
    {
      return HarokuController(espId: args.espId,title: args.title,);
    }
    
    return Text('controle desconhecido');
  }
}