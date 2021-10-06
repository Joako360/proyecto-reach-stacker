#ifndef MAESTRO_H_
#define MAESTRO_H_
  
  // Comunicacion
  #define HEAD 0x02   // ASCII STX Comienza transmision
  #define TAIL 0x03   // ASCII ETX Finaliza transmision
  
  // Comandos soportados
  #define CMD_LEE 0x11  // ASCII DC1 Leer sensor/celda de carga
  #define CMD_ROT 0x12  // ASCII DC2 Rotar servomotor un angulo
  #define CMD_MOV 0x13  // ASCII DC3 Apertura/cierre de efector
  
  // Formato de Trama: <HEAD> <CMD> <DATA> <TAIL>
  // Si es enviado por el maestro, el esclavo debe ejecuar <CMD>, posiblemente con un valor <DATA>
  // Si es enviado por el esclavo, el maestro recive <DATA> como resultado de ejecutar CMD_LEE
  
  byte trama[4], idx;
  void enviarComando(byte cmd, byte data);
  int recibirRespuesta();

#endif // MAESTRO_H_
