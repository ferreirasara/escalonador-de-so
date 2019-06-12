/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Código feito por Sara Cristina Ferreira		 *
 *		Disciplina: Estrutura de Dados e Algoritmos	 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "hora.h"

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