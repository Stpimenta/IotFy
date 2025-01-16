import 'package:flutter/material.dart';
import 'package:flutter_svg/flutter_svg.dart';
import 'package:iotfy_app/models/nav_to_projector_controller_model.dart';
import 'package:iotfy_app/screens/ir_remote_controller/components/buttons/buttons_projector.dart';
import 'package:iotfy_app/screens/ir_remote_controller/controller/controller_ir_remote.dart';
import 'package:provider/provider.dart';



class ProjectorControllerCard extends StatefulWidget {

  //espid
  final String espId;
  final String title;
  final String type;
  const ProjectorControllerCard({super.key, required this.espId, required this.title, required this.type} );
  @override
  State<ProjectorControllerCard> createState() => _RelayCardState();
}

class _RelayCardState extends State<ProjectorControllerCard> {
  bool switchState = false;

  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {

    final  controllerIrRemote = Provider.of<ControllerIrRemote>(context, listen: false);
    final ButtonsProjector buttons = ButtonsProjector();

    return LayoutBuilder(
      builder: (context, constraints) 
      {  
        double cardWidth = (constraints.maxWidth * 0.9).clamp(0, 600);
       

        return InkWell(
          onTap: (){
              Navigator.pushNamed(
                context, 
                '/ir_controller',
                arguments: NavToProjectorControllerModel(espId: widget.espId, controllerName: widget.type, title: widget.title)
              );
          },
          child: Card(
            shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(20),
           
            ),
          
            elevation: 1,
            shadowColor: Color.fromARGB(255, 192, 240, 255),
            
            child: SizedBox(
              width: cardWidth,
              height: 100,
              // constraints: BoxConstraints(maxWidth: 200),
          
              child: Row(
                //aling
                mainAxisAlignment: MainAxisAlignment.spaceAround,
                crossAxisAlignment: CrossAxisAlignment.center,
          
                children: [
                  
                  SizedBox(
                    width: cardWidth * 0.2,
                    child: SvgPicture.asset('assets/icons/google_tv_remote.svg', height: 35),
                  ),
                 
          
                  SizedBox(
                    width: cardWidth * 0.6, 
                    child: Text(
                      widget.title,
                      style: TextStyle(fontSize: 20),
                      maxLines: 1,
                      overflow: TextOverflow.ellipsis,
                      textAlign: TextAlign.center,
                    ),
                  ),
          
                  SizedBox(
                    width: cardWidth * 0.2,
                    child: IconButton(
          
                          onPressed: (){

                               controllerIrRemote.sendIrCode(widget.espId, buttons.power.code);
                  
                          }, 
                          icon: Icon(Icons.power_settings_new_rounded, color: Colors.white, size: 40,)
          
                        )
                  ),
                  
                ],
          
              )
            ),
          ),
        );
      },
    );
  }
    
      
}