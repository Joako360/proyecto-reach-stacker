#include <SoftwareSerial.h>;
#include"global.h"

SoftwareSerial RS485(0, 1);    // RX, TX

byte buff[3], idx;
float temperatura, humedad;

void enviarRespuesta( float x ){
  buff[0] = HEAD;
  buff[1] = (byte)x;
  buff[2] = TAIL;
  RS485.write( buff, 3 );               // transmitir mensaje
  RS485.flush();
}

void ejecutarComando(){
  Serial.println("Ejectutando comando!!!");
  if ( buff[1] != MY_SLAVE_ID ) // el mensaje es para otro esclavo
    return;

  switch( buff[2] ){                      // ejecutar comando

    case CMD_A:                      // Encender Led
      digitalWrite( LED_BUILTIN, HIGH );  
      break;

    case CMD_B:                     // Apagar Led
      digitalWrite( LED_BUILTIN, LOW );
      break;
      
    default:                              // Comando Inva'lido
      break;
  }
}
