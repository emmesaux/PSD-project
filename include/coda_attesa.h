// Coda FIFO per la lista di attesa degli accessi.
#ifndef CODA_ATTESA_H
#define CODA_ATTESA_H

#include <stddef.h>
#include "configurazione.h"

// Dati minimi per uno studente in attesa.
typedef struct {
	char matricola[AULA_MAX_ID];
	char data[AULA_MAX_DATA];
	char fascia[AULA_MAX_FASCIA];
} attesa_entry_t;

typedef struct coda_attesa coda_attesa_t;

// Gestione ciclo di vita della coda.
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | capienza | intero | Numero massimo di elementi in coda |
 * | coda | coda_attesa | Istanza della coda di attesa |
 *
 * Specifica Sintattica:
 * coda_attesa_create(intero) -> coda_attesa
 *
 * Specifica Semantica:
 * coda_attesa_create(capienza) = q
 * Pre: capienza > 0
 * Post: q e' una nuova coda vuota con capacita massima pari a capienza.
 * Side-effect: inizializza il contenitore della coda.
 */
coda_attesa_t *coda_attesa_create(size_t capienza);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | coda | coda_attesa | Istanza della coda di attesa |
 *
 * Specifica Sintattica:
 * coda_attesa_destroy(coda_attesa) -> void
 *
 * Specifica Semantica:
 * coda_attesa_destroy(coda) = void
 * Pre: coda esiste.
 * Post: coda non e' piu utilizzabile come struttura valida.
 * Side-effect: rilascia le risorse del modulo coda.
 */
void coda_attesa_destroy(coda_attesa_t *coda);

// Inserisce in fondo ed estrae il primo con data/fascia compatibili.
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | coda | coda_attesa | Istanza della coda di attesa |
 * | entry | elemento_attesa | Dati dello studente in attesa |
 * | r | intero | Esito dell'operazione |
 *
 * Specifica Sintattica:
 * coda_attesa_inserisci(coda_attesa, elemento_attesa) -> intero
 *
 * Specifica Semantica:
 * coda_attesa_inserisci(coda, entry) = r
 * Pre: entry valida.
 * Post: se r = successo allora entry risulta inserita in fondo alla coda.
 * Side-effect: modifica lo stato della coda.
 */
int coda_attesa_inserisci(coda_attesa_t *coda, const attesa_entry_t *entry);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | coda | coda_attesa | L'istanza della coda di attesa |
 * | data | stringa | La data richiesta per il match |
 * | fascia | stringa | La fascia oraria richiesta per il match |
 * | out | elemento_attesa | Contenitore per l'elemento eventualmente estratto |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * coda_attesa_estrai_match(coda_attesa, stringa, stringa, elemento_attesa) -> intero
 *
 * Specifica Semantica:
 * coda_attesa_estrai_match(coda, data, fascia, out) = r
 * Pre: data e fascia sono espresse in un formato valido.
 * Post: Se esiste in coda un elemento compatibile con data e fascia,
 *       allora r = successo, out e' uguale a quel primo elemento compatibile,
 *       e tale elemento viene rimosso da coda.
 *       Altrimenti, r = fallimento e coda resta invariata.
 * Effetti collaterali: modifica lo stato interno della coda e aggiorna out.
 */
int coda_attesa_estrai_match(coda_attesa_t *coda, const char *data, const char *fascia, attesa_entry_t *out);

/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | coda | coda_attesa | Istanza della coda di attesa |
 * | r | intero | Esito del test di vuotezza |
 *
 * Specifica Sintattica:
 * coda_attesa_vuota(coda_attesa) -> intero
 *
 * Specifica Semantica:
 * coda_attesa_vuota(coda) = r
 * Pre: coda esiste.
 * Post: r = 1 se la coda e' vuota, altrimenti r = 0.
 * Side-effect: Nessuno
 */
int coda_attesa_vuota(const coda_attesa_t *coda);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | coda | coda_attesa | Istanza della coda di attesa |
 * | r | intero | Numero di elementi presenti |
 *
 * Specifica Sintattica:
 * coda_attesa_numero(coda_attesa) -> intero
 *
 * Specifica Semantica:
 * coda_attesa_numero(coda) = r
 * Pre: coda esiste.
 * Post: r = numero di elementi presenti in coda.
 * Side-effect: Nessuno
 */
size_t coda_attesa_numero(const coda_attesa_t *coda);

#endif
