#ifndef LISTAGEN_H
#define LISTAGEN_H

#include <stdio.h>
#include <stdlib.h>
#include "PCB.h"

typedef struct lista Lista;

Lista* cria_lista(void);
void destroi_lista(Lista*);
void dump_lista(const Lista*);
bool underflow_lista(const Lista*);
void ins_fim_lista(Lista*, const PCB*);
void rem_processo_lista(Lista*, PCB*);

#endif