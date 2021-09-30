/**
 * Ejemplo RS-485 con MAX485 y Arduino
 * 
 * Comunicacion: Half-duplex
 * Roll: Master
 * Placa: Arduino MEGA 2560
 */
#include "maestro.h"
}

void setup() {
  // Configurar Serial para utilizarlo como monitor
  Serial.begin(19200);

  // Configurar Serial3 para el bus RS-485
  Serial3.begin(9600);
}

void loop() {
  
  if( Serial.available() ){
    char c = Serial.read();
    int r;
    switch(c){
      case '0':
        enviarComando(CMD_A);
        break;
        
      case '1':
        enviarComando(CMD_B);
        break;
        
      case '2':
        enviarComando(CMD_C);
        break;

      case '3':
        enviarComando(CMD_D);
        Serial.print("Respuesta D: ");
        r = recibirRespuesta();
        if( r == -1 )
          Serial.println( "No se recibio' respuesta" );
        else
          Serial.println(r);
        break;

      case '4':
        enviarComando(CMD_E);
        Serial.print("Respuesta E: ");
        r = recibirRespuesta();
        if( r == -1 )
          Serial.println( "No se recibio' respuesta" );
        else
          Serial.println(r);
        break;

      case '5':
        enviarComando(CMD_F);
        Serial.print("Respuesta F: ");
        r = recibirRespuesta();
        if( r == -1 )
          Serial.println( "No se recibio' respuesta" );
        else
          Serial.println(r);
        break;

      default:
        break;
    }
  }
}
