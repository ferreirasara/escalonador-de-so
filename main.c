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


int main(void){
	int quantum;

	PCB* processo1;
	processo1 = geraProcesso();
	printf("%d\n", processo1->PID);
	printf("%d\n", processo1->tempo_total);
	printf("%d:%d:%d\n", processo1->hr_entrada, processo1->min_entrada, processo1->sec_entrada);
}

PCB* geraProcesso() {
	int hr[3];
	retornaHora(hr);

	srand((unsigned) time(NULL));
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