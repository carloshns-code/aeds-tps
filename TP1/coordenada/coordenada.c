#include <stddef.h> //biblioteca que inclui definicoes padrao essenciais em C, como NULL E size_t ()
                    //size_t quantidade_elementos = sizeof(valores) / sizeof(valores[0]
#include "coordenada.h"

float c_ditancia(Coordenada c1, Coordenada c2)
{                           // recebe apenas uma copia, ja que os valores nao serao alterados. c1 e c2 sao duas structs
    float dx = c1.x - c2.x; // para acessar a copia do ponteiro uso o .
    float dy = c1.y - c2.y;
    return sqrtf(dx * dx + dy * dy); // calculo da distancia euclidiana
}

void c_init(Coordenada *c, float x, float y)
{ // aqui chega float, nao int
    if (c == NULL)
    {           // analisa seo ponteiro eh null, ou seja, que nao aponta para lugar nenhum.
        return; // se operar com ponteiro null causa erro grave e encerra o programa (crach)
    }
    c->x = x; // aqui ocorre a atualizacao das coordendas. Outra fofma: (*c).x = x
    c->y = y; // para derreferenciar o ponteiro, uso ->
}