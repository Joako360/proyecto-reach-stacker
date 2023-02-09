/*
 * RS-485 con MAX485 y Arduino
 *
 * Comunicacion: Full-duplex
 * Roll: Master
 * Placa: Arduino UNO
 * Comandos: 0x11 - Leer sensor/celda de carga (solo lectura)
 *           0x12 - Rotar servomotor un angulo (escritura)
 *           0x13 - Apertura/cierre de efector (escritura)
 */

#include "maestro.h"
#include "parar_emergencia.h"
#include "lcd.h"
int r = -1;
byte velSlv;
char pesoStr[4], plimStr[4], yStr[4], xStr[4];
float peso, plim, xpos, ypos;

void setup() {
	// Configurar Serial para el bus RS-485
	Serial.begin(19200);
	setupInterrup();
	setupMotores();
	setupLCD();
	plim = PMAX;

}

void loop() {
	r = recibirRespuesta();// ya tiene if(Serial.available);
	if (r != -1){
		peso = (r / 255.0 *10.0) -5.0;
		dtostrf(peso, 4,2,pesoStr);	//convertir la variable flotante peso en cadena para el lcd
		codEmergencia = peso >= plim ? 2 : 0;// codigo 2: peso excedido del limite
	}

	xpos = NEMA1.currentPosition() / 25.0;//mm
	dtostrf(xpos, 4, 2, xStr);
	ypos = NEMA2.currentPosition() / 25.0;//mm
	dtostrf(ypos, 4, 2, yStr);
	plim = PMAX - xpos * 0.1 - ypos *0.1;
	dtostrf(plim, 4, 2, plimStr);
	//---enviamos el ángulo para mover el servo------
	enviarComando(CMD_ROT, ang);
	//---solicitamos una lectura del sensor----------
	enviarComando(CMD_MOV, velSlv);
	enviarComando(CMD_LEE, 0x00);
	sprintf(line0, "P:%sl:%s", pesoStr, plimStr);
	sprintf(line1, "x:%sy:%s", xStr, yStr);
	updateLCD();
}