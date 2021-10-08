#ifndef BYJ_H
#define BYJ_H
#define IN1 8      // pin digital 8 de Arduino a IN1 de modulo controlador
#define IN2 9      // pin digital 9 de Arduino a IN2 de modulo controlador
#define IN3 10     // pin digital 10 de Arduino a IN3 de modulo controlador
#define IN4 11     // pin digital 11 de Arduino a IN4 de modulo controlador
#define DEMORA 15      // demora entre pasos, no debe ser menor a 10 ms.
// paso completo simple

void secuencia(int demora);
void secuencia_inv(int demora);
void detener();
#endif // BYJ_h
