/**
 * Ejemplo RS-485 con MAX485 y Arduino
 * 
 * Comunicacion: Half-duplex
 * Roll: Master
 * Placa: Arduino MEGA 2560
 */
#include <SoftwareSerial.h>

#define HEAD 0xAA
#define TAIL 0xFE

// Comandos soportados
#define CMD_LED_ON      0x01
#define CMD_LED_OFF     0x02
#define CMD_READ_TEMP   0x03
#define CMD_READ_HUMED  0x04

// Formato de Trama: &lt;HEAD&gt; &lt;SLAVE_ID&gt; &lt;CMD&gt; &lt;TAIL&gt;
// Ejemplo: 0xFF 0x34 0x01 0xFE -&gt; Indica que el esclavo 0x34 debe ejecutar la orden 0x01

#define RS485_PIN_MODE 25         // HIGH -&gt; Transmision; LOW-&gt; recepcion
#define SLAVE 0x23
byte trama[5], idx;


void enviarComando(byte esclavo, byte cmd){
  trama[0] = HEAD;
  trama[1] = esclavo;
  trama[2] = cmd;
  trama[3] = TAIL;
  digitalWrite(RS485_PIN_MODE, HIGH); // modo tx
  Serial3.write(trama, 4);
  Serial3.flush();  
  digitalWrite(RS485_PIN_MODE, LOW); // modo rx
}


int recibirRespuesta( byte esclavo ){
  digitalWrite(RS485_PIN_MODE, LOW); // modo rx
  delay(2000);
  Serial3.readBytes( trama, 4 );

  if( trama[0] != HEAD )    // error en la trama
    return -1;
    
  if( trama[1] != esclavo ) // respuesta de otro esclavo
    return -1;

  if( trama[3] != TAIL )    // error en trama
    return -1;

  return trama[2];
  
}


void setup() {
  // Configurar Serial para utilizarlo como monitor
  Serial.begin(19200);

  pinMode( RS485_PIN_MODE, OUTPUT );
  digitalWrite(RS485_PIN_MODE, LOW); // modo recepcion
  // Configurar Serial3 para el bus RS-485
  Serial3.begin(9600);
}


void loop() {
  
  if( Serial.available() ){
    char c = Serial.read();
    int h, t;
    switch(c){
      case '0':
        enviarComando(SLAVE, CMD_LED_ON);
        break;
        
      case '1':
        enviarComando(SLAVE, CMD_LED_OFF);
        break;

      case '2':
        enviarComando(SLAVE, CMD_READ_TEMP);
        Serial.print("Temperatura: ");
        t = recibirRespuesta(SLAVE);
        if( t == -1 )
          Serial.println( "No se recibio' respuesta" );
        else
          Serial.println(t);
        break;

      case '3':
        enviarComando(SLAVE, CMD_READ_HUMED);
        Serial.print("Humedad: ");
        h = recibirRespuesta(SLAVE);
        if( h == -1 )
          Serial.println( "No se recibio' respuesta" );
        else
          Serial.println(h);
        break;

      default:
        break;
    }
 
  }
}
