/*
  Capitulo 30 de Arduino desde cero en Español.
  Programa que realiza un giro completo del motor 28BYJ-48 en conjunto con el controlador
  basado en ULN2003, detiene 5 segundos y luego comienza nuevamente. La secuencia es la de
  paso completo simple (wave drive) energizando de a una bobina por vez utilizando una
  matriz para su definicion. 
  Alimentar Arduino con fuente de alimentacion externa de 6 a 12 Vdc.

  Autor: bitwiseAr  

*/
#include "28BYJ.h"

void setup() {
  pinMode(IN1, OUTPUT);   // todos los pines como salida
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {

  secuencia(DEMORA);
  detener();
  delay(5000);

}
