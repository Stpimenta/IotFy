import 'package:flutter/material.dart';
import 'package:IotFy/screens/ir_remote_controller/components/buttons/buttons_projector.dart';
import 'package:IotFy/screens/ir_remote_controller/controller/controller_ir_remote.dart';
import 'package:provider/provider.dart';

class ProjectorController extends StatelessWidget {

  final buttons = ButtonsProjector();
  final String espId;
  final String title;
  
  ProjectorController({super.key, required this.espId, required this.title});
 

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
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
    
                        children: [
          
                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.power.code);},
                                icon:buttons.power.icon
                            ),

                             IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.volUp.code);},
                                icon:buttons.volUp.icon
                            ),

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.volDown.code);},
                                icon:buttons.volDown.icon
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
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        crossAxisAlignment: CrossAxisAlignment.end,
                        children: [

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.returnBtn.code);},
                                icon:buttons.returnBtn.icon
                            ),

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.menu.code);},
                                icon:buttons.menu.icon
                            ),

                            IconButton(
                                onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.mute.code);},
                                icon:buttons.mute.icon
                            ),
                        
                        ],
                      ),

                      Row(
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        crossAxisAlignment: CrossAxisAlignment.end,
                        children: [

                            Column(
                              children: [
                                IconButton(
                                  onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.hdmi1.code);},
                                  icon:buttons.hdmi1.icon
                                ),
                                Text('hdmi 1', style: TextStyle(fontSize: 15),)
                              ],
                            ),
                            
                            Column(
                              children: [
                                IconButton(
                                  onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.hdmi2.code);},
                                  icon:buttons.hdmi2.icon
                                ),
                                Text('hdmi 2', style: TextStyle(fontSize: 15),)
                              ],
                            ),

                            Column(
                              children: [
                                IconButton(
                                  onPressed: (){controllerIrRemote.sendIrCode(espId, buttons.hdmi3.code);},
                                  icon:buttons.hdmi3.icon
                                ),
                                Text('hdmi 3', style: TextStyle(fontSize: 15),)
                              ],
                            )
                        ],
                      ),
                ],
              ),
          ),
        ),

    );
  }
}