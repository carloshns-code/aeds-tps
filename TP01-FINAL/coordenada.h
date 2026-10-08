#ifndef COORDENADA_H
#define COORDENADA_H

typedef struct {
    float x;
    float y;
} Coordenada;


/// PROTOTIPOS DAS FUNCOES ENVOLVIDAS NOS CALCULOS DAS COORDENADAS
//permite que outros arquivos conhecam a assinatura de funcoes sem saber como funcionam


//funcao que inicializa a coordenada
Coordenada c_init (float x, float y);

//calculo da distancia
float c_distancia(Coordenada c1, Coordenada c2);

// getters
float c_get_localizacao_x(Coordenada c);
float c_get_localizacao_y(Coordenada c);

#endif