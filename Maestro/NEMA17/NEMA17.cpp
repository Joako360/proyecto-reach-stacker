#include <Arduino.h>
#include "NEMA17.h"

void giro(){
    digitalWrite(DIR, HIGH);    // giro en un sentido
  for(int i = 0; i < 200; i++){ // 200 pasos para motor de 0.9 grados de angulo de paso
    digitalWrite(STEP, HIGH);   // nivel alto
    delay(10);                  // por 10 mseg
    digitalWrite(STEP, LOW);    // nivel bajo
    delay(10);                  // por 10 mseg
  }
}
void giro_inv(){
  digitalWrite(DIR, LOW);     // giro en sentido opuesto
  for(int i = 0; i < 200; i++){
    digitalWrite(STEP, HIGH); 
    delay(10);
    digitalWrite(STEP, LOW);
    delay(10);
  }
}
