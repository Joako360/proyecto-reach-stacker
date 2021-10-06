#ifndef BYJ_H
#define BYJ_H
int IN1 = 8;      // pin digital 8 de Arduino a IN1 de modulo controlador
int IN2 = 9;      // pin digital 9 de Arduino a IN2 de modulo controlador
int IN3 = 10;     // pin digital 10 de Arduino a IN3 de modulo controlador
int IN4 = 11;     // pin digital 11 de Arduino a IN4 de modulo controlador
int demora = 15;      // demora entre pasos, no debe ser menor a 10 ms.
// paso completo simple
int paso [4][4] =   // matriz (array bidimensional) con la secuencia de pasos
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};
void secuencia(demora)
void secuencia_inv(demora)
void detener()
#endif // BYJ_h
