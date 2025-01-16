import 'package:flutter/material.dart';

final ThemeData appThema = ThemeData(
  useMaterial3: true, // Enable Material 3
        // Defining the custom color scheme
        colorScheme: ColorScheme(
          brightness: Brightness.light,
          primary: Color(0xFFD4CDA6), // Primary color (for navigation bar, etc.)
          onPrimary: Color(0xFFD4CDA6), // Text color on primary elements
          secondary: Colors.white, // Secondary color
          onSecondary: Colors.white, // Text color on secondary elements
          surface: Color(0xFF0E1D22), // Surface background
          onSurface: Colors.white, // Text color on surfaces
          error: Colors.red, // Color for error messages
          onError: Colors.white, // Text color on error elements
        ),
        iconTheme: IconThemeData(
          color: Colors.white, // Icon color
        ),
        switchTheme: SwitchThemeData(
          thumbColor: WidgetStateProperty.all(Colors.white), // Thumb color of the switch
        ),
        buttonTheme: ButtonThemeData(
          buttonColor: Colors.white, // Button background color
          textTheme: ButtonTextTheme.primary, // Text color on buttons
        ),
        elevatedButtonTheme: ElevatedButtonThemeData(
          style: ButtonStyle(
            backgroundColor: WidgetStateProperty.all(Color.fromARGB(255, 167, 161, 128)), // ElevatedButton background color
            foregroundColor: WidgetStateProperty.all(Colors.white), // ElevatedButton text color
            animationDuration: Duration(milliseconds: 500), 
        
          ),
          
        ),
        floatingActionButtonTheme: FloatingActionButtonThemeData(
          backgroundColor: Color(0xFFD4CDA6),
          foregroundColor: Colors.white,
          elevation: 6,
          hoverElevation: 10
        ),
        cardTheme: CardTheme(
            color: Color.fromARGB(255, 24, 50, 58),
        ),

        sliderTheme: SliderThemeData(
          activeTrackColor: Color(0xFFD4CDA6), // Cor da parte ativa do slider
          inactiveTrackColor: Colors.grey, // Cor da parte inativa do slider
          thumbColor: Colors.white, // Cor do "polegar" (círculo que move)
          overlayColor:  Color.fromARGB(69, 212, 205, 166), // Cor da parte ativa do slider
          valueIndicatorColor: const Color.fromARGB(0, 0, 0, 0), // Cor do indicador de valor
       ),
);