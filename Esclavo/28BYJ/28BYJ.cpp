/*
  Programa que realiza un giro completo del motor 28BYJ-48 en conjunto con el controlador
  basado en ULN2003, detiene 5 segundos y luego comienza nuevamente. La secuencia es la de
  paso completo simple (wave drive) energizando de a una bobina por vez utilizando una
  matriz para su definicion. 
  Alimentar Arduino con fuente de alimentacion externa de 6 a 12 Vdc.
 */
#include <Arduino.h>
#include "28BYJ.h"
int paso [4][4] =   // matriz (array bidimensional) con la secuencia de pasos
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};
void secuencia(int demora){
  for (int i = 0; i < 512; i++) // 512*4 = 2048 pasos
  {
    for (int j = 0; i < 4; j++)   // bucle recorre la matriz de a una fila por vez
    {                               // para obtener los valores logicos a aplicar
      digitalWrite(IN1, paso[j][0]);  // a IN1, IN2, IN3 e IN4
      digitalWrite(IN2, paso[j][1]);
      digitalWrite(IN3, paso[j][2]);
      digitalWrite(IN4, paso[j][3]);
      delay(DEMORA);
    }
  }
}

void secuencia_inv(int demora){
  for (int i = 0; i < 512; i++) // 512*4 = 2048 pasos
  { 
   for (int j = 3; j >= 0; j--)
    {
      digitalWrite(IN4, paso[j][3]);  // bucle recorre la matriz de a una fila por vez
      digitalWrite(IN3, paso[j][2]);  // en sentido inverso
      digitalWrite(IN2, paso[j][1]);
      digitalWrite(IN1, paso[j][0]);
      delay(DEMORA);
    }
  }
}

void detener(){
  digitalWrite(IN1, LOW); // detiene el motor.
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
