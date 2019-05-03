#include <stdbool.h>

#ifndef PCB_H
#define PCB_H

struct pcb {
	char* nome;
	int situacao; // 1 - Termino do processo
			      // 2 - Termino do quantum
				  // 3 - E/S
	int tempo_execucao; // Em ms
	int status; // 1 - Pronto
				// 2 - Executando
				// 3 - Espera
};

typedef pcb PCB;