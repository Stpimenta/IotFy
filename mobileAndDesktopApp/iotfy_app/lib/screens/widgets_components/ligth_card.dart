import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import '../../services/client_mqtt_service.dart';

class LightCard extends StatefulWidget {
  final String espId;
  final String title;

  // LIGHT1 ou LIGHT2
  final int lightNumber;

  const LightCard({
    super.key,
    required this.espId,
    required this.title,
    required this.lightNumber,
  });

  @override
  State<LightCard> createState() => _LightCardState();
}

class _LightCardState extends State<LightCard> {
  bool switchState = false;

  late final String onCommand;
  late final String offCommand;
  late final String stateCommand;

  @override
  void initState() {
    super.initState();

    final mqttService = context.read<MQTTService>();

    onCommand = "LIGHT${widget.lightNumber}_ON";
    offCommand = "LIGHT${widget.lightNumber}_OFF";
    stateCommand = "LIGHT${widget.lightNumber}_STATE";

    void mqttCallback(String message) {
      if (!mounted) return;

      setState(() {
        if (message == onCommand) {
          switchState = true;
        }

        if (message == offCommand) {
          switchState = false;
        }
      });
    }

    mqttService.subscribeToTopic(widget.espId, mqttCallback);

    // solicita estado atual
    mqttService.publishMessage(
      widget.espId,
      stateCommand,
    );
  }

  @override
  Widget build(BuildContext context) {
    final mqttService = context.read<MQTTService>();

    return LayoutBuilder(
      builder: (context, constraints) {
        double cardWidth =
            (constraints.maxWidth * 0.9).clamp(0, 600);

        return Card(
          shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(20),
          ),
          elevation: 1,
          shadowColor: const Color.fromARGB(
            255,
            192,
            240,
            255,
          ),
          child: SizedBox(
            width: cardWidth,
            height: 100,
            child: Row(
              mainAxisAlignment:
                  MainAxisAlignment.spaceAround,
              crossAxisAlignment:
                  CrossAxisAlignment.center,
              children: [
                SizedBox(
                  width: cardWidth * 0.2,
                  child: Icon(
                    switchState
                        ? Icons.tungsten_rounded
                        : Icons.tungsten_outlined,
                    size: 30,
                  ),
                ),

                SizedBox(
                  width: cardWidth * 0.6,
                  child: Text(
                    widget.title,
                    style: const TextStyle(fontSize: 20),
                    maxLines: 1,
                    overflow: TextOverflow.ellipsis,
                    textAlign: TextAlign.center,
                  ),
                ),

                SizedBox(
                  width: cardWidth * 0.2,
                  child: Switch(
                    value: switchState,
                    onChanged: (bool state) {
                      mqttService.publishMessage(
                        widget.espId,
                        state ? onCommand : offCommand,
                      );
                    },
                  ),
                ),
              ],
            ),
          ),
        );
      },
    );
  }
}