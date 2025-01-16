// ignore: duplicate_ignore
// ignore: file_names
// ignore_for_file: file_names

import 'package:flutter/material.dart';
import 'package:iotfy_app/screens/ir_remote_controller/components/buttons/buttons_haroku.dart';
import 'package:iotfy_app/screens/ir_remote_controller/controller/controller_ir_remote.dart';
import 'package:provider/provider.dart';

class HarokuController extends StatelessWidget {

  final buttons = ButtonsHaroku();
  final String espId;
  final String title;
  
  HarokuController({super.key, required this.espId, required this.title});
 

  @override
  Widget build(BuildContext context) {
    
    final controllerIrRemote = Provider.of<ControllerIrRemote>(context, listen: false);

    return Scaffold(
        appBar: AppBar(title: Text(title),),
        body: Center(
          child: ConstrainedBox(
              constraints: BoxConstraints(
                maxWidth: 270
              ),
              
              child: Column(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            
                children: [
                  
                      Row(
                        mainAxisAlignment: MainAxisAlignment.spaceAround,
    
                        children: [
          
                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.back.code);},
                                icon:buttons.back.icon
                            ),

                             IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.home.code);},
                                icon:buttons.home.icon
                            ),
                        ],
                      ),
          
                      Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.up.code);},
                                icon:buttons.up.icon
                            ),
                        ],
                      ),
                      
                       Row(
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        children: [
                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.left.code);},
                                icon:buttons.left.icon
                            ),

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.enter.code);},
                                icon:buttons.enter.icon
                            ),

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.right.code);},
                                icon:buttons.right.icon
                            ),
                        ],
                      ),

                      Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.down.code);},
                                icon:buttons.down.icon
                            ),
                        ],
                      ),

                      Row(
                        mainAxisAlignment: MainAxisAlignment.spaceAround,
                        crossAxisAlignment: CrossAxisAlignment.end,
                        children: [

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.returnBtn.code);},
                                icon:buttons.returnBtn.icon
                            ),

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.asterisk.code);},
                                icon:buttons.asterisk.icon
                            ),
                        
                        ],
                      ),

                      Row(
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        crossAxisAlignment: CrossAxisAlignment.end,
                        children: [

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.advancedLeft.code);},
                                icon:buttons.advancedLeft.icon
                            ),

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.play.code);},
                                icon:buttons.play.icon
                            ),

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.advancedRight.code);},
                                icon:buttons.advancedRight.icon
                            ),
                        
                        ],
                      ),
                ],
              ),
          ),
        ),

    );
  }
}