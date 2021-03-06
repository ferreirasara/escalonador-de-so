/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Código feito por Sara Cristina Ferreira		 *
 *		Disciplina: Estrutura de Dados e Algoritmos	 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "listagen.h"
#include "hora.h"

// define o "noh" da lista
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
Lista* criaLista(void) {
	Lista* l = malloc(sizeof(Lista));
	
	l->cauda = NULL;
	l->cabeca = NULL;
	l->num_nodos = 0;
	return l;
}
void destroiLista(Lista* l) {
	while(!underflowLista(l)) {
		PCB dummy;
		remInicioLista(l, &dummy);
	}
	free(l);
}

bool underflowLista(const Lista* l) {
	return l->cabeca == NULL;
}

void dumpLista(const Lista* l) {
	if (underflowLista(l)) {
		printf("║ Nenhum Processo                                                            ║\n");
		return;
	}
	int contador = 1;
	printf("║ N° Processo │ PID │ Hora Inicio │ Hora Fim │ Tempo Restante                ║\n");
	printf("║ ────────────┼─────┼─────────────┼──────────┼───────────────                ║\n");	
	Nodo* i = l->cabeca;
	do {
		printf("║ %11d │", contador);
		printf(" %3d │", i->processo.PID);
		printf("    %02d:%02d:%02d │", i->processo.hr_entrada, i->processo.min_entrada, i->processo.sec_entrada);
		printf(" %02d:%02d:%02d │", i->processo.hr_saida, i->processo.min_saida, i->processo.sec_saida);	
		printf("%13ds                 ║\n", i->processo.tempo_total);
		i = i->proximo;
		++contador;
	} while (i != NULL);
}

void insInicioLista(Lista* l, const PCB* p) {
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

void insFimLista(Lista* l, const PCB* p) {
    if (underflowLista(l)) {
        insInicioLista(l, p);
        return;
    }
    Nodo* n = malloc(sizeof(Nodo));
    memcpy(&n->processo, p, sizeof(PCB));
    Hora* hora_atual = retornaHora();
	n->processo.hr_entrada_fila = hora_atual->hr;
	n->processo.min_entrada_fila = hora_atual->min;
	n->processo.sec_entrada_fila = hora_atual->sec;
    n->proximo = NULL;
    n->anterior = l->cauda;
    n->anterior->proximo = n;
    ++l->num_nodos;
}

void remProcessoLista(Lista* l, PCB* p, PCB* r) {
	Nodo* i = l->cabeca;
	while (i != NULL) {
		if (memcmp(&i->processo, p, sizeof(PCB)) == 0) {
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
			--l->num_nodos;
			memcpy(r, p, sizeof(PCB));
			Hora* hora_atual = retornaHora();
			int sec_entrada = (r->hr_entrada * 3600) + (r->min_entrada * 60) + (r->sec_entrada);
			int sec_saida = (hora_atual->hr * 3600) + (hora_atual->min * 60) + (hora_atual->sec);
			r->tempo_espera = sec_saida - sec_entrada;
			free(i);
			return;
		} else {
			i = i->proximo;
		}
	}
}

void remInicioLista(Lista* l, PCB* p) {
	Nodo* i = l->cabeca;
	l->cabeca = i->proximo;
	memcpy(p, &i->processo, sizeof(PCB));
	free(i);
	if (l->cabeca == NULL) {
		l->cauda = NULL;
	} else {
		l->cabeca->anterior = NULL;
	}
	--l->num_nodos;
}

bool fimES(Lista* l, PCB* p) {
	// PCB* retorno;
	Nodo* i = l->cabeca;
	while (i != NULL) {
		if(geraFimSolicitacaoES()) {
			remProcessoLista(l, &i->processo, p);
			return true;
		} else {
			i = i->proximo;
		}
	}
	return false;
}

int tamanhoLista(const Lista* l) {
	return l->num_nodos;
}

bool geraFimSolicitacaoES() {
	srand((unsigned) time(NULL));
	int flag_fim_ES = rand() % 5;
	return flag_fim_ES == 1 ? true : false;
}