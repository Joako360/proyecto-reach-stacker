#include "maestro.h"

AccelStepper NEMA1 = AccelStepper(TIPO_INTR1, STEP1, DIR1);
AccelStepper NEMA2 = AccelStepper(TIPO_INTR2, STEP2, DIR2);
byte envio[LARGO_TRAMA], recibo[LARGO_TRAMA], idx = 0;
int vel1, vel2;

void setupMotores(){
	// Motor 1
	NEMA1.setEnablePin(ENABLE);
	NEMA1.setMaxSpeed(VMAX);				// Configurar velocidad máxima en pasos por segundo
	NEMA1.setAcceleration(ACEL);		// configurar aceleracion en pasos por segundo^2:
	pinMode(FINAL_CARRERA1, INPUT);	// final de carrera 1
	// Motor 2
	NEMA2.setEnablePin(ENABLE);
	NEMA2.setMaxSpeed(VMAX);				// Configurar velocidad máxima en pasos por segundo
	NEMA2.setAcceleration(ACEL);		// configurar aceleracion en pasos por segundo^2:
	pinMode(FINAL_CARRERA2, INPUT);	// Finales de carrera
}

void enviarComando(byte cmd, byte data){
	envio[0] = HEAD;
	envio[1] = cmd;
	envio[2] = data;
	envio[3] = TAIL;
	if (Serial.availableForWrite() >= LARGO_TRAMA){
		Serial.write(envio, LARGO_TRAMA);
		Serial.flush();	 
	}
}

int recibirRespuesta(){
	bool tramaValida = false;
	byte bytesDisp = Serial.available();
	byte buffer[bytesDisp];
	if ( bytesDisp ){
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
	if (tramaValida){
		if (recivo[1] == CMD_LEE)
			return recivo[2]
		ejecutarRespuesta(recibo);
	}
	else return -1;
}

void ejecutarRespuesta(byte trama[]){
	if (!codEmergencia){
		switch( trama[1] ){					// ejecutar comando

			case CMD_MO1:{						// lectura sensor/celda de carga
				
				vel1 = 101 - trama[2];			// analog1: velocidad nema17.1.
				if (abs(vel1) < 10){
					vel1 = 0;																	// forzar a velocidad cero en la cercania 
					NEMA1.disableOutputs(); 
				}
				NEMA1.enableOutputs();
				NEMA1.setSpeed(vel1);
				NEMA1.runSpeed();
				break;
			}
			
			case CMD_MO2:{						// Mover paso a paso de efector
				{
				vel2 = 101 - trama[2];			// analog2: velocidad nema17.2.
				if (abs(vel2) < 10){
					vel2 = 0;																	// forzar a velocidad cero en la cercania
					NEMA2.disableOutputs();
				}
				NEMA2.enableOutputs();
				NEMA2.setSpeed(vel2);
				NEMA2.runSpeed();
				}
				break;
			}
			
			default:									// Comando Inva'lido
				break;
		}
	}
}