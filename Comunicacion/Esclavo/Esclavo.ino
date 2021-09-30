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

void setup() {
  // Configurar Serial a 19200 baudios (para el monitor serie)
  Serial.begin(19200);

  // Configurar para utilizar el bus 485 a 9600
  RS485.begin(9600);

  // configrar pines
  pinMode( LED_BUILTIN, OUTPUT );

  digitalWrite( LED_BUILTIN, LOW );   // apagar led
  
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
  else if ( idx > 0 && idx < 4 ){ // 
    buff[idx++] = incoming;      //
     
    if ( idx == 4 ){                // fin de trama
      if( buff[3] == TAIL )         // verificar que termine bien
        ejecutarComando();
      idx = 0;
    }
  }
}
