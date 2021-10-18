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
 
  //Servo
  #define PINSERVO 9       // pin 9 conectado a señal del servo
  #define PULSOMIN 1000    // pulso minimo en microsegundos
  #define PULSOMAX 2000    // pulso maximo en microsegundos

  //28BYJ-48
  #define IN1 4      // pin digital 4 de Arduino a IN1 de modulo ULN2003
  #define IN2 5      // pin digital 5 de Arduino a IN2 de modulo ULN2003
  #define IN3 6     // pin digital 6 de Arduino a IN3 de modulo ULN2003
  #define IN4 7     // pin digital 7 de Arduino a IN4 de modulo ULN2003
  #define TIPO_INTR 4  //Definir el tipo de interfaz 
  
  #include <Arduino.h>
//  #include <SoftwareSerial.h>
  #include <Servo.h>      // incluye libreria de Servo
  #include <AccelStepper.h>  // Incluir libreria AccelStepper

  extern Servo servo1;           // crea objeto
  extern AccelStepper BYJ;
  extern byte trama[4], idx, lec;
  extern int vel;
  void enviarRespuesta( float x );
  void ejecutarComando();
  
#endif // ESCLAVO_H_
