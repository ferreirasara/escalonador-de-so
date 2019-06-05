#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "filagen.h"
#include "listagen.h"
#include "PCB.h"
#include "hora.h"

// Definicao das cores que serao usadas
#define RED     "\x1b[31m"
#define GREEN	"\e[0;32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define BOLD	"\033[1m"
#define BLINK	"\033[5m"
#define RESET   "\x1b[0m"

// Prototipo das funcoes
PCB* geraProcesso();
PCB* geraProcessoVazio();
void finalizaProcesso(PCB*);
bool geraSolicitacaoES();
bool geraFimSolicitacaoES();

int main(void){
	srand((unsigned) time(NULL));
	// criacao das listas e filas
	Fila* pronto = criaFila();
	Fila* finalizado = criaFila();
	Lista* em_espera = criaLista();

	// Inicio do programa
	Hora* hr_inicio = retornaHora();
	int quantum, qtd_processos, modo;
	system("clear");
	printf(YELLOW"╔══════════════════════════════════════════════════════════╗\n");
	puts("║                     _                       _            ║");
	puts("║  ___  ___  ___ __ _| | ___  _ __   __ _  __| | ___  _ __ ║");
	puts("║ / _ \\/ __|/ __/ _` | |/ _ \\| '_ \\ / _` |/ _` |/ _ \\| '__|║");
	puts("║|  __/\\__ \\ (_| (_| | | (_) | | | | (_| | (_| | (_) | |   ║");
	puts("║ \\___||___/\\___\\__,_|_|\\___/|_| |_|\\__,_|\\__,_|\\___/|_|   ║");
	puts("║                                                          ║");
	puts("║     _                                                    ║");
	puts("║  __| | ___   ___   ___                                   ║");
	puts("║ / _` |/ _ \\ / __| / _ \\                                  ║");
	puts("║| (_| |  __/ \\__ \\| (_) |                                 ║");
	puts("║ \\__,_|\\___| |___(_)___(_)                                ║");
	puts("║                                                          ║");
	puts("╚══════════════════════════════════════════════════════════╝");
	puts("");
	printf(RESET" Informe o número de processos: ");
	scanf("%d", &qtd_processos);
	printf(" Informe a duracao do quantum (em s): ");
	scanf("%d", &quantum);
	while (modo != 1 && modo != 2) {
		printf(" Escolha o modo:\n [1] Automatico\n [2] Por passos\n");
		scanf("%d", &modo);
	}
	system("clear");

	// Inicializa a lista com processos prontos, na quantidade informada pelo usuário
	int i;
	for (i = 0; i < qtd_processos; ++i) {
		PCB* novo = geraProcesso();
		insFimFila(pronto, novo);
	}
	// Executa o programa enquanto existir processos para rodar
	while (tamanhoFila(finalizado) < qtd_processos) {
		system("clear");
		printf(RESET"\nInicio do programa: %02d:%02d:%02d\n", hr_inicio->hr, hr_inicio->min, hr_inicio->sec);
		printf(RED"╔════════════════════════════════════════════════════════════════════════════╗\n");
		printf(BOLD"║                             PROCESSOS PRONTOS                              ║\n"RESET RED);
		printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
		printf("║ QTD de processos: %3d                                                      ║\n", tamanhoFila(pronto));
		dumpFila(pronto);
		
		printf(RESET YELLOW "╠════════════════════════════════════════════════════════════════════════════╣\n");
		printf(BOLD"║                            PROCESSOS EM ESPERA                             ║\n"RESET YELLOW);
		printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
		printf("║ QTD de processos: %3d                                                      ║\n", tamanhoLista(em_espera));
		dumpLista(em_espera);

		printf(RESET GREEN"╠════════════════════════════════════════════════════════════════════════════╣\n");
		printf(BOLD"║                           PROCESSOS FINALIZADOS                            ║\n"RESET GREEN);
		printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
		printf("║ QTD de processos: %3d                                                      ║\n", tamanhoFila(finalizado));
		dumpFilaFinalizado(finalizado);
		printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
		
		// Cria um novo processo, que sera trabalhado mais adiante
		PCB* processo_da_vez = malloc(sizeof(struct pcb));
		// Pega o primeiro processo da fila de processos prontos
		if (!underflowFila(pronto)) {
			// Pega o primeiro processo da fila e o coloca no processador
			remInicioFila(pronto, processo_da_vez);
			printf(RESET"║ O processo %3d foi para o processador                                      ║\n", processo_da_vez->PID);
			int contador = 0;
			bool solicitou = false;
			while (contador <= quantum) {
				contador++;
				sleep(1);
				if (processo_da_vez->tempo_total == contador) {
					// desconta do tempo total o tempo que o processo ficou no processador
					processo_da_vez->tempo_total -= contador;
					break;
				} else if (geraSolicitacaoES()) {
					printf("║ O processo %3d solicitou E/S                                               ║\n", processo_da_vez->PID);
					// desconta do tempo total o tempo que o processo ficou no processador
					processo_da_vez->tempo_total -= contador;
					// coloca o processo na lista de espera
					insInicioLista(em_espera, processo_da_vez);
					solicitou = true;
					break;
				} 
			}
			printf("║ O processo %3d executou por %3ds. Seu \"tamanho\" diminuiu para %3d.         ║\n", processo_da_vez->PID, contador, processo_da_vez->tempo_total);
			if (processo_da_vez->tempo_total <= 0) {
				// se o processo terminou a execucao, o coloca na fila dos processos finalizados
				printf("║ O processo %3d terminou sua execucao                                       ║\n", processo_da_vez->PID);
				finalizaProcesso(processo_da_vez);
				insFimFila(finalizado, processo_da_vez);
			} else if (!solicitou) {
				// se o processo nao solicitou E/S e ainda não foi atendido, volta para a fila pronto
				processo_da_vez->tempo_total -=contador;
				insFimFila(pronto, processo_da_vez);
			} else if (!underflowLista(em_espera)) {
				// se a lista de espera nao esta vazia, existe a possibilidade de um processo ter uma resposta para E/S
				if (fimES(em_espera, processo_da_vez)) {
					printf("║ O processo %3d teve uma resposta para E/S                                  ║\n", processo_da_vez->PID);
					insFimFila(pronto, processo_da_vez);
				}
			}
		} else {
			// se a fila dos processos prontos esta vazia, e a fila dos finalizados nao esta cheia, existe processos em espera
			printf(RESET"║ Aguardando E/S de um dos processos                                         ║\n");
			// ate um processo receber uma resposta E/S
			while (true) {
				if (fimES(em_espera, processo_da_vez)) {
					printf("║ O processo %3d teve uma resposta para E/S                                  ║\n", processo_da_vez->PID);
					insFimFila(pronto, processo_da_vez);
					break;
				}
			}
		}
		if (modo == 2) {
			// Modo por passos
			printf(RESET"Pressione qualquer tecla para continuar: ");
			char next;
			scanf(" %c", &next);
		} else {
			// Modo automatico
			printf("║ Proximo processo...                                                        ║\n");
			printf("╚════════════════════════════════════════════════════════════════════════════╝\n");
			sleep(1);
		}
	}
	printf("Finalizando...\n");
	sleep(1);
	system("clear");
	printf(BOLD " RESUMO\n"RESET);
	printf(GREEN"╔════════════════════════════════════════════════════════════════════════════╗\n");
	dumpFilaFinalizado(finalizado);
	printf("╚════════════════════════════════════════════════════════════════════════════╝\n"RESET);

	destroiFila(finalizado);
	destroiFila(pronto);
	destroiLista(em_espera);
}

PCB* geraProcesso() {
	Hora* hora_atual = retornaHora();
	
	PCB* new = malloc(sizeof(struct pcb));
	new->PID = rand() % 1000;
	// + 1 para nao ter processos com tempo igual a zero
	new->tempo_total = rand() % 10 + 1;
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
	// transforma o tempo em segundos para poder calcular
	int sec_entrada = (p->hr_entrada * 3600) + (p->min_entrada * 60) + (p->sec_entrada);
	int sec_saida = (p->hr_saida * 3600) + (p->min_saida * 60) + (p->sec_saida);
	// faz o calculo do tempo total
	p->tempo_gasto = sec_saida - sec_entrada;
}

bool geraSolicitacaoES() {
	int flag_gera_ES = rand() % 4;
	return flag_gera_ES == 0 ? true : false;
}

void limpaTela() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
