# Progettazione - Sistema Gestione Aula Studio

## 1. Obiettivo del sistema
Progettare un sistema in C per gestire accessi e prenotazioni di un'aula studio universitaria.
La progettazione copre architettura, moduli, flussi operativi, responsabilita e vincoli.

## 2. Vincoli progettuali
- Linguaggio target: C99.
- Interfaccia utente: CLI a menu.
- Information hiding: ogni ADT espone solo API pubbliche, nascondendo i dettagli interni.

## 3. Architettura logica
Il sistema e suddiviso in tre livelli.

1. Livello Presentazione (CLI)
- Gestisce input/output utente e menu.
- Passa le richieste ai moduli di gestione.

2. Livello Funzioni del sistema
- Coordina le operazioni principali: registrazione, prenotazione, check-in/check-out, attesa, report.

3. Livello ADT (Dati)
- Implementa strutture dati e operazioni primitive in modo incapsulato.

## 4. ADT scelti e responsabilita
### 4.1 Studenti - Tabella Hash
Responsabilita:
- Inserimento nuovo studente.
- Ricerca per matricola.
- Verifica esistenza studente.

Motivazione:
- Accesso medio O(1) per operazioni frequenti su matricola.

### 4.2 Prenotazioni - Lista collegata
Responsabilita:
- Inserimento prenotazione.
- Ricerca prenotazioni per studente/data/fascia.
- Annullamento prenotazione.
- Visualizzazione prenotati.

Motivazione:
- Struttura dinamica adatta a inserimenti/rimozioni frequenti.

### 4.3 Posti aula - Array
Responsabilita:
- Stato posto (libero, prenotato, occupato).
- Verifica disponibilita per fascia.
- Assegnazione/rilascio posto.

Motivazione:
- Accesso diretto O(1) per indice posto.

### 4.4 Presenze - Lista collegata
Responsabilita:
- Traccia studenti attualmente presenti.
- Supporto a check-in e check-out.

Motivazione:
- Cardinalita variabile durante la giornata.

### 4.5 Lista di attesa - Coda circolare su array
Responsabilita:
- Inserimento in attesa quando aula piena.
- Estrazione FIFO quando si libera un posto.

Motivazione:
- Politica equa FIFO e uso efficiente dello spazio.

### 4.6 Storico accessi - Lista collegata
Responsabilita:
- Registrazione eventi ingresso/uscita.
- Tracciamento stato finale (prenotato, no-show, da attesa).
- Supporto report statistici.

Motivazione:
- Crescita dinamica e append naturale degli eventi.

## 5. Interazioni tra componenti
### 5.1 Registrazione studente
CLI -> Servizio Studenti -> ADT Studenti.

### 5.2 Prenotazione posto
CLI -> Servizio Prenotazioni -> ADT Studenti (validazione matricola) -> ADT Posti (disponibilita) -> ADT Prenotazioni (inserimento).

### 5.3 Check-in studente prenotato
CLI -> Servizio Accessi -> ADT Prenotazioni (verifica) -> ADT Posti (stato occupato) -> ADT Presenze (inserimento) -> ADT Storico (evento ingresso).

### 5.4 Ingresso senza prenotazione
CLI -> Servizio Accessi -> ADT Posti.
- Se posto disponibile: ingresso diretto e aggiornamento Presenze/Storico.
- Se aula piena: enqueue in ADT Lista Attesa.

### 5.5 Uscita studente
CLI -> Servizio Accessi -> ADT Presenze (rimozione) -> ADT Posti (rilascio) -> ADT Storico (evento uscita) -> ADT Lista Attesa (eventuale promozione del primo in coda).

### 5.6 Report
CLI -> Servizio Report -> ADT Prenotazioni + ADT Presenze + ADT Storico + ADT Lista Attesa.

## 6. Regole principali
- Uno studente deve essere registrato prima di prenotare.
- Un posto non puo essere assegnato a due studenti nella stessa fascia.
- Il check-in prenotato e consentito solo se prenotazione valida.
- L'ingresso senza prenotazione e consentito solo con posti liberi.
- In caso di aula piena, l'ingresso passa in lista di attesa FIFO.
- L'uscita libera il posto e puo innescare promozione automatica dalla lista di attesa.

## 7. Invarianti di sistema
- Una matricola identifica univocamente uno studente.
- Uno studente non puo risultare presente due volte contemporaneamente.
- Uno stesso posto non puo essere contemporaneamente libero e occupato.
- Ogni check-in/check-out deve avere corrispondenza nello storico.

## 8. Progettazione del menu CLI
Voci minime previste:
1. Registra studente
2. Inserisci prenotazione
3. Verifica disponibilita posti
4. Check-in prenotato
5. Ingresso senza prenotazione
6. Registra uscita
7. Visualizza prenotati
8. Visualizza presenti
9. Visualizza lista di attesa
10. Annulla prenotazione
11. Visualizza storico accessi
12. Genera report riepilogativo
13. Esci

## 9. Metriche e output report
Il report deve includere almeno:
- Numero totale prenotazioni.
- Accessi effettivi.
- Occupazione per fascia oraria.
- Numero studenti no-show.
- Numero studenti rimasti in attesa.

## 10. Specifica sintattica e semantica
In questa fase manteniamo solo 3 funzioni guida, utili per avviare l'implementazione dei file.

### 10.1 Registra studente
SPECIFICA SINTATTICA
int registra_studente(char*, char*, char*)->int
tipi char*, char*, char*, int

SPECIFICA SEMANTICA
registra_studente(matricola, nome, corso)->r
precondizione: matricola valida e non gia presente
postcondizione: lo studente viene inserito nella tabella studenti
side effect: aggiornamento della tabella hash studenti

### 10.2 Inserisci prenotazione
SPECIFICA SINTATTICA
int inserisci_prenotazione(char*, char*, char*, int)->int
tipi char*, char*, char*, int, int

SPECIFICA SEMANTICA
inserisci_prenotazione(matricola, data, fascia_oraria, posto)->r
precondizione: studente registrato, posto disponibile, nessun duplicato su matricola/data/fascia
postcondizione: prenotazione registrata e posto marcato come prenotato
side effect: aggiornamento lista prenotazioni e stato posti

### 10.3 Verifica disponibilita posti
SPECIFICA SINTATTICA
int verifica_disponibilita(char*, char*)->int
tipi char*, char*, int

SPECIFICA SEMANTICA
verifica_disponibilita(data, fascia_oraria)->r
precondizione: data e fascia_oraria valide
postcondizione: r rappresenta il numero di posti disponibili nella fascia richiesta
side effect: non ce ne sono

## 11. Struttura file proposta (solo progettazione)
- include/: interfacce pubbliche dei moduli.
- src/adt/: implementazioni ADT.
- src/services/: regole del sistema.
- src/app/: menu CLI e orchestrazione.
- tests/: test unitari e integrazione.
- docs/: report e progettazione.

## 12. Ambiente di sviluppo da dichiarare nel report
Inserire una sezione esplicita con:
- Sistema operativo usato per sviluppo e test (Windows).
- Compilatore e versione.
- Standard C usato C99.

## 13. Criteri di accettazione della progettazione
La progettazione e considerata completa se:
- Copre tutti i requisiti funzionali della traccia.
- Definisce responsabilita e confini dei moduli.
- Esplicita flussi operativi.
- Stabilisce invarianti verificabili nei test.
- E pronta per essere tradotta in codice senza ambiguita.
