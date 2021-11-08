/**
   RS-485 con MAX485 y Arduino

   Comunicacion: Full-duplex
   Roll: Master
   Placa: Arduino UNO
*/
#include "maestro.h"

int js[4], velMst;      // Joystick de 4GL
byte ang, velSlv;
float peso

void setup() {
  // Configurar Serial para el bus RS-485
  Serial.begin(19200);
  pinMode(LED_BUILTIN, OUTPUT);//inicializamos el pin del Led como salida
  setupMotores();
}

void loop() {

  if ( Serial.available() ) {
    int r = recibirRespuesta();
	if (r!=1){
		peso = map(r, 0, 255, 0, 5);
	}
    alarma(r);
  }
  for(byte i = 0; i < 4; i++){
    js[i] = analogRead(i);
  }
  ang = (byte)round(js[0] * (180.0 / 1023.0)); // escalamos la lectura a un valor de ángulo (entre 0 y 180) 
  velSlv = (byte)round(js[1] * 0.25);
  velMst = map(js[2], 0, 1023, -400, 400);
  //---enviamos el ángulo para mover el servo------
  enviarComando(CMD_ROT, ang);
  //---solicitamos una lectura del sensor----------
  enviarComando(CMD_MOV, velSlv);
  NEMA.setSpeed(velMst);
  NEMA.runSpeed();
}
