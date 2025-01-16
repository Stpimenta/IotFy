import 'package:flutter/material.dart';
import '../../services/client_mqtt_service.dart';
import 'package:provider/provider.dart';


class RelayCard extends StatefulWidget {

  //espid
  final String espId;
  final String title;
  const RelayCard({super.key, required this.espId, required this.title});
  @override
  State<RelayCard> createState() => _RelayCardState();
}

class _RelayCardState extends State<RelayCard> {
  bool switchState = false;

  @override
  void initState() {
    super.initState();
    final mqttService = context.read<MQTTService>();
    
    void mqttCallback(String message) {

      setState(() {
     
            if (message.toLowerCase().contains('turn_on_relay') || message.toLowerCase().contains('true')) {
              switchState = true;
            } 
            
            if (message.toLowerCase().contains('turn_off_relay') || message.toLowerCase().contains('false')) {
              switchState = false;
            }
    
      });
    }

    mqttService.subscribeToTopic(widget.espId, mqttCallback);
    mqttService.publishMessage(widget.espId, 'state');

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
                    child:  Icon( switchState == false?  Icons.tungsten_outlined : Icons.tungsten_rounded , size: 30,)
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
                    child:  Switch(
                      value: switchState, 
                      onChanged: (bool state){
          
                        if(state)
                        {
                          mqttService.publishMessage(widget.espId, 'turn_on_relay');
                        }
                        
                        else
                        {
                          mqttService.publishMessage(widget.espId, 'turn_off_relay');
                        }
                      }
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