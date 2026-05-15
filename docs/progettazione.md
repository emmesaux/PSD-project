# Progettazione - Sistema Gestione Aula Studio

## 1. Obiettivo del sistema
Questo sistema in C gestisce accessi e prenotazioni di un'aula studio.
La progettazione descrive architettura, moduli, flussi, responsabilita e vincoli.

## 2. Vincoli progettuali
- Linguaggio: C99.
- Interfaccia: CLI a menu.
- Information hiding: gli ADT espongono solo API pubbliche.

## 3. Architettura logica
Il sistema ha tre livelli.

1. Presentazione (CLI)
- Gestisce input/output e menu.
- Inoltra le richieste alla logica applicativa.

2. Funzioni del sistema
- Coordina registrazioni, prenotazioni, accessi, attese e report.

3. ADT (Dati)
- Implementa strutture dati e operazioni primitive.

## 4. ADT scelti e responsabilita
### 4.1 Studenti - Tabella Hash
Responsabilita:
- Inserimento studenti.
- Ricerca per matricola.
- Verifica esistenza.

Motivazione:
- Accesso medio O(1) per chiave.

### 4.2 Prenotazioni - Lista collegata
Responsabilita:
- Inserimento prenotazioni.
- Ricerca per studente/data/fascia.
- Annullamenti.

Motivazione:
- Struttura dinamica adatta a inserimenti e rimozioni.

### 4.3 Posti aula - Array
Responsabilita:
- Stato posto (libero, prenotato, occupato).
- Verifica disponibilita per fascia.
- Assegnazione e rilascio posto.

Motivazione:
- Accesso diretto per indice.

### 4.4 Presenze - Lista collegata
Responsabilita:
- Traccia studenti presenti.
- Supporto a check-in e check-out.

Motivazione:
- Cardinalita variabile.

### 4.5 Lista di attesa - Coda circolare su array
Responsabilita:
- Inserimento in attesa quando l'aula e piena.
- Estrazione FIFO quando si libera un posto.

Motivazione:
- Ordine di arrivo e uso efficiente della memoria.

### 4.6 Storico accessi - Lista collegata
Responsabilita:
- Registra ingresso e uscita.
- Traccia lo stato finale (prenotato, no-show, da attesa).

Motivazione:
- Crescita dinamica e append naturale.

## 5. Interazioni tra componenti
### 5.1 Registrazione studente
CLI -> Gestione aula -> ADT Studenti.

### 5.2 Prenotazione posto
CLI -> Gestione aula -> ADT Studenti -> ADT Posti -> ADT Prenotazioni.

### 5.3 Check-in studente prenotato
CLI -> Gestione aula -> ADT Prenotazioni -> ADT Posti -> ADT Presenze -> ADT Storico.

### 5.4 Ingresso senza prenotazione
CLI -> Gestione aula -> ADT Posti.
- Posto libero: aggiorna Presenze e Storico.
- Aula piena: inserisce in Lista Attesa.

### 5.5 Uscita studente
CLI -> Gestione aula -> ADT Presenze -> ADT Posti -> ADT Storico -> ADT Lista Attesa.

### 5.6 Report
CLI -> Report -> ADT Prenotazioni, Presenze, Storico, Lista Attesa.

## 6. Regole principali
- Uno studente deve essere registrato prima di prenotare.
- Un posto non puo essere assegnato a due studenti nella stessa fascia.
- Il check-in prenotato richiede prenotazione valida.
- L'ingresso senza prenotazione richiede posto libero.
- In caso di aula piena si usa la lista di attesa FIFO.
- L'uscita libera il posto e puo attivare una promozione dalla lista.

## 7. Invarianti di sistema
- Una matricola identifica uno studente in modo univoco.
- Uno studente non puo risultare presente due volte.
- Un posto non puo essere libero e occupato nello stesso istante.
- Ogni check-in e check-out deve comparire nello storico.

## 8. Progettazione del menu CLI
Voci previste:
1. Registra studente
2. Inserisci prenotazione
3. Verifica disponibilita
4. Check-in prenotato
5. Ingresso senza prenotazione
6. Registra uscita
7. Report
0. Esci

Nota operativa:
- Durante un inserimento, scrivere 0 per annullare e tornare al menu.

## 9. Metriche e output report
Il report include:
- Numero totale prenotazioni.
- Accessi effettivi.
- Occupazione per fascia oraria.
- Numero studenti no-show.
- Numero studenti rimasti in attesa.

## 10. Struttura file (versione accorpata)
- include/: interfacce pubbliche dei moduli.
- src/: implementazioni core dei moduli.
- main.c: CLI e orchestrazione.
- tests/: test di base.
- docs/: report e progettazione.

## 10.1 Mappatura file --> moduli
### Moduli principali
- **include/studente.h** e **src/studente.c**: Anagrafica studenti (tabella hash).
- **include/aula_gestione.h** e **src/aula_gestione.c**: Prenotazioni, presenze e logica di accesso.
- **include/coda_attesa.h** e **src/coda_attesa.c**: Lista di attesa FIFO (coda circolare).
- **include/report.h** e **src/report.c**: Calcolo e stampa report.
- **include/errori.h**: Codici esito comuni.
- **include/configurazione.h**: Costanti e limiti input.

### Presentazione e test
- **main.c**: Menu CLI.
- **tests/test_main.c**: Test di integrazione base.

Inserire una sezione esplicita con:
- Sistema operativo usato per sviluppo e test (Windows).
- Compilatore e versione.
- Standard C usato C99.

## 11. Criteri di accettazione della progettazione
La progettazione e completa se:
- Copre tutti i requisiti funzionali della traccia.
- Definisce responsabilita e confini dei moduli.
- Esplicita i flussi operativi.
- Stabilisce invarianti verificabili nei test.
- E pronta per essere tradotta in codice.
