/*
  Simple programa para controlar un motor del tipo bipolar NEMA 17 mediante el
  controlador driver A4988 logrando un giro de media vuelta en un sentido y en otro
*/

#include "NEMA17.h"

void setup()
{
  pinMode(STEP, OUTPUT);  // pin 4 como salida
  pinMode(DIR, OUTPUT);   // pin 5 como salida
}

void loop()
{
  giro();
  delay(2000);          // demora de 2 segundos

  giro_inv();
  delay(2000);          // demora de 2 segundos
}
