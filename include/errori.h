// Codici di esito comuni per uniformare la gestione errori.
#ifndef ERRORI_H
#define ERRORI_H

typedef enum {
	AULA_OK = 0,
	AULA_ERRORE_ALLOC = -1,
	AULA_ERRORE_INPUT = -2,
	AULA_ERRORE_DUPLICATO = -3,
	AULA_ERRORE_NON_TROVATO = -4,
	AULA_ERRORE_PIENO = -5
} aula_esito_t;

#endif
