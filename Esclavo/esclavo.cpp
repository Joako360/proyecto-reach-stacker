#include "esclavo.h"
//#include "interrup_esclavo.h"

Servo servo1;           // crea objeto
AccelStepper BYJ = AccelStepper(TIPO_INTR, IN1, IN3, IN2, IN4);
byte envio[LARGO_TRAMA],recibo[LARGO_TRAMA], lecByte, ang, idx;
int vel;
float peso;

void setupMotores(){
  // configurar velocidad maxima en pasos por segundo:
  BYJ.setMaxSpeed(VMAX);
  // configurar la aceleraccion en pasos por segundo^2:
  BYJ.setAcceleration(ACEL);
  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX);  // inicializacion de servo
}

void enviarRespuesta(byte cmd, byte x){
  envio[0] = HEAD;                    // Cabecera
  envio[1] = cmd;                     // Lectura del sensor de carga
  envio[2] = x;                       // Respuesta
  envio[3] = TAIL;                    // Cola
  if (Serial.availableForWrite() >= LARGO_TRAMA){
    Serial.write( envio, LARGO_TRAMA );	// transmitir mensaje
    Serial.flush();
  }
}

void ejecutarComando(byte trama[]){
  switch( trama[1] ){         // ejecutar comando

    case CMD_LEE:             // lectura sensor/celda de carga
      {
        //funcion lectura sensor/celda de carga y envio de dato
        peso = (celda.read() - 8264000) / 533700.0;
        lecByte = (celda.read() / 16777216.0 * 255.0);
        enviarRespuesta(CMD_LEE, lectByte);
      }
      break;
      
    default:                  // Comando Inva'lido
      break;
  }
}

void recibirComando(){
	bool tramaValida = false;
	byte bytesDisp = Serial.available();
	byte buffer[bytesDisp];
	if (bytesDisp){
		for (idx = 0; idx < bytesDisp; idx++){
			buffer[idx] = Serial.read();
			if (buffer[idx] == TAIL){
				recibo[0] = buffer[idx-3];
				recibo[1] = buffer[idx-2];
				recibo[2] = buffer[idx-1];
				recibo[3] = buffer[idx];
				tramaValida = true;
			}
		}
	}
	if (tramaValida) ejecutarComando(recibo);
	else return;
}