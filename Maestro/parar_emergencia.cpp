#include "parar_emergencia.h"
volatile byte codEmergencia;
void setupInterrup(){
  pinMode(PARAR,INPUT_PULLUP);
  codEmergencia = 0;	//codigo 0: No hay emergencia
  // Configuro el pin 2 como interrupción externa, indico que la rutina de atención de la interrupción es funcionIntExterna.
  // La interrupción se generará con flancos descendentes (Falling).
  attachInterrupt(digitalPinToInterrupt(PARAR), PararEmergencia, FALLING);
}
void PararEmergencia(){
	codEmergencia = 1;	//Codigo 1: parada de emergencia
}
