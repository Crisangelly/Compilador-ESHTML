#ifndef ERRORES_H
#define ERRORES_H

struct error_estructura{
    int linea;
    char mensaje[256];
    int tipo; // 0: léxico, 1: sintáctico, 2: semántico
    char token[100];
};

extern struct error_estructura errores[10];
extern int num_errores;

void agregar_error(int linea, char *mensaje, int tipo, char *token);

#endif