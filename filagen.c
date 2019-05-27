#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filagen.h"
#include "hora.h"

// definicao do "noh" da fila
struct nodo {
	PCB processo;
	struct nodo* proximo;
};
typedef struct nodo Nodo;

struct fila {
	Nodo* cauda;
	size_t num_nodos;
};

Fila* criaFila(void) {
	Fila* f = malloc(sizeof(Fila));
	
	f->cauda = NULL;
	f->num_nodos = 0;

	return f;
}

void destroiFila(Fila* f) {
	while(!underflowFila(f)) {
		PCB dummy;
		remInicioFila(f, &dummy);
	}
	free(f);
}

bool underflowFila(const Fila* f) {
	return f->cauda == NULL;
}

void dumpFila(const Fila* f) {
	if (underflowFila(f)) {
		printf("║ Nenhum Processo                                                            ║\n");
		return;
	}
	int contador = 1;
	printf("║ N° Processo │ PID │ Hora Inicio │ Hora Fim │ Tempo Restante                ║\n");
	printf("║ ────────────┼─────┼─────────────┼──────────┼───────────────                ║\n");
	Nodo* i = f->cauda;
	do {
		i = i->proximo;
		printf("║ %11d │", contador);
		printf(" %3d │", i->processo.PID);
		printf("    %02d:%02d:%02d │", i->processo.hr_entrada, i->processo.min_entrada, i->processo.sec_entrada);
		printf(" %02d:%02d:%02d │", i->processo.hr_saida, i->processo.min_saida, i->processo.sec_saida);
		printf("%13ds                 ║\n", i->processo.tempo_total);
		++contador;
	} while (i != f->cauda);
}
void dumpFilaFinalizado(const Fila* f) {
	if (underflowFila(f)) {
		printf("║ Nenhum Processo                                                            ║\n");
		return;
	}
	int contador = 1;
	int tempo_processador = 0;
	printf("║ N° Processo │ PID │ Hora Inicio │ Hora Fim │ Tempo Total │ Tempo em Espera ║\n");
	printf("║ ────────────┼─────┼─────────────┼──────────┼─────────────┼──────────────── ║\n");
	Nodo* i = f->cauda;
	do {
		i = i->proximo;
		printf("║ %11d │", contador);
		printf(" %3d │", i->processo.PID);
		printf("    %02d:%02d:%02d │", i->processo.hr_entrada, i->processo.min_entrada, i->processo.sec_entrada);
		printf(" %02d:%02d:%02d │", i->processo.hr_saida, i->processo.min_saida, i->processo.sec_saida);
		printf(" %10ds │", i->processo.tempo_gasto);
		printf(" %14ds ║\n", i->processo.tempo_espera);
		++contador;
		tempo_processador += i->processo.tempo_gasto;
	} while (i != f->cauda);
	printf("║ Tempo acumulado da ultilizacao do processador: %3ds                        ║\n", tempo_processador);
}

void insFimFila(Fila* f, const PCB* p) {
	Nodo* n = malloc(sizeof(Nodo));
	memcpy(&n->processo, p, sizeof(PCB));
	Hora* hora_atual = retornaHora();
	// necessario para calcular o tempo em espera (conta o tempo na fila de pronto)
	n->processo.hr_entrada_fila = hora_atual->hr;
	n->processo.min_entrada_fila = hora_atual->min;
	n->processo.sec_entrada_fila = hora_atual->sec;
	if (f->cauda == NULL) {
		f->cauda = n;
		n->proximo = n;
	} else {
		n->proximo = f->cauda->proximo;
		f->cauda->proximo = n;
		f->cauda = n;
	}
	++f->num_nodos;
}
void remInicioFila(Fila* f, PCB* p) {
	if (underflowFila(f)) {
		return;
	}
	Nodo* i = f->cauda->proximo;
	memcpy(p, &i->processo, sizeof(PCB));
	Hora* hora_atual = retornaHora();
	// transforma em segundos para poder calcular o tempo
	int sec_entrada = (p->hr_entrada * 3600) + (p->min_entrada * 60) + (p->sec_entrada);
	int sec_saida = (hora_atual->hr * 3600) + (hora_atual->min * 60) + (hora_atual->sec);
	// tempo total em espera
	p->tempo_espera = sec_saida - sec_entrada;

	if (f->cauda == i) {
		f->cauda = NULL;
	} else {
		f->cauda->proximo = i->proximo;
	}
	free(i);
	--f->num_nodos;
}

int tamanhoFila(const Fila* f) {
	return f->num_nodos;
}