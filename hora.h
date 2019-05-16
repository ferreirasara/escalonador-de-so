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