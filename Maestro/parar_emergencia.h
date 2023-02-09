#ifndef PARAR_EMERGENCIA_H
#define PARAR_EMERGENCIA_H
  #define PARAR 11 // final de carrera z
  #include <Arduino.h>
	extern volatile byte codEmergencia;
  void setupInterrup();
  void PararEmergencia();
#endif // PARAR_EMERGENCIA_H
