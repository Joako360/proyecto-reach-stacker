// Comunicacion

#define HEAD 0x02 // STX COmienza transmision
#define TAIL 0x03 // ETX FInaliza transmision

// Comandos soportados
#define CMD_A 0xAA
#define CMD_B 0xBB
#define CMD_C 0xCC
#define CMD_D 0xDD
#define CMD_E 0xEE
#define CMD_F 0xFF

// Formato de Trama Maestro: <HEAD>  <CMD> <TAIL>
// Formato de Trama Esclavo: <HEAD> <DATA> <TAIL>
// Ejemplo: 0x02 0xCC 0x03 Indica que el esclavo debe ejecutar la orden C
