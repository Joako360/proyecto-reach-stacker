#ifndef MAESTRO_H_
#define MAESTRO_H_
  
  // Comunicacion
  #define HEAD 0x02   // ASCII STX Comienza transmision
  #define TAIL 0x03   // ASCII ETX Finaliza transmision
  #define LARO_TRAMA 4 // tamaño de trama en bytes
  
  // Comandos soportados
  #define CMD_LEE 0x11  // ASCII DC1 Leer sensor/celda de carga
  #define CMD_ROT 0x12  // ASCII DC2 Rotar servomotor un angulo
  #define CMD_MOV 0x13  // ASCII DC3 Apertura/cierre de efector
  
  // Formato de Trama: <HEAD> <CMD> <DATA> <TAIL>
  // Si es enviado por el maestro, el esclavo debe ejecuar <CMD>, posiblemente con un valor <DATA>
  // Si es enviado por el esclavo, el maestro recive <DATA> como resultado de ejecutar CMD_LEE
  //NEMA17
  #define DIR 2   // pin 2 como salida
  #define STEP 3  // pin 5 como salida
  #define TIPO_INTR 1
  #define VMAX 1000 // Velocidad maxima pasos por segundo
  #define ACEL 20 // Aceleracion pasos por segundo cuadrado

  #include <Arduino.h>
  #include <SoftwareSerial.h>
  #include <AccelStepper.h>
  
  #define DIR 2   // pin 2 como salida
  #define STEP 3  // pin 5 como salida
  #define TIPO_INTR 1

  extern AccelStepper NEMA;
  extern byte trama[LARGO_TRAMA], idx;
  void setupMotores();
  void enviarComando(byte cmd, byte data);
  int recibirRespuesta();
  void alarma(float peso);

#endif // MAESTRO_H_
