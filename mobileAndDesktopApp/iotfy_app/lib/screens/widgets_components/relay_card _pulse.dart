import 'package:flutter/material.dart';
import 'package:flutter_svg/svg.dart';
import '../../services/client_mqtt_service.dart';
import 'package:provider/provider.dart';


class RelayCardPulse extends StatefulWidget {

  //espid
  final String espId;
  final String title;
  const RelayCardPulse({super.key, required this.espId, required this.title});
  @override
  State<RelayCardPulse> createState() => _RelayCardPulseState();
}

class _RelayCardPulseState extends State<RelayCardPulse> {
  bool switchState = false;
  int pulseDuration = 500;

  @override
  void initState() {
    super.initState();
    final mqttService = context.read<MQTTService>();
    

     void pulseUiSimulation() async
    {
        setState(() {
            switchState = true;
        });

        await Future.delayed(Duration(milliseconds: pulseDuration));

        setState(() {
            switchState = false;
        });

    }

    void mqttCallback(String message) {

    

        if (message.toLowerCase().contains('pulse')) {
           pulseUiSimulation();
        }
    }

    mqttService.subscribeToTopic(widget.espId, mqttCallback);
  }

  @override
  Widget build(BuildContext context) {
    final mqttService = context.read<MQTTService>();
    return LayoutBuilder(
      builder: (context, constraints) 
      {  
        double cardWidth = (constraints.maxWidth * 0.9).clamp(0, 600);
       

        return Card(
          
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
                    child:  SvgPicture.asset(
                              'assets/icons/avg_time.svg',
                              height: 30,
                              width: 30,
                            )
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
                    child:  IconButton(

                      icon:  switchState
                              ? CircularProgressIndicator(
                                  strokeWidth: 2,
                                  color: Colors.white,
                                )
                              : Icon(Icons.send),

                      onPressed: (){
                          mqttService.publishMessage(widget.espId, "pulse/$pulseDuration");
                      },
                    )
                  ),
                  
                ],
          
              )
            ),
          );
      },
    );
  }
    
      
}