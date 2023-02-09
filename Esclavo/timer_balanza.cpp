#include "timer_balanza.h"

Q2HX711 celda(DT, CLK);
volatile float peso = 0.0;

void setupTimer(){
  // Desabilito interrupciones globales poniendo en cero el Bit 7 del registro SREG. 
  // Uso AND para no modificar el estado del resto de los bits.
  SREG = (SREG & 0b01111111);
  // Habilito interrupcion de Timer 2 por Desborde: cuando pasa de 255 a cero genera una interrupción. 
  // Uso OR para no afectar al resto de bits.
  TIMSK2 = TIMSK2|0b00000001; 
  // Al usar frecuencia de 15.625HZ, cada incremento del contador se realizará cada 1/15.625 = 64 uS. Como cuenta de 0 a 255, 
  // la función asociada a la interrupción se ejecutará cada 256 * 64uS =  16,38 mseg
  TCCR2B = 0b00000111; 
  // Preparar el modulo HX711 para la celda de carga
  celda.readyToSend();
  //Habilito interrupciones globales
  SREG = (SREG & 0b01111111) | 0b10000000; 
}

ISR(TIMER2_OVF_vect){
  peso = (celda.read() - 8388608) / ESCALA;
}