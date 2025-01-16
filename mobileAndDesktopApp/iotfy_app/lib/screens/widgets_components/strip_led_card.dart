import 'package:flutter/material.dart';
import 'package:iotfy_app/models/nav_to_strip_led_model.dart';




class StripLedCard extends StatefulWidget {

  //espid
  final String espId;
  final String title;
  const StripLedCard({super.key, required this.espId, required this.title} );
  @override
  State<StripLedCard> createState() => _StripLedState();
}

class _StripLedState extends State<StripLedCard> {
  bool switchState = false;

  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {


    return LayoutBuilder(
      builder: (context, constraints) 
      {  
        double cardWidth = (constraints.maxWidth * 0.9).clamp(0, 600);
       

        return InkWell(
          onTap: (){
              Navigator.pushNamed(
                context, 
                '/strip_led',
                arguments: NavToStripLedModel(espId: widget.espId)
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
                    child: Icon(Icons.earbuds)
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
                    child: null
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