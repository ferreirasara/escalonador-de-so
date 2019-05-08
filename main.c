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
PCB* geraProcessoVazio();
bool geraSolicitacaoES();
bool geraFimSolicitacaoES();
int geraTempoUso();
void limpatela();
void exibeProcesso(PCB*);


int main(void){
	srand((unsigned) time(NULL));
	Fila* pronto = cria_fila();
	Fila* finalizado = cria_fila();
	Lista* em_espera = cria_lista();

	// Inicio do programa
	int quantum, qtd_processos;
	limpatela();
	printf("BEM VINDO!\n\n");
	printf("Informe o número de processos: ");
	scanf("%d", &qtd_processos);
	printf("Informe a duracao do quantum (em ms): ");
	scanf("%d", &quantum);
	printf("-------------------------------------------------------\n");
	limpatela();

	// Inicializa a lista com processos prontos, na quantidade informada pelo usuário
	int i;
	for (i = 0; i < qtd_processos; ++i) {
		PCB* novo = geraProcesso();
		ins_fim_fila(pronto, novo);
	}

	

	printf("FILA DE ESTADO PRONTO\n");
	dump_fila(pronto);
	printf("-------------------------------------------------------\n");
	PCB* processo_da_vez = geraProcessoVazio();
	printf("LISTA DE ESTADO EM ESPERA\n");
	dump_lista(em_espera);
	printf("-------------------------------------------------------\n");
	rem_inicio_fila(pronto, processo_da_vez);
	ins_fim_lista(em_espera, processo_da_vez);
	printf("-------------------------------------------------------\n");
	printf("LISTA DE ESTADO EM ESPERA\n");
	dump_lista(em_espera);
	printf("-------------------------------------------------------\n");
}

PCB* geraProcessoVazio() {
	PCB* new = malloc(sizeof(struct pcb));
	new->PID = 0;
	new->tempo_total = 0;
	new->hr_entrada = 0;
	new->min_entrada = 0;
	new->sec_entrada = 0;
	new->hr_saida = 0;
	new->min_saida = 0;
	new->sec_saida = 0;

	return new;
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

void exibeProcesso(PCB* p) {
	printf("PID: %d\n", p->PID);
	printf("Tempo Total: %d\n", p->tempo_total);
	printf("Hora Entrada: %02d:%02d:%02d\n", p->hr_entrada, p->min_entrada, p->sec_entrada);
}

void limpatela() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}