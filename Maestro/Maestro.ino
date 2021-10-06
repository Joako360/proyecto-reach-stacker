/**
   RS-485 con MAX485 y Arduino

   Comunicacion: Full-duplex
   Roll: Master
   Placa: Arduino MEGA 2560
*/
#include "maestro.h"
#include "NEMA17/NEMA17.h"

void setup() {
  // Configurar Serial para utilizarlo como monitor
  Serial.begin(19200);

  // Configurar Serial3 para el bus RS-485
  Serial3.begin(9600);

  pinMode(STEP, OUTPUT);  // pin 4 como salida
  pinMode(DIR, OUTPUT);   // pin 5 como salida
}

void loop() {

  if ( Serial.available() ) {
    char c = Serial.read();
    int r;
    switch (c) {
      case '0':
        if ( Serial.available() )
          char c = Serial.read();
        enviarComando(CMD_MOV, c);
        break;

      case '1':
        if ( Serial.available() )
          char c = Serial.read();
        enviarComando(CMD_ROT, c);
        break;

      case '2':
        enviarComando(CMD_LEE, 0x00);
        Serial.print("Respuesta Carga: ");
        r = recibirRespuesta();
        if ( r == -1 )
          Serial.println( "No se recibio' respuesta" );
        else
          Serial.println(r);
        break;

      default:
        break;
    }
  }
}
