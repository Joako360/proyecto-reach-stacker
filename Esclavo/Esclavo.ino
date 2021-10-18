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
//#include "28BYJ/28BYJ.h"
//AccelStepper BYJ = AccelStepper(TIPO_INTR, IN1, IN3, IN2, IN4);
//Servo servo1;

void setup() {
  // Configurar Serial a 19200 baudios para utilizar el bus 485 a 9600
  Serial.begin(19200);
  
  idx = 0;  // Indice explorador de trama entrante
  // Set the maximum steps per second:
  BYJ.setMaxSpeed(1000);
  // Set the maximum acceleration in steps per second^2:
  BYJ.setAcceleration(200);

  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX);  // inicializacion de servo
}


void loop() {

  if( !Serial.available() )
    return;

  Serial.readBytes(trama, 4);
    
  if (trama[0]!=HEAD) // principio de trama incorrecta
    return;

  if (trama[3]==TAIL)   // verificar que fin de trama termine bien
    ejecutarComando();          // el comando solo se ejecuta si la cola es correcta

    
}
