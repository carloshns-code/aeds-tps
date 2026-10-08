#include <math.h>    //utilizacao da funcao sqrt()
#include "coordenada.h"  //ensina a TAD Coordenada para esse arquivo.c

// inicializa uma coordenada e retorna a coordenada inicializada
Coordenada c_init(float x, float y){
    Coordenada c;   //recebeu valores de x e y e fez com que o programa os vissem como um par de coordenadas

    c.x = x;
    c.y = y;

    return c;
}


//Calculo da distancia entre dois pontos
float c_distancia(Coordenada c1, Coordenada c2){
    float dx = c1.x - c2.x;
    float dy = c1.y - c2.y;

    return sqrt(dx*dx + dy*dy);
}

//envia a coordenada x
float c_get_localizacao_x(Coordenada c){
    return c.x;
}

float c_get_localizacao_y(Coordenada c){
    return c.y;
}