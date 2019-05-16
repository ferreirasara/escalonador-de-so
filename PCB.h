#ifndef PCB_H
#define PCB_H

#include <stdbool.h>

struct pcb {
	int PID;			// Identificador do processo
	int tempo_total;	// Em s
	int hr_entrada, min_entrada, sec_entrada;
	int hr_saida, min_saida, sec_saida;
	int hr_entrada_fila, min_entrada_fila, sec_entrada_fila;
	// int hr_saida_fila, min_saida_fila, sec_saida_fila;
	int tempo_gasto;
	int tempo_espera;
};

typedef struct pcb PCB;

#endif