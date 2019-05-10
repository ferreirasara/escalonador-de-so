#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filagen.h"

struct nodo {
	PCB processo;
	struct nodo* proximo;
};
typedef struct nodo Nodo;

struct fila {
	Nodo* cauda;
	size_t num_nodos;
};

Fila* cria_fila(void) {
	Fila* f = malloc(sizeof(Fila));
	
	f->cauda = NULL;
	f->num_nodos = 0;

	return f;
}

void destroi_fila(Fila* f) {
	while(!underflow_fila(f)) {
		PCB dummy;
		rem_inicio_fila(f, &dummy);
	}
	free(f);
}

bool underflow_fila(const Fila* f) {
	return f->cauda == NULL;
}

void dump_fila(const Fila* f) {
	if (underflow_fila(f)) {
		printf("Nenhum Processo\n");
		return;
	}
	int contador = 1;
	printf(" N° Processo | PID | Hora Inicio | Hora Fim | Tempo Restante\n");
	Nodo* i = f->cauda;
	do {
		i = i->proximo;
		printf("%7d      |", contador);
		printf("%4d |", i->processo.PID);
		printf("  %02d:%02d:%02d   |", i->processo.hr_entrada, i->processo.min_entrada, i->processo.sec_entrada);
		printf(" %02d:%02d:%02d |", i->processo.hr_saida, i->processo.min_saida, i->processo.sec_saida);
		printf("%9d\n", i->processo.tempo_total);
		++contador;
	} while (i != f->cauda);
}

void ins_fim_fila(Fila* f, const PCB* p) {
	Nodo* n = malloc(sizeof(Nodo));
	memcpy(&n->processo, p, sizeof(PCB));
	if (f->cauda == NULL) {
		n->proximo = n;
		f->cauda = n;
	} else {
		n->proximo = f->cauda->proximo;
		f->cauda->proximo = n;
	}
	++f->num_nodos;
}

void rem_inicio_fila(Fila* f, PCB* p) {
	if (underflow_fila(f)) {
		return;
	}
	Nodo* i = f->cauda->proximo;
	memcpy(p, &i->processo, sizeof(PCB));
	if (f->cauda == i) {
		f->cauda = NULL;
	} else {
		f->cauda->proximo = i->proximo;

	}
	free(i);
	--f->num_nodos;
}

int tamanho_fila(const Fila* f) {
	return f->num_nodos;
}