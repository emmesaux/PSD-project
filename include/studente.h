// Registro studenti basato su tabella hash (ricerca per matricola).
#ifndef STUDENTE_H
#define STUDENTE_H

#include <stddef.h>
#include "configurazione.h"

typedef struct studenti_db studenti_db_t;

// Dati anagrafici minimi dello studente.
typedef struct {
    char matricola[AULA_MAX_ID];
    char nome[AULA_MAX_NOME];
    char corso[AULA_MAX_CORSO];
} studente_info_t;

// Gestione del contenitore studenti.
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | buckets | intero | Numero di contenitori logici del registro |
 * | db | studenti | Registro studenti |
 *
 * Specifica Sintattica:
 * studenti_create(intero) -> studenti
 *
 * Specifica Semantica:
 * studenti_create(buckets) = db
 * Pre: buckets > 0
 * Post: db e' un nuovo registro studenti vuoto con capacita logica definita da buckets.
 * Side-effect: inizializza il registro studenti.
 */
studenti_db_t *studenti_create(size_t buckets);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | db | studenti | Registro studenti |
 *
 * Specifica Sintattica:
 * studenti_destroy(studenti) -> void
 *
 * Specifica Semantica:
 * studenti_destroy(db) = void
 * Pre: db e' un registro valido.
 * Post: il registro studenti viene dismesso e non e' piu utilizzabile.
 * Side-effect: rilascia le risorse del modulo studenti.
 */
void studenti_destroy(studenti_db_t *db);

/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | db | studenti | Registro studenti |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | nome | stringa | Nome dello studente |
 * | corso | stringa | Corso di laurea |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * studenti_registra(studenti, stringa, stringa, stringa) -> intero
 *
 * Specifica Semantica:
 * studenti_registra(db, matricola, nome, corso) = r
 * Pre: matricola valida AND matricola non presente nel registro
 * Post: se r = successo allora lo studente risulta registrato.
 * Side-effect: modifica il registro studenti.
 */
int studenti_registra(studenti_db_t *db, const char *matricola, const char *nome, const char *corso);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | db | studenti | Registro studenti |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | r | intero | Esito della verifica |
 *
 * Specifica Sintattica:
 * studenti_esiste(studenti, stringa) -> intero
 *
 * Specifica Semantica:
 * studenti_esiste(db, matricola) = r
 * Pre: matricola valida
 * Post: r = 1 se lo studente con matricola risulta registrato, altrimenti r = 0.
 * Side-effect: Nessuno
 */
int studenti_esiste(const studenti_db_t *db, const char *matricola);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | db | studenti | Registro studenti |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | out | studente_info | Contenitore per i dati anagrafici |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * studenti_get(studenti, stringa, studente_info) -> intero
 *
 * Specifica Semantica:
 * studenti_get(db, matricola, out) = r
 * Pre: matricola valida
 * Post: se r = successo allora out contiene i dati dello studente con matricola.
 * Side-effect: Nessuno
 */
int studenti_get(const studenti_db_t *db, const char *matricola, studente_info_t *out);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | db | studenti | Registro studenti |
 * | r | intero | Numero di studenti registrati |
 *
 * Specifica Sintattica:
 * studenti_count(studenti) -> intero
 *
 * Specifica Semantica:
 * studenti_count(db) = r
 * Pre: db e' un registro valido
 * Post: r = numero di studenti registrati.
 * Side-effect: Nessuno
 */
size_t studenti_count(const studenti_db_t *db);

#endif
