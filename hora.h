/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Código feito por Sara Cristina Ferreira		 *
 *		Disciplina: Estrutura de Dados e Algoritmos	 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef HORA_H
#define HORA_H

#include <stdbool.h>

struct hora {
	int hr;
	int min;
	int sec;
};

typedef struct hora Hora;

Hora* retornaHora();

#endif