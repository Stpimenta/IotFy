import 'package:flutter/material.dart';
import 'package:iotfy_app/screens/widgets_components/projector_controller_card.dart';
import 'package:iotfy_app/screens/widgets_components/relay_card.dart';
import 'package:iotfy_app/screens/widgets_components/strip_led_card.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _SeconHomeScreen();
}

class _SeconHomeScreen extends State<HomeScreen> {
  // GlobalKey para o Scaffold permite o acesso em widgets mesmos estes não estando na arvore
  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: _scaffoldKey, // Atribuindo o GlobalKey ao Scaffold
      appBar: PreferredSize(
        preferredSize: Size.fromHeight(60.0), // Aumenta a altura da AppBar
        child: AppBar(
          automaticallyImplyLeading: false, // Remove o ícone do drawer automátic

          //stack permite sobrepor elementos neste caso para centralizar a logoS
          title: Stack(
            alignment: Alignment.center,
            children: [
              // Logo centralizada
              Center(
                child: Image.asset(
                  'assets/logo.png',
                  width: 40, 
                ),
              ),
              
              Positioned(
                left: -10, // Distância da esquerda
                top: 5, // Distância do topo (ajuste conforme necessário)
                child: IconButton(
                  icon: Icon(Icons.menu), // Ícone do menu (Drawer)
                  onPressed: () {
                    // Usando o GlobalKey para abrir o Drawer
                    _scaffoldKey.currentState?.openDrawer();
                  },
                ),
              ),
            ],
          ),

        ),
      ),
      

      //drawer
      drawer: Drawer(
                backgroundColor: Color.fromARGB(255, 54, 54, 59),
                child: Center(child: Text("em breve"))
              ),
      drawerScrimColor: Color.fromARGB(111, 13, 15, 24), //cor do fundo quando abrir o drawer


      body: LayoutBuilder(
        builder: (context, constraints) {
          return Center(
              child: Padding(
                padding: const EdgeInsets.symmetric(horizontal: 16.0),
                child: ListView(
                  children: 
                  [
                      Align(
                        alignment: Alignment.center,
                        child: Container(
                          margin: const EdgeInsets.only(top: 8.0),
                          child: RelayCard(espId: 'esp01_luz_quarto', title: 'luz quarto'),
                        ),
                      ),
                      
                      Align(
                        alignment: Alignment.center,
                        child: Container(
                          margin: const EdgeInsets.only(top: 8.0),
                          child: RelayCard(espId: 'esp01_luz_banheiro', title: 'luz banheiro'),
                        ),
                      ),
                      
                      Align(
                        alignment: Alignment.center,
                        child: Container(
                          margin: const EdgeInsets.only(top: 8.0),
                          child: RelayCard(espId: 'esp01_luz_banheiro_descanso', title: 'mini luz'),
                        ),
                      ),
                      
                      Align(
                        alignment: Alignment.center,
                        child: Container(
                          margin: const EdgeInsets.only(top: 8.0),
                          child: ProjectorControllerCard(
                            espId: 'boa',
                            title: 'controle projetor',
                            type: 'projector',
                          ),
                        ),
                      ),
                      
                      Align(
                        alignment: Alignment.center,
                        child: Container(
                          margin: const EdgeInsets.only(top: 8.0),
                          child: ProjectorControllerCard(
                            espId: 'boaa',
                            title: 'controle haroku',
                            type: 'haroku',
                          ),
                        ),
                      ),
                      
                      Align(
                        alignment: Alignment.center,
                        child: Container(
                          margin: const EdgeInsets.only(top: 8.0),
                          child: StripLedCard(espId: 'boaaa', title: 'fita led'),
                        ),
                      ),
                  ]

                ),
              ),
          );
        },
      ),


      //floating button
      floatingActionButton: FloatingActionButton(onPressed:null, child: Icon(Icons.add, color: Colors.white)),

      
    );
  }
}
