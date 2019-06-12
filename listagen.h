/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Código feito por Sara Cristina Ferreira		 *
 *		Disciplina: Estrutura de Dados e Algoritmos	 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef LISTAGEN_H
#define LISTAGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PCB.h"

typedef struct lista Lista;

Lista* criaLista(void);
bool fimES(Lista*, PCB*);
bool geraFimSolicitacaoES();
bool underflowLista(const Lista*);
int tamanhoLista(const Lista*);
void destroiLista(Lista*);
void dumpLista(const Lista*);
void insFimLista(Lista*, const PCB*);
void insInicioLista(Lista*, const PCB*);
void remInicioLista(Lista*, PCB*);
void remProcessoLista(Lista*, PCB*, PCB*);

#endif