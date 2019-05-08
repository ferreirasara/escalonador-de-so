#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "filagen.h"
#include "listagen.h"
#include "PCB.h"
#include "hora.h"

Hora* retornaHora();
PCB* geraProcesso();
bool geraSolicitacaoES();
bool geraFimSolicitacaoES();
int geraTempoUso();
void limpatela();


int main(void){
	srand((unsigned) time(NULL));

	int quantum, qtd_processos;
	limpatela();
	printf("BEM VINDO!\n\n");
	printf("Informe o número de processos: ");
	scanf("%d", &qtd_processos);
	printf("Informe a duracao do quantum (em ms): ");
	scanf("%d", &quantum);

	Lista* em_espera = cria_lista();
	Fila* pronto = cria_fila();
	Fila* finalizado = cria_fila();

	int i;
	for (i = 0; i < qtd_processos; ++i) {
		PCB* novo;
		novo = geraProcesso();
		ins_fim_fila(pronto, novo);
		}
	printf("FILA DE ESTADO PRONTO\n");
	dump_fila(pronto);
	while (!underflow_fila(pronto)) {	

		PCB* processo_da_vez = geraProcesso();
		
		rem_inicio_fila(pronto, processo_da_vez);
		ins_fim_lista(em_espera, processo_da_vez);
	}
	printf("LISTA DE ESTADO EM ESPERA\n");
	dump_lista(em_espera);
}

PCB* geraProcesso() {
	Hora* hora_atual = retornaHora();
	
	PCB* new = malloc(sizeof(struct pcb));
	new->PID = rand() % 1000;
	new->tempo_total = rand() % 10000;
	new->hr_entrada = hora_atual->hr;
	new->min_entrada = hora_atual->min;
	new->sec_entrada = hora_atual->sec;

	return new;
}

bool geraSolicitacaoES() {
	bool flag_gera_ES = rand() % 2;
	return flag_gera_ES == 0 ? true : false;
}

bool geraFimSolicitacaoES() {
	srand((unsigned) time(NULL));
	bool flag_fim_ES = rand() % 2;
	return flag_fim_ES == 0 ? true : false;
}

int geraTempoUso() {
	srand((unsigned) time(NULL));
	int tempo_uso = rand() % 1000;
	return tempo_uso;
}

Hora* retornaHora() {
	Hora* atual = malloc(sizeof(struct hora));
	struct tm *data_hora_atual;
	time_t segundos;
	time(&segundos);
	data_hora_atual = localtime(&segundos);

	atual->hr = data_hora_atual->tm_hour;
	atual->min = data_hora_atual->tm_min;
	atual->sec = data_hora_atual->tm_sec;
}

void limpatela() {
	int i;
	for (i = 0; i < 50; ++i) {
		printf("\n");
	}
}