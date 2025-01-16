import 'package:flutter/material.dart';
import 'package:iotfy_app/screens/widgets_components/relay_card.dart';

class SecondScreen extends StatefulWidget {
  const SecondScreen({super.key});

  @override
  State<SecondScreen> createState() => _SecondScreenState();
}

class _SecondScreenState extends State<SecondScreen> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Second Screen'),
      ),
      body: LayoutBuilder(
        builder: (context, constraints) {

          return Center(
            child: ConstrainedBox(
              constraints: BoxConstraints(
                maxWidth: 600,
              ),
              child: Padding(
                padding: const EdgeInsets.symmetric(horizontal: 16.0), 
                child: ListView(
                    children: [
                      Container(
                        margin: const EdgeInsets.only(top: 8.0), // Margem abaixo do card
                        child: RelayCard(espId: 'esp01_luz_quarto', title: 'luz quarto'),
                      ),
                      Container(
                        margin: const EdgeInsets.only(top: 8.0), // Margem abaixo do card
                        child: RelayCard(espId: 'esp01_luz_banheiro', title: 'luz banheiro'),
                      ),
                      Container(
                        margin: const EdgeInsets.only(top: 8.0), // Margem abaixo do card
                        child: RelayCard(espId: 'esp01_luz_banheiro_descanso', title: 'mini luz'),
                      ),
                    ],
                ),
              ),
            ),
          );
        },
      ),
    );
  }
}
