import 'package:flutter/material.dart';
import 'package:flutter_colorpicker/flutter_colorpicker.dart';


class StripLedChangeColor extends StatefulWidget {
  final  String espId;
  const StripLedChangeColor({super.key, required this.espId});

  @override
  State<StripLedChangeColor> createState() => _StripLedChangeColorState();
}

class _StripLedChangeColorState extends State<StripLedChangeColor> {

 
  double sliderValue = 0;
  int brightnessValue = 0;

  Color currentColor = Colors.black;


  //modal and data picker

  Widget buildColorPicker () => ColorPicker(
    pickerColor: currentColor, 
    onColorChanged: (color) {
      setState(() {
          currentColor  = color;
          print(color);
      });
    },
    enableAlpha: false,
    displayThumbColor: false,
  );


  void showDataPicker (BuildContext context)
  {
    showDialog(
      context: context, 
      builder: (BuildContext context){
          return AlertDialog(
            actions: [
              // Align(
              //   alignment: Alignment.topRight,
              //   child: IconButton(
              //     onPressed: (){
              //       Navigator.of(context).pop();
              //     }, 
              //     icon:Icon(Icons.close, size: 30,), // Ou Icons.cancel
                    
              //   ),
              // ),
              buildColorPicker(),


            
            ],
          );
      }
    );
  }

  @override
  Widget build(BuildContext context) {

    double screenWidth = MediaQuery.of(context).size.width;
 

    return 
    Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: [

              //show current strip color
              ConstrainedBox(
                constraints: BoxConstraints(
                  maxWidth: 350,
                  maxHeight: 350
                ),


                child: GestureDetector(
                  onTap: () => showDataPicker(context),
                  child: Container(
                    height: screenWidth * 0.9,
                    width: screenWidth * 0.9,
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(300),
                      color:currentColor
                    ),
                  ),
                ),
              ),


              //button show color picker
              Column(
                children: [
                  SizedBox(
                    width: 300,
                    child: Column(
                      children: [
                        Align(alignment: Alignment.topLeft, child: Text('brilho $brightnessValue%', style: TextStyle(fontSize: 20),)),
                        Slider(
                          min: 0,
                          max:100,
                          value: sliderValue, 
                          onChanged: (value)  {
                            setState(() {
                                sliderValue = value.ceilToDouble();
                                brightnessValue = value.ceil();
                            });
                          },
                          onChangeEnd: (value) {
                              print(sliderValue);
                          },

                          
                        ),

                        ElevatedButton(
                          onPressed: (){
                            showDataPicker(context);
                          }, 
        
                          child: Text('change color', style: TextStyle(fontSize: 20),)
                        )
                      ],
                    )
                  ),
                ],
              ),
            ],
        ),
    ); 
  }
}