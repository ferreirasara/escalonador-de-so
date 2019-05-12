#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "listagen.h"

struct nodo {
	PCB processo;
	struct nodo* proximo;
	struct nodo* anterior;
};
typedef struct nodo Nodo;

struct lista {
	Nodo* cabeca;
	Nodo* cauda;
	size_t num_nodos;
};
Lista* cria_lista(void) {
	Lista* l = malloc(sizeof(Lista));
	
	l->cauda = NULL;
	l->cabeca = NULL;
	l->num_nodos = 0;
	return l;
}
void destroi_lista(Lista* l) {
	while(!underflow_lista(l)) {
		PCB dummy;
		// rem_fim_lista(l, &dummy);
	}
	free(l);
}

bool underflow_lista(const Lista* l) {
	return l->cabeca == NULL;
}

void dump_lista(const Lista* l) {
	if (underflow_lista(l)) {
		printf("Nenhum Processo\n");
		return;
	}
	int contador = 1;
	printf(" N° Processo | PID | Hora Inicio | Hora Fim | Tempo Restante\n");
	Nodo* i = l->cabeca;
	do {
		printf("      %d      |", contador);
		printf(" %3d |", i->processo.PID);
		printf("  %02d:%02d:%02d   |", i->processo.hr_entrada, i->processo.min_entrada, i->processo.sec_entrada);
		printf(" %02d:%02d:%02d |", i->processo.hr_saida, i->processo.min_saida, i->processo.sec_saida);
		printf("%9ds\n", i->processo.tempo_total);
		i = i->proximo;
		++contador;
	} while (i != NULL);
}

void ins_inicio_lista(Lista* l, const PCB* p) {
    Nodo* n = malloc(sizeof(Nodo));
    memcpy(&n->processo, p, sizeof(PCB));
   	n->proximo = l->cabeca;
   	l->cabeca = n;
   	n->anterior = NULL;
   	++l->num_nodos;
	if (n->proximo != NULL) {
		n->proximo->anterior = n;
	} else {
		l->cauda = n;
	}	
}

void ins_fim_lista(Lista* l, const PCB* p) {
    if (underflow_lista(l)) {
        ins_inicio_lista(l, p);
        return;
    }
    Nodo* n = malloc(sizeof(Nodo));
    memcpy(&n->processo, p, sizeof(PCB));
    n->proximo = NULL;
    n->anterior = l->cauda;
    n->anterior->proximo = n;
    ++l->num_nodos;
}

PCB* rem_processo_lista(Lista* l, PCB* p) {
	Nodo* i = l->cabeca;
	while (i != NULL) {
		if (memcmp(&i->processo, p, sizeof(PCB))) {
			if (i->anterior != NULL) {
				i->anterior->proximo = i->proximo;
			} else {
				l->cabeca = i->proximo;
			}
			if (i->proximo != NULL) {
				i->proximo->anterior = i->anterior;
			} else {
				l->cauda = i->anterior;
			}
			Nodo* x = i;
			return &i->processo;
			i = i->proximo;
			free(x);
			--l->num_nodos;
		} else {
			i = i->proximo;
		}
	}
}

bool fimES(Lista* l, PCB* p) {
	PCB* retorno;
	Nodo* i = l->cabeca;
	while (i != NULL) {
		if(geraFimSolicitacaoES()) {
			retorno = rem_processo_lista(l, &i->processo);
			memcpy(p, retorno, sizeof(PCB));
			return true;
		} else {
			i = i->proximo;
		}
	}
	return false;
}

int tamanho_lista(const Lista* l) {
	return l->num_nodos;
}

bool geraFimSolicitacaoES() {
	srand((unsigned) time(NULL));
	int flag_fim_ES = rand() % 50;
	return flag_fim_ES == 1 ? true : false;
}