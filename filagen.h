#ifndef FILAGEN_H
#define FILAGEN_H

#include <stdio.h>
#include <stdlib.h>
#include "PCB.h"

typedef struct fila Fila;

Fila* cria_fila(void);
void destroi_fila(Fila*);
bool underflow_fila(const Fila*);
void dump_fila(const Fila*);
void ins_fim_fila(Fila*, const PCB*);
void rem_inicio_fila(Fila*, PCB*);
int tamanho_fila(const Fila*);

#endif