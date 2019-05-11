#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "filagen.h"
#include "listagen.h"
#include "PCB.h"
#include "hora.h"

#define RED     "\x1b[31m"
#define GREEN	"\e[0;32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define BOLD	"\033[1m"
#define RESET   "\x1b[0m"

Hora* retornaHora();
PCB* geraProcesso();
PCB* geraProcessoVazio();
void finalizaProcesso(PCB*);
bool geraSolicitacaoES();
bool geraFimSolicitacaoES();
void limpaTela();
void exibeProcesso(PCB*);


int main(void){
	srand((unsigned) time(NULL));
	Fila* pronto = cria_fila();
	Fila* finalizado = cria_fila();
	Lista* em_espera = cria_lista();

	// Inicio do programa
	Hora* hr_inicio = retornaHora();
	int quantum, qtd_processos;
	limpaTela();
	printf("BEM VINDO!\n\n");
	printf("Informe o número de processos: ");
	scanf("%d", &qtd_processos);
	printf("Informe a duracao do quantum (em ms): ");
	scanf("%d", &quantum);
	printf("--------------------------------------------------------------\n");
	limpaTela();

	// Inicializa a lista com processos prontos, na quantidade informada pelo usuário
	int i;
	for (i = 0; i < qtd_processos; ++i) {
		PCB* novo = geraProcesso();
		ins_fim_fila(pronto, novo);
	}
	while (tamanho_fila(finalizado) < qtd_processos) {
		limpaTela();
		printf(RESET"\nInicio do programa: %02d:%02d:%02d\n", hr_inicio->hr, hr_inicio->min, hr_inicio->sec);
		printf(RED "--------------------------------------------------------------\n");
		printf(BOLD"\t\t\tPROCESSOS PRONTOS\n"RESET RED);
		printf("QTD de processos: %d\n", tamanho_fila(pronto));
		dump_fila(pronto);
		
		printf(RESET YELLOW "--------------------------------------------------------------\n");
		printf(BOLD"\t\t       PROCESSOS EM ESPERA\n"RESET YELLOW);
		dump_lista(em_espera);

		printf(RESET GREEN"--------------------------------------------------------------\n");
		printf(BOLD"\t\t      PROCESSOS FINALIZADOS\n"RESET GREEN);
		dump_fila(finalizado);
		printf(RESET BLUE"--------------------------------------------------------------\n");
		
		// Cria um novo processo, que sera trabalhado mais adiante
		PCB* processo_da_vez;
		// Pega o primeiro processo da fila de processos prontos
		rem_inicio_fila(pronto, processo_da_vez);
		// Se o processo pedir ES vai para lista em espera
		if (geraSolicitacaoES()) {
			printf("O processo %d solicitou E/S\n", processo_da_vez->PID);
			printf("--------------------------------------------------------------\n");
			ins_inicio_lista(em_espera, processo_da_vez);
		} else {
			// Se não, vai para o processador, diminui o tempo total de execução e volta para fila pronto
			printf("O processo %d foi para o processador\n", processo_da_vez->PID);
			printf("--------------------------------------------------------------\n");
			processo_da_vez->tempo_total -= quantum;
			ins_fim_fila(pronto, processo_da_vez);
		}
		if (processo_da_vez->tempo_total <= 0) {
			printf("O processo %d terminou sua execucao\n", processo_da_vez->PID);
			printf("--------------------------------------------------------------\n");
			finalizaProcesso(processo_da_vez);
			ins_fim_fila(finalizado, processo_da_vez);
		}
		if (fimES(em_espera, processo_da_vez)) {
			printf("O processo %d teve uma resposta para E/S\n", processo_da_vez->PID);
			printf("--------------------------------------------------------------\n");
			ins_fim_fila(pronto, processo_da_vez);
		}
		printf(RESET"Pressione qualquer tecla para continuar: ");
		char next;
		scanf(" %c", &next);
	}
	limpaTela();
	printf(BOLD RED"\t\t\tRESUMO\n"RESET);
	printf(RED"--------------------------------------------------------------\n");
	dump_fila(finalizado);
	printf("--------------------------------------------------------------\n"RESET);
}

PCB* geraProcesso() {
	Hora* hora_atual = retornaHora();
	
	PCB* new = malloc(sizeof(struct pcb));
	new->PID = rand() % 1000;
	new->tempo_total = rand() % 1000;
	new->hr_entrada = hora_atual->hr;
	new->min_entrada = hora_atual->min;
	new->sec_entrada = hora_atual->sec;

	return new;
}

void finalizaProcesso(PCB* p) {
	Hora* hora_atual = retornaHora();
	p->hr_saida = hora_atual->hr;
	p->min_saida = hora_atual->min;
	p->sec_saida = hora_atual->sec;
}

bool geraSolicitacaoES() {
	int flag_gera_ES = rand() % 2;
	return flag_gera_ES == 0 ? true : false;
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

void limpaTela() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}