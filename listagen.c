#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
	Lista* l;
	
	l->cauda = NULL;
	l->cabeca = NULL;
	l->num_nodos = 0;

	return l;
}
void destroi_lista(Lista* l) {
	while(!underflow_lista(l)) {
		PCB dummy;
		//rem_fim(l, &dummy);
	}
	free(l);
}

bool underflow_lista(const Lista* l) {
	return l->cabeca == NULL;
}

void dump_lista(const Lista* l) {
	if (underflow_lista(l)) {
		printf("NENHUM PROCESSO\n");
		return;
	}
	int contador = 1;
	printf("%-14s|%-14s\n", "  N PROCESSO", "    PID");
	Nodo* i;
	for (i = l->cabeca; i != NULL; i = i->proximo) {
		printf("%7d%7s|%7d\n", contador, "", i->processo.PID);
		++contador;
	}
}

void ins_fim_lista(Lista* l, const PCB* p) {
	Nodo* n = malloc(sizeof(Nodo));
	memcpy(&n->processo, p, sizeof(p));
	if (l->cabeca == NULL) {
		n->proximo = l->cabeca;
		l->cabeca = n;
		n->anterior = NULL;
		if (n->proximo != NULL) {
			n->proximo->anterior = n;
		} else {
			l->cauda = n;
		}
	} else {
		n->proximo = NULL;
		n->anterior = l->cauda;
		n->anterior->proximo = n;
	}
	++l->num_nodos;
}

void rem_processo_lista(Lista* l, PCB* p) {
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
			i = i->proximo;
			free(x);
			--l->num_nodos;
		} else {
			i = i->proximo;
		}
	}
}
