/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Código feito por Sara Cristina Ferreira		 *
 *		Disciplina: Estrutura de Dados e Algoritmos	 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef FILAGEN_H
#define FILAGEN_H

#include <stdio.h>
#include <stdlib.h>
#include "PCB.h"

typedef struct fila Fila;

Fila* criaFila(void);
bool underflowFila(const Fila*);
int tamanhoFila(const Fila*);
void destroiFila(Fila*);
void dumpFila(const Fila*);
void dumpFilaFinalizado(const Fila*);
void insFimFila(Fila*, const PCB*);
void insInicioFila(Fila*, const PCB*);
void remInicioFila(Fila*, PCB*);


#endif