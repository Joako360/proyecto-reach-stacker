#ifndef MAESTRO_H_
#define MAESTRO_H_

	#define PMAX 4.5
	// Comunicacion
	#define HEAD 0xAA   // ASCII STX Comienza transmision
	#define TAIL 0x55   // ASCII ETX Finaliza transmision
	#define LARGO_TRAMA 4 // tamaño de trama en bytes

	// Comandos soportados
	#define CMD_LEE 0x11  // ASCII DC1 Leer sensor/celda de carga
	#define CMD_ROT 0x12  // ASCII DC2 Rotar servomotor un angulo
	#define CMD_MOV 0x13  // ASCII DC3 Apertura/cierre de efector
	#define CMD_MO1 0x14  // Mover NEMA17 1
	#define CMD_MO2 0x15  // Mover NEMA17 2

	// Formato de Trama: <HEAD> <CMD> <DATA> <TAIL>
	// Si es enviado por el maestro, el esclavo debe ejecuar <CMD>, posiblemente con un valor <DATA>
	// Si es enviado por el esclavo, el maestro recive <DATA> como resultado de ejecutar CMD_LEE
    
  //CNC Shield / 42HS08
  #define ENABLE 8
  #define VMAX 100
  #define ACEL 50
  //NEMA17.x
  #define DIR1 5   // pin 5 direccion X
  #define STEP1 2  // pin 2 Paso x
  #define TIPO_INTR1 1  // interfaz tipo driver
  #define FINAL_CARRERA1 9 // Final de carrera x
  //NEMA17.y
  #define DIR2 6   // pin 6 direccion y
  #define STEP2 3  // pin 3 paso Y
  #define TIPO_INTR2 1 // interfaz tipo driver
  #define FINAL_CARRERA2 10 // Final de carrera y

  #include <Arduino.h>
  #include <AccelStepper.h>

  extern AccelStepper NEMA1;
  extern AccelStepper NEMA2;
  extern byte envio[LARGO_TRAMA], recibo[LARGO_TRAMA];
  extern int vel1, vel2;
  void finalCarrera(AccelStepper motor);
  void setupMotores();
  void enviarComando(byte cmd, byte data);
  int recibirRespuesta();
	void ejecutarRespuesta(byte trama[]);
  //void alarma(float peso);

#endif // MAESTRO_H_
