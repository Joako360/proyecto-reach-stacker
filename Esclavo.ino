/**
 * Ejemplo RS-485 con MAX485 y Arduino
 * 
 * Comunicacion: Half-duplex
 * Roll: Slave
 * Placa: Arduino UNO R3
 * Comandos: 0x01 - Encender led
 *           0x02 - Apagar led 
 *           0x03 - leer temperatura
 *           0x04 - leer humedad
 */
#include <SoftwareSerial.h>
#include <DHT.h>

// Trama maestro-esclavo
#define HEAD 0xAA
#define MY_SLAVE_ID 0x23
#define TAIL 0xFE

//Comandos soportados
#define CMD_LED_ON      0x01
#define CMD_LED_OFF     0x02
#define CMD_READ_TEMP   0x03
#define CMD_READ_HUMED  0x04

// Formato de Trama: &lt;HEAD&gt; &lt;SLAVE_ID&gt; &lt;CMD&gt; &lt;TAIL&gt;
// Ejemplo: 0xFF 0x34 0x01 0xFE -&gt; Indica que el esclavo 0x34 debe ejecutar la orden 0x01

#define DHT_GND 2 // tierra dht11
#define DHT_VCC 4 // alimentacion dht11
#define DHT_PIN 3 // comunicacion dht11

#define RS485_PIN_MODE 9         // HIGH -&gt; Transmision; LOW-&gt; recepcion

SoftwareSerial RS485(10, 8);    // RX, TX

DHT dht(DHT_PIN, DHT11);

byte buff[5], idx;
float temperatura, humedad;

void enviarRespuesta( float x ){
  buff[0] = HEAD;
  buff[1] = MY_SLAVE_ID;
  buff[2] = (byte)x;
  buff[3] = TAIL;
  digitalWrite( RS485_PIN_MODE, HIGH ); // poner en modo Tx
  RS485.write( buff, 4 );               // transmitir mensaje
  RS485.flush();
  digitalWrite( RS485_PIN_MODE, LOW);   // poner en modo Rx
  
}

void ejecutarComando(){
  Serial.println("Ejectutando comando!!!");
  if ( buff[1] != MY_SLAVE_ID ) // el mensaje es para otro esclavo
    return;

  switch( buff[2] ){                      // ejecutar comando

    case CMD_LED_ON:                      // Encender Led
      digitalWrite( LED_BUILTIN, HIGH );  
      break;

    case CMD_LED_OFF:                     // Apagar Led
      digitalWrite( LED_BUILTIN, LOW );
      break;
    
    case CMD_READ_TEMP:
      temperatura = dht.readTemperature(); // grados Celcius
      enviarRespuesta( temperatura );
      break;

    case CMD_READ_HUMED:
      humedad = dht.readHumidity();
      enviarRespuesta( humedad );
      break;

      
    default:                              // Comando Inva'lido
      break;
  }
}


void setup() {
  // Configurar Serial a 19200 baudios (para el monitor serie)
  Serial.begin(19200);

  // Configurar para utilizar el bus 485 a 9600
  RS485.begin(9600);

  // configrar pines
  pinMode( LED_BUILTIN, OUTPUT );
  pinMode( RS485_PIN_MODE, OUTPUT );
  pinMode( DHT_VCC, OUTPUT );
  pinMode( DHT_GND, OUTPUT );

  // encender dht11
  digitalWrite( DHT_VCC, HIGH );
  digitalWrite( DHT_GND, LOW );

  digitalWrite( LED_BUILTIN, LOW );   // apagar led
  
  digitalWrite( RS485_PIN_MODE, LOW );// poner en modo de recepcion

  dht.begin();
  idx = 0;

}


void loop() {

  if( !RS485.available() )
    return;

  byte incoming = RS485.read();
  Serial.print("Recibido: ");
  Serial.println(incoming);
    
  if( idx == 0 ){           // principio de trama
    if( incoming != HEAD ) // trama incorrecta
      return;

    buff[idx] = incoming;
    idx++;
  }
  else if ( idx &gt; 0 &amp;&amp; idx &lt; 4 ){ // 
    buff[idx++] = incoming;      //
     
    if ( idx == 4 ){                // fin de trama
      if( buff[3] == TAIL )         // verificar que termine bien
        ejecutarComando();
      idx = 0;
    }
  }
}
