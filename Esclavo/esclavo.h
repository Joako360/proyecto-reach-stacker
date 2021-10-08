#ifndef ESCLAVO_H_
#define ESCLAVO_H_
  // Comunicacion

  #define HEAD 0x02  // ASCII STX Comienza transmision
  #define TAIL 0x03 // ASCII ETX Finaliza transmision
  
  // Comandos soportados
  #define CMD_LEE 0x11  // Leer sensor/celda de carga
  #define CMD_ROT 0x12  // Rotar servomotor un angulo
  #define CMD_MOV 0x13  // Apertura/cierre de efector
  
  // Formato de Trama: <HEAD> <CMD> <DATA> <TAIL>
  // Si es enviado por el maestro, el esclavo debe ejecuar <CMD>, posiblemente con un valor <DATA>
  // Si es enviado por el esclavo, el maestro podria recibir <DATA> como resultado de ejecutar <CMD>
  
  #define PINSERVO 2       // pin 2 conectado a señal del servo
  #define PULSOMIN 1000    // pulso minimo en microsegundos
  #define PULSOMAX 2000    // pulso maximo en microsegundos

  #include <Arduino.h>
  #include <SoftwareSerial.h>
  #include <Servo.h>      // incluye libreria de Servo

  SoftwareSerial RS485(8, 9);    // RX, TX
  extern Servo servo1;           // crea objeto
  extern byte trama[4], idx;
  void enviarRespuesta( float x );
  void ejecutarComando();
  
#endif // ESCLAVO_H_
