#include "esclavo.h"


Servo servo1;           // crea objeto
AccelStepper BYJ = AccelStepper(TIPO_INTR, IN1, IN3, IN2, IN4);
byte trama[LARGO_TRAMA], idx, lec;
int vel;
float peso;

void setupMotores(){
  // configurar velocidad maxima en pasos por segundo:
  BYJ.setMaxSpeed(VMAX);
  // configurar la aceleraccion en pasos por segundo^2:
  BYJ.setAcceleration(ACEL);

  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX);  // inicializacion de servo
}

void enviarRespuesta( float x ){
  trama[0] = HEAD;                          // Cabecera
  trama[1] = CMD_LEE;                        // Lectura del sensor de carga
  trama[2] = (byte)x;                       // Respuesta
  trama[3] = TAIL;                          // Cola
  Serial.write( trama, LARGO_TRAMA );        // transmitir mensaje
  Serial.flush();
}

void ejecutarComando(){
  switch( trama[1] ){               // ejecutar comando

    case CMD_LEE:                           // lectura sensor/celda de carga
      {
      //funcion lectura sensor/celda de carga y envio de dato  
      }
      break;

    case CMD_MOV:                           // Mover paso a paso de efector
      {
      // funcion 28BYJ
      lec = trama[2];
      vel = round(map(lec, 0, 255, -500, 500));
      // cambiar la velocidad del motor en pasos por segundo:
      BYJ.setSpeed(vel);
      // mover el motor con la velocidad definida en setSpeed():
      BYJ.runSpeed();
      }
      break;

    case CMD_ROT:                           // Rotar servomotor
      {
      int angulo = (int)trama[2];
      if(angulo<=180) //verificamos que sea un valor en el rango del servo
          servo1.write(angulo); //movemos el servomotor al ángulo correspondiente.
      }
      break;
      
    default:                                // Comando Inva'lido
      break;
  }
}
