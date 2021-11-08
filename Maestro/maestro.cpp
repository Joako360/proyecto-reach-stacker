#include "maestro.h"

AccelStepper NEMA = AccelStepper(TIPO_INTR, STEP, DIR);
byte trama[LARGO_TRAMA], idx;

void setupMotores(){
  // Configurar la velocidad máxima en pasos por segundo
  NEMA.setMaxSpeed(VMAX);
  // configurar la aceleracion en pasos por segundo^2:
  NEMA.setAcceleration(ACEL);
}

void enviarComando(byte cmd, byte data){
  trama[0] = HEAD;
  trama[1] = cmd;
  trama[2] = data;
  trama[3] = TAIL;
  Serial.write(trama, LARGO_TRAMA);
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

void alarma(float peso){
  if (peso > 4.5)
    digitalWrite(LED_BUILTIN,HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}
