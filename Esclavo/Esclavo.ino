/**
 * RS-485 con MAX485 y Arduino
 * 
 * Comunicacion: Full-dup
 * Roll: Slave
 * Placa: Arduino UNO R3
 * Comandos: 0x11 - Leer sensor/celda de carga (solo lectura)
 *           0x12 - Rotar servomotor un angulo (escritura)
 *           0x13 - Apertura/cierre de efector (escritura)
 */
#include "esclavo.h"
#include "28BYJ/28BYJ.h"
#include "../global.h"

void setup() {
  // Configurar Serial a 19200 baudios (para el monitor serie)
  Serial.begin(19200);

  // Configurar para utilizar el bus 485 a 9600
  RS485.begin(9600);
  
  idx = 0;  // Indice explorador de trama entrante
  
  // 28BJY-48
  pinMode(IN1, OUTPUT);   // todos los pines como salida
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX);  // inicializacion de servo
}


void loop() {

  if( !RS485.available() )
    return;

  byte incoming = RS485.read();
  Serial.print("Recibido: ");
  Serial.println(incoming);
    
  if( idx == 0 ){           // principio de trama
    if( incoming != HEAD ) // trama incorrecta
      return;

    trama[idx] = incoming;
    idx++;
  }
  else if ( idx > 0 && idx < 4 ){ // comando, dato o cola
    trama[idx++] = incoming;      //
     
    if ( idx == 3 ){                // fin de trama
      if( trama[idx] == TAIL )      // verificar que termine bien
        ejecutarComando();          // el comando solo se ejecuta si la cola es correcta
      idx = 0;
    }
  }
}
