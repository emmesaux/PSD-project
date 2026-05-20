// Interfaccia principale per gestione aula, prenotazioni e accessi.
#ifndef AULA_GESTIONE_H
#define AULA_GESTIONE_H

#include "errori.h"
#include "configurazione.h"

// Tipo opaco: nasconde le strutture interne.
typedef struct aula aula_t;

// Costruzione/distruzione del contesto applicativo.
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | posti_totali | intero | Numero totale di posti gestiti dall'aula |
 * | capienza_attesa | intero | Numero massimo di studenti in attesa |
 * | aula | aula | Contesto applicativo dell'aula |
 *
 * Specifica Sintattica:
 * aula_create(intero, intero) -> aula
 *
 * Specifica Semantica:
 * aula_create(posti_totali, capienza_attesa) = a
 * Pre: posti_totali > 0 AND capienza_attesa >= 0
 * Post: a e' un nuovo contesto aula con posti_totali posti e capienza_attesa;
 *       non contiene studenti, prenotazioni o presenze.
 * Side-effect: inizializza il contesto applicativo.
 */
aula_t *aula_create(int posti_totali, int capienza_attesa);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 *
 * Specifica Sintattica:
 * aula_destroy(aula) -> void
 *
 * Specifica Semantica:
 * aula_destroy(aula) = void
 * Pre: aula e' un contesto valido.
 * Post: il contesto aula viene dismesso e non e' piu utilizzabile.
 * Side-effect: rilascia le risorse del modulo aula.
 */
void aula_destroy(aula_t *aula);

// Operazioni di dominio (registrazioni, prenotazioni, accessi).
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | nome | stringa | Nome dello studente |
 * | corso | stringa | Corso di laurea dello studente |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * aula_registra_studente(aula, stringa, stringa, stringa) -> intero
 *
 * Specifica Semantica:
 * aula_registra_studente(aula, matricola, nome, corso) = r
 * Pre: matricola valida AND matricola non presente nel sistema
 * Post: se r = successo allora lo studente (matricola, nome, corso)
 *       risulta registrato nel sistema.
 * Side-effect: aggiorna l'archivio studenti.
 */
int aula_registra_studente(aula_t *aula, const char *matricola, const char *nome, const char *corso);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | data | stringa | Data della prenotazione |
 * | fascia | stringa | Fascia oraria della prenotazione |
 * | posto | intero | Indice del posto richiesto |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * aula_inserisci_prenotazione(aula, stringa, stringa, stringa, intero) -> intero
 *
 * Specifica Semantica:
 * aula_inserisci_prenotazione(aula, matricola, data, fascia, posto) = r
 * Pre: studente registrato AND posto disponibile per data/fascia
 *      AND nessuna prenotazione duplicata per matricola/data/fascia
 * Post: se r = successo allora la prenotazione e' registrata.
 * Side-effect: aggiorna lo stato prenotazioni e posti.
 */
int aula_inserisci_prenotazione(aula_t *aula, const char *matricola, const char *data, const char *fascia, int posto);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | data | stringa | Data della fascia richiesta |
 * | fascia | stringa | Fascia oraria richiesta |
 * | disponibili | numero | Numero di posti disponibili (output) |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * aula_verifica_disponibilita(aula, stringa, stringa, numero) -> intero
 *
 * Specifica Semantica:
 * aula_verifica_disponibilita(aula, data, fascia, disponibili) = r
 * Pre: data valida AND fascia valida
 * Post: se r = successo allora disponibili = numero di posti liberi per data/fascia.
 * Side-effect: Nessuno
 */
int aula_verifica_disponibilita(aula_t *aula, const char *data, const char *fascia, int *disponibili);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | data | stringa | Data della prenotazione |
 * | fascia | stringa | Fascia oraria della prenotazione |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * aula_check_in_prenotato(aula, stringa, stringa, stringa) -> intero
 *
 * Specifica Semantica:
 * aula_check_in_prenotato(aula, matricola, data, fascia) = r
 * Pre: prenotazione valida per matricola/data/fascia
 * Post: se r = successo allora lo studente risulta presente
 *       e il posto associato alla prenotazione risulta occupato.
 * Side-effect: aggiorna presenze, stato posti e storico accessi.
 */
int aula_check_in_prenotato(aula_t *aula, const char *matricola, const char *data, const char *fascia);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | data | stringa | Data dell'accesso |
 * | fascia | stringa | Fascia oraria dell'accesso |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * aula_ingresso_senza_prenotazione(aula, stringa, stringa, stringa) -> intero
 *
 * Specifica Semantica:
 * aula_ingresso_senza_prenotazione(aula, matricola, data, fascia) = r
 * Pre: studente registrato AND data valida AND fascia valida
 * Post: se r = successo allora lo studente risulta presente.
 *       Se non vi sono posti disponibili allora lo studente risulta in attesa.
 * Side-effect: aggiorna presenze o lista di attesa e lo storico accessi.
 */
int aula_ingresso_senza_prenotazione(aula_t *aula, const char *matricola, const char *data, const char *fascia);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | data | stringa | Data dell'uscita |
 * | fascia | stringa | Fascia oraria dell'uscita |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * aula_registra_uscita(aula, stringa, stringa, stringa) -> intero
 *
 * Specifica Semantica:
 * aula_registra_uscita(aula, matricola, data, fascia) = r
 * Pre: lo studente risulta presente
 * Post: se r = successo allora lo studente non risulta piu presente
 *       e il posto associato risulta libero.
 * Side-effect: aggiorna presenze, stato posti e storico accessi; puo' avanzare la lista di attesa.
 */
int aula_registra_uscita(aula_t *aula, const char *matricola, const char *data, const char *fascia);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | matricola | stringa | Identificatore univoco dello studente |
 * | data | stringa | Data della prenotazione |
 * | fascia | stringa | Fascia oraria della prenotazione |
 * | r | intero | Esito dell'operazione (es. 1 successo, 0 fallimento) |
 *
 * Specifica Sintattica:
 * aula_annulla_prenotazione(aula, stringa, stringa, stringa) -> intero
 *
 * Specifica Semantica:
 * aula_annulla_prenotazione(aula, matricola, data, fascia) = r
 * Pre: esiste una prenotazione per matricola/data/fascia
 * Post: se r = successo allora la prenotazione non risulta piu presente.
 * Side-effect: aggiorna prenotazioni e stato dei posti.
 */
int aula_annulla_prenotazione(aula_t *aula, const char *matricola, const char *data, const char *fascia);

// Metriche per report e statistiche.
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | data | stringa | Data della fascia richiesta |
 * | fascia | stringa | Fascia oraria richiesta |
 * | r | intero | Numero di prenotazioni nella fascia |
 *
 * Specifica Sintattica:
 * aula_prenotazioni_per_fascia(aula, stringa, stringa) -> intero
 *
 * Specifica Semantica:
 * aula_prenotazioni_per_fascia(aula, data, fascia) = r
 * Pre: data valida AND fascia valida
 * Post: r = numero di prenotazioni registrate per data/fascia.
 * Side-effect: Nessuno
 */
int aula_prenotazioni_per_fascia(const aula_t *aula, const char *data, const char *fascia);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | data | stringa | Data della fascia richiesta |
 * | fascia | stringa | Fascia oraria richiesta |
 * | r | intero | Numero di presenze nella fascia |
 *
 * Specifica Sintattica:
 * aula_presenze_per_fascia(aula, stringa, stringa) -> intero
 *
 * Specifica Semantica:
 * aula_presenze_per_fascia(aula, data, fascia) = r
 * Pre: data valida AND fascia valida
 * Post: r = numero di presenze registrate per data/fascia.
 * Side-effect: Nessuno
 */
int aula_presenze_per_fascia(const aula_t *aula, const char *data, const char *fascia);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | r | intero | Numero totale di prenotazioni |
 *
 * Specifica Sintattica:
 * aula_totale_prenotazioni(aula) -> intero
 *
 * Specifica Semantica:
 * aula_totale_prenotazioni(aula) = r
 * Pre: aula e' un contesto valido
 * Post: r = numero totale di prenotazioni registrate.
 * Side-effect: Nessuno
 */
int aula_totale_prenotazioni(const aula_t *aula);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | r | intero | Numero di accessi effettivi |
 *
 * Specifica Sintattica:
 * aula_accessi_effettivi(aula) -> intero
 *
 * Specifica Semantica:
 * aula_accessi_effettivi(aula) = r
 * Pre: aula e' un contesto valido
 * Post: r = numero di accessi effettivi registrati.
 * Side-effect: Nessuno
 */
int aula_accessi_effettivi(const aula_t *aula);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | r | intero | Numero di studenti in attesa |
 *
 * Specifica Sintattica:
 * aula_studenti_in_attesa(aula) -> intero
 *
 * Specifica Semantica:
 * aula_studenti_in_attesa(aula) = r
 * Pre: aula e' un contesto valido
 * Post: r = numero di studenti attualmente in attesa.
 * Side-effect: Nessuno
 */
int aula_studenti_in_attesa(const aula_t *aula);
/*
 * Dizionario dei Dati:
 * | Identificatore | Tipo | Descrizione |
 * | aula | aula | Contesto applicativo dell'aula |
 * | r | intero | Numero di studenti assenti a prenotazione |
 *
 * Specifica Sintattica:
 * aula_no_show(aula) -> intero
 *
 * Specifica Semantica:
 * aula_no_show(aula) = r
 * Pre: aula e' un contesto valido
 * Post: r = numero di studenti prenotati che non hanno effettuato accesso.
 * Side-effect: Nessuno
 */
int aula_no_show(const aula_t *aula);

#endif
