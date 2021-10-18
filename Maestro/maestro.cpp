#include "maestro.h"

AccelStepper NEMA = AccelStepper(TIPO_INTR, STEP, DIR);
byte trama[4], idx;

void enviarComando(byte cmd, byte data){
  trama[0] = HEAD;
  trama[1] = cmd;
  trama[2] = data;
  trama[3] = TAIL;
  Serial.write(trama, 4);
  Serial.flush();  
}

int recibirRespuesta(){
  delay(2000);
  Serial.readBytes( trama, 4 );

  if( trama[0] != HEAD )    // error en la cabecera
    return -1;

  if( trama[3] != TAIL )    // error en el trailer
    return -1;

  return trama[2];
}

bool alarma(int r){
  return (r<921)?false:true;
}
