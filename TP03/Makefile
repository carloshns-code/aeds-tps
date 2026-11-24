# Linux: make ; Windows (MinGW/MSYS2 com GCC e make): make
# No MinGW que oferece mingw32-make, use mingw32-make.
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
OBJ = main.o pokemon.o pokelista.o centroDePesquisa.o controleDaMissao.o
ifeq ($(OS),Windows_NT)
    ALVO = tp3.exe
else
    ALVO = tp3
endif

all: $(ALVO)

$(ALVO): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(ALVO)

main.o: main.c controleDaMissao.h centroDePesquisa.h pokelista.h pokemon.h utils.h
pokemon.o: pokemon.c pokemon.h utils.h
pokelista.o: pokelista.c pokelista.h pokemon.h utils.h
centroDePesquisa.o: centroDePesquisa.c centroDePesquisa.h pokelista.h pokemon.h utils.h
controleDaMissao.o: controleDaMissao.c controleDaMissao.h centroDePesquisa.h pokelista.h pokemon.h utils.h

.PHONY: all
