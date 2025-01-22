import 'package:flutter/material.dart';
import 'package:IotFy/models/nav_to_strip_led_model.dart';
import 'package:IotFy/screens/strip_led/controller/strip_led_controller.dart';
import 'package:provider/provider.dart';

class StripLedCard extends StatefulWidget {
  // espId
  final String espId;
  final String title;
  const StripLedCard({super.key, required this.espId, required this.title});
  
  @override
  State<StripLedCard> createState() => _StripLedState();
}

class _StripLedState extends State<StripLedCard> {


  @override
  void initState() {
    super.initState();
    final stripLedController = context.read<StripLedController>();
    stripLedController.registerCallback(widget.espId);
    stripLedController.getState(widget.espId);
  }

  @override
  Widget build(BuildContext context) {
    
    return LayoutBuilder(
      builder: (context, constraints) {
        double cardWidth = (constraints.maxWidth * 0.9).clamp(0, 600);

        return Consumer<StripLedController>(
          builder: (context, stripLedController, child) {
            return InkWell(
              onTap: () {
                Navigator.pushNamed(
                  context,
                  '/strip_led',
                  arguments: NavToStripLedModel(espId: widget.espId),
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
                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceAround,
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: [
                      SizedBox(
                        width: cardWidth * 0.2,
                        child: Icon(Icons.earbuds),
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
                      // Aqui você pode adicionar o switch ou outros widgets que dependem do estado
                      SizedBox(
                        width: cardWidth * 0.2,
                        child: IconButton(
                          icon: Icon(Icons.power_rounded, size: 40, 
                                  color: stripLedController.stripState.isOn.value? Colors.green : Colors.white ,
                                ),
                          onPressed: () {
                            
                            if(stripLedController.stripState.isOn.value)
                            {
                                stripLedController.powerOff(widget.espId);
                            }

                            else
                            {
                                stripLedController.powerOn(widget.espId);
                            }

                          },
                        ),
                      ),
                    ],
                  ),
                ),
              ),
            );
          },
        );
      },
    );
  }
}
