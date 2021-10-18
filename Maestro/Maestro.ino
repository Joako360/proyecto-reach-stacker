/**
   RS-485 con MAX485 y Arduino

   Comunicacion: Full-duplex
   Roll: Master
   Placa: Arduino MEGA 2560
*/
#include "maestro.h"
//#include "NEMA17/NEMA17.h"

int lect0, lect1, lect2;
byte ang, velSlv, velMst;

void setup() {
  // Configurar Serial para el bus RS-485
  Serial.begin(19200);
  pinMode(LED_BUILTIN, OUTPUT);//inicializamos el pin del Led como salida
  // Set the maximum speed in steps per second:
  NEMA.setMaxSpeed(1000);
  // Set the maximum acceleration in steps per second^2:
  NEMA.setAcceleration(30);
}

void loop() {

  if ( Serial.available() ) {
    int r = recibirRespuesta();
    if (alarma(r))
      digitalWrite(LED_BUILTIN,HIGH);
    else
      digitalWrite(LED_BUILTIN, LOW);
  }
  lect0 = analogRead(A0);//leemos el valor del potenciómetro (de 0 a 1023) 
  lect1 = analogRead(A1);
  lect2 = analogRead(A2);
  ang = (byte)map(lect0, 0, 1023, 0, 180); // escalamos la lectura a un valor de ángulo (entre 0 y 180) 
  velSlv = (byte)map(lect1, 0, 1023, 0, 255);
  velMst = map(lect2, 0, 1023, -400, 400);
  //---enviamos el ángulo para mover el servo------
  enviarComando(CMD_ROT, ang);
  //---solicitamos una lectura del sensor----------
  enviarComando(CMD_MOV, velSlv);
  NEMA.setSpeed(velMst);
  NEMA.runSpeed();
}
