#ifndef COORDENADA_H
#define COORDENADA_H

#include <math.h>

#define ORIGEM 0

typedef struct {
  float x;
  float y;
} Coordenada;

float c_distancia(Coordenada c1, Coordenada c2);

void c_init(Coordenada *c, int x, int y);

#endif