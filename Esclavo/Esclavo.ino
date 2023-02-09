/*
 * RS-485 con MAX485 y Arduino
 * 
 * Comunicacion: Full-dup
 * Rol: Slave
 * Placa: Arduino MEGA 2560
 * Comandos: 0x11 - Leer sensor/celda de carga (solo lectura)
 *           0x12 - Rotar servomotor un angulo (escritura)
 *           0x13 - Apertura/cierre de efector (escritura)
 */

#include "esclavo.h"
#include "timer_balanza.h"
int js[3], vel1, vel2  // Joystick de 4GL
byte ang,

void setup() {
	// Configurar Serial a 19200 baudios para utilizar el bus 485
	Serial.begin(19200);
	setupMotores();
	setupTimer();	//ya inicia la celda de carga
	idx = 0;// Indice explorador de trama entrante
}

void loop() {
	for(byte i = 0; i < 3; i++){
		js[i] = analogRead(i);
	}
	ang = round(js[0] / 1023.0 * 180.0);  // analog0: escalamos la lectura a un valor de ángulo (entre 0 y 180)
	if(ang<=180)          //verificamos que sea un valor en el rango del servo
		servo1.write(ang);  //movemos el servomotor al ángulo correspondiente.

	vel1 = map(js[1], 0, 1023, 0, 201);      // analog1: velocidad nema17.1.
	vel2 = map(js[2], 0, 1023, 0, 201);      // analog2: velocidad nema17.2.
	//---enviamos velocidad de motor 1------
	enviarComando(CMD_MO1, vel1);
	//---enviamos velocidad de motor 2----------
	enviarComando(CMD_MO2, vel2);
	recibirComando();
}
