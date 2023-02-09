#ifndef TIMER_BALANZA
#define TIMER_BALANZA
  #define DT A2
  #define CLK A3
  #define ESCALA 533700.0 // Calibrar
	#include <Arduino.h>
  #include <Q2HX711.h>
  extern Q2HX711 celda;
	extern volatile float peso;
	void setupTimer();
#endif // TIMER_BALANZA
