#include "esclavo.h"


Servo servo1;           // crea objeto
byte trama[4], idx;
float peso;

void enviarRespuesta( float x ){
  trama[0] = HEAD;                          // Cabecera
  trama[1] = CMD_LEE;                        // Lectura del sensor de carga
  trama[2] = (byte)x;                       // Respuesta
  trama[3] = TAIL;                          // Cola
  RS485.write( trama, 4 );        // transmitir mensaje
  RS485.flush();
}

void ejecutarComando(){
  Serial.println("Ejectutando comando!!!");
  switch( trama[2] ){               // ejecutar comando

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
