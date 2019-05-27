#ifndef PCB_H
#define PCB_H

#include <stdbool.h>

struct pcb {
	int PID; // Identificador do processo
	int tempo_total; // Em s
	int hr_entrada, min_entrada, sec_entrada; // Hora de criacao do processo
	int hr_saida, min_saida, sec_saida; // Hora de termino do processo
	int hr_entrada_fila, min_entrada_fila, sec_entrada_fila; // Hora de entrada na fila de espera
	int tempo_gasto; // Tempo total gasto
	int tempo_espera; // Tempo total em espera
};

typedef struct pcb PCB;

#endif