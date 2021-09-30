#include <Arduino.h>
#include <SoftwareSerial.h>
#include "global.h"

byte trama[3], idx;

void enviarComando(byte cmd){
  trama[0] = HEAD;
  trama[1] = cmd;
  trama[2] = TAIL;
  Serial3.write(trama, 3);
  Serial3.flush();  
}

int recibirRespuesta(){
  delay(2000);
  Serial3.readBytes( trama, 3 );

  if( trama[0] != HEAD )    // error en la cabecera
    return -1;

  if( trama[2] != TAIL )    // error en el trailer
    return -1;

  return trama[1];
}
