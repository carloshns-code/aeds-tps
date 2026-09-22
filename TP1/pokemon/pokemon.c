#include "pokemon.h"

void p_init(Pokemon *p, int id, int numPokedex, char nome[], char tipo[], Coordenada localizacao){
    if (p==NULL){
        return;
    }

    p_set_id(p, id);
    p_set_numPokedex(p, numPokedex);
    p_set_nome(p, nome);
    p_set_tipo(p, tipo);
    p_set_localizacao(p,localizacao);
}

void p_imprime(Pokemon *p){
    if (p==NULL){
        return;
    }

    printf("ID: %d \n Pokedex: %d \n Nome: %s \n Tipo: %s \n Localizacao: (%.2f, %.2f) \n", 
        p->id, p->numPokedex, p->nome, p->tipo, p->localizacao.x, p->localizacao.y);
}

int p_get_id(Pokemon *p){
    if (p!=NULL){
        return p->id;
    } else {
        return -1;       //aqui escolhi -1 pq esse número nao pode ser nunca um ID. Isso eh para sinalizar que p=NULL.
    }
}

int p_get_numPokedex(Pokemon *p){
    if (p!=NULL){
        return p->numPokedex;
    } else {
        return -1;       //aqui escolhi -1 pq esse número nao pode ser nunca um ID. Isso eh para sinalizar que p=NULL.
    }
}

char* p_get_nome(Pokemon *p){
    if (p!=NULL){
        return p->nome;
    } else {
        return "NOME-NULL";       //aqui escolhi -1 pq esse número nao pode ser nunca um ID. Isso eh para sinalizar que p=NULL.
    }
}

char* p_get_tipo(Pokemon *p){
    if (p!=NULL){
        return p->tipo;
    } else {
        return "TIPO-NULL";       //aqui escolhi -1 pq esse número nao pode ser nunca um ID. Isso eh para sinalizar que p=NULL.
    }
}

Coordenada p_get_localizacao(Pokemon *p){
    Coordenada origem;
    c_init(&origem, ORIGEM, ORIGEM);   //colocando o objeto na origem ()
    
    if (p!=NULL){                       //se p ja tiver fido inicializado, ele tem uma localizacao real
        return p->localizacao;
    }else{
        return origem;     //do contrario, o objeto esta na origem
    }

}

float p_get_localizacao_x(Pokemon *p){
    if (p != NULL){
        return p->localizacao.x;
    }
    else{return ORIGEM;}
}

float p_get_localizacao_y(Pokemon *p){
    if (p != NULL){
        return p->localizacao.y;
    }
    else{return ORIGEM;}
}

void p_set_id(Pokemon *p, int id){
    if (p!=NULL){
        p->id = id;
    }
}

void p_set_numPokedex(Pokemon *p, int numPokedex){
    if(p!=NULL){
        p->numPokedex=numPokedex;
    }
}

void p_set_nome(Pokemon *p, char nome[]){     //char nome [] eh o mesmo que "char *nome"
    if (p==NULL || nome==NULL){
        return;
    }
    strncpy(p->nome, nome, MAX_TAM_STRING - 1);
    p->nome[MAX_TAM_STRING - 1] = '\0';         //aqui preciso garantir que o ultimo caracter do vetor de string contenha o terminador 
}                                               //justamente para um caso em que o novo nome exceda o tamanho maximo da string, tipo 60 caracteres


void p_set_tipo(Pokemon *p, char tipo[]){
    if (p==NULL || tipo==NULL){
        return;
    }
    strncpy(p->tipo, tipo, MAX_TAM_STRING - 1);
    p->tipo[MAX_TAM_STRING - 1] = '\0';
}

void p_set_localizacao(Pokemon *p, Coordenada l){
    if (p!=NULL){
        p->localizacao = l;
    }
}