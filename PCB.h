#ifndef PCB_H
#define PCB_H

#include <stdbool.h>

struct pcb {
	int PID;			// Identificador do processo
	int tempo_total;	// Em ms
	int hr_entrada, min_entrada, sec_entrada;
	int hr_saida, min_saida, sec_saida;
};

typedef struct pcb PCB;

#endif