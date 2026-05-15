# PSD-project

Sistema in C per la gestione di un'aula studio: studenti, prenotazioni, accessi e report.

## Menu CLI
=== Menu Aula Studio ===
1) Registra studente
2) Inserisci prenotazione
3) Verifica disponibilita
4) Check-in prenotato
5) Ingresso senza prenotazione
6) Registra uscita
7) Report
0) Esci
(Durante un inserimento scrivi 0 per annullare)

## Moduli e struttura
- include/: interfacce pubbliche.
- src/: implementazioni dei moduli.
- main.c: CLI e orchestrazione.
- tests/: test di base.
- docs/: documentazione.

## ADT principali
- Studenti: tabella hash (ricerca per matricola).
- Prenotazioni: lista collegata.
- Posti aula: array.
- Presenze: lista collegata.
- Lista di attesa: coda circolare.
- Storico accessi: lista collegata.

## Documentazione
La progettazione completa e in [docs/progettazione.md](docs/progettazione.md).
