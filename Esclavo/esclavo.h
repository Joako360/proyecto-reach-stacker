#ifndef ESCLAVO_H_
#define ESCLAVO_H_

	// Comunicacion
	#define HEAD 0xAA  // ASCII STX Comienza transmision
	#define TAIL 0x55 // ASCII ETX Finaliza transmision
	#define LARGO_TRAMA 4 // tamaño de trama en bytes

	// Comandos soportados
	#define CMD_LEE 0x11  // Leer sensor/celda de carga
	#define CMD_ROT 0x12  // Rotar servomotor un angulo
	#define CMD_MOV 0x13  // Apertura/cierre de efector
	#define CMD_MO1 0x14  // Motor NEMA17 1
	#define CMD_MO2 0x15  // Motor NEMA17 2


	// Formato de Trama: <HEAD> <CMD> <DATA> <TAIL>
	// Si es enviado por el maestro, el esclavo debe ejecuar <CMD>, posiblemente con un valor <DATA>
	// Si es enviado por el esclavo, el maestro podria recibir <DATA> como resultado de ejecutar <CMD>

	//Servo
	#define PINSERVO 9       // pin 9 conectado a señal del servo
	#define PULSOMIN 500    // pulso minimo en microsegundos
	#define PULSOMAX 2500    // pulso maximo en microsegundos

	//28BYJ-48
	#define IN1 A8      // pin digital 4 de Arduino a IN1 de modulo ULN2003
	#define IN2 A9      // pin digital 5 de Arduino a IN2 de modulo ULN2003
	#define IN3 A10     // pin digital 6 de Arduino a IN3 de modulo ULN2003
	#define IN4 A11     // pin digital 7 de Arduino a IN4 de modulo ULN2003
	#define TIPO_INTR 4  //Definir el tipo de interfaz 
	#define VMAX 1000 // Velocidad maxima pasos por segundo
	#define ACEL 200  // Aceleracion en pasos por segundo al cuadrado

	#include <Arduino.h>
	#include <Servo.h>      // incluye libreria de Servo
	#include <AccelStepper.h>  // Incluir libreria AccelStepper
	extern Servo servo1;           // crea objeto
	extern AccelStepper BYJ;
	extern byte envio[LARGO_TRAMA], recibo[LARGO_TRAMA], lecByte, idx;
	extern int vel;
	void setupMotores();
	void enviarRespuesta(byte cmd, byte x);
	void ejecutarComando(byte trama[]);
	void recibirComando();

#endif // ESCLAVO_H_
