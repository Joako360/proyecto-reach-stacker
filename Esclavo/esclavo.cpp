#include <Arduino.h>
#include <SoftwareSerial.h>;
#include <Servo.h>      // incluye libreria de Servo

// Comunicacion

#define HEAD 0x02	// ASCII STX Comienza transmision
#define TAIL 0x03	// ASCII ETX Finaliza transmision

// Comandos soportados
#define CMD_LEE 0x11	// Leer sensor/celda de carga
#define CMD_ROT 0x12	// Rotar servomotor un angulo
#define CMD_MOV 0x13	// Apertura/cierre de efector

// Formato de Trama: <HEAD> <CMD> <DATA> <TAIL>
// Si es enviado por el maestro, el esclavo debe ejecuar <CMD>, posiblemente con un valor <DATA>
// Si es enviado por el esclavo, el maestro podria recibir <DATA> como resultado de ejecutar <CMD>

SoftwareSerial RS485(0, 1);    // RX, TX

byte trama[4], idx;
float peso;
int PINSERVO = 2;       // pin 2 conectado a señal del servo
int PULSOMIN = 1000;    // pulso minimo en microsegundos
int PULSOMAX = 2000;    // pulso maximo en microsegundos
Servo servo1;           // crea objeto

void enviarRespuesta( float x ){
  trama[0] = HEAD;                          // Cabecera
  trama[1] = CMD_LEE                        // Lectura del sensor de carga
  trama[2] = (byte)x;                       // Respuesta
  trama[3] = TAIL;                          // Cola
  RS485.write( trama_respuesta, 4 );        // transmitir mensaje
  RS485.flush();
}

void ejecutarComando(){
  Serial.println("Ejectutando comando!!!");
  switch( trama_entrada[2] ){               // ejecutar comando

    case CMD_LEE:                           // lectura sensor/celda de carga
      //funcion lectura sensor/celda de carga y envio de dato  
      break;

    case CMD_MOV:                           // Mover paso a paso de efector
      // funcion 28BYJ
      break;

    case CMD_ROT:                           // Rotar servomotor
      // funcion rotar servomotor
      break;
      
    default:                                // Comando Inva'lido
      break;
  }
}
