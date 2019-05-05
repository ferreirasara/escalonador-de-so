#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "filagen.h"
#include "listagen.h"
#include "PCB.h"

PCB* geraProcesso();
bool geraSolicitacaoES();
bool geraFimSolicitacaoES();
int geraTempoUso();
void retornaHora(int[]);
void limpatela();


int main(void){
	srand((unsigned) time(NULL));
	
	int quantum, qtd_processos;

	limpatela();
	printf("BEM VINDO!\n\n");
	printf("Informe o número de processos: ");
	scanf("%d", &qtd_processos);
	printf("Informe a duracao do quantum (em ms): ");
	scanf("%d", & quantum);

	Lista* espera = cria_lista();
	Fila* pronto = cria_fila();

	int i;
	for (i = 0; i < qtd_processos; ++i) {
		PCB* novo;
		novo = geraProcesso();
		ins_fim_fila(pronto, novo);
	}
	dump_fila(pronto);
}

PCB* geraProcesso() {
	int hr[3];
	retornaHora(hr);

	PCB* new = malloc(sizeof(struct pcb));
	new->PID = rand() % 1000;
	new->tempo_total = rand() % 60;
	new->hr_entrada = hr[0];
	new->min_entrada = hr[1];
	new->sec_entrada = hr[2];

	return new;
}

bool geraSolicitacaoES() {
	srand((unsigned) time(NULL));
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

void retornaHora(int hr[]) {
	struct tm *data_hora_atual;     
	time_t segundos;
	time(&segundos);   
	data_hora_atual = localtime(&segundos);  

	hr[0] = data_hora_atual->tm_hour;
	hr[1] = data_hora_atual->tm_min;
	hr[2] = data_hora_atual->tm_sec;
}

void limpatela() {
	int i;
	for (i = 0; i < 50; ++i) {
		printf("\n");
	}
}