# PSD-project

Commit iniziale per abilitare la creazione di branch.
Generazione secondo Brench

Struttura iniziale del progetto, con creazione dei possibili file utili e di un inizio di progettazione.


SCHEMA COMPLETO DEGLI ADT
1?? ????? Studenti
?? ADT: Tabella Hash
Contiene: dati studenti (matricola, nome, corso)
Serve per:
registrazione
ricerca veloce per matricola
Motivo:
accesso O(1)
2?? ?? Prenotazioni
?? ADT: Lista collegata
Contiene:
matricola
data
fascia oraria
posto assegnato
Serve per:
gestire prenotazioni
annullamenti
visualizzazione prenotati
Motivo:
struttura dinamica

?? (opzionale migliore: una lista per fascia oraria)

3?? ?? Posti aula
?? ADT: Array
Contiene:
stato posto (libero/occupato/prenotato)
Serve per:
verificare disponibilit?
assegnare posti
Motivo:
accesso diretto O(1)
4?? ?? Presenze
?? ADT: Lista collegata
Contiene:
matricola
posto occupato
Serve per:
sapere chi ? dentro
gestire check-in/check-out
Motivo:
numero variabile
5?? ? Lista di attesa
?? ADT: Coda circolare (array)
Contiene:
matricole studenti in attesa
Serve per:
gestire ingresso quando aula piena
Motivo:
FIFO + ottimizzazione spazio
6?? ?? Storico accessi
?? ADT: Lista collegata
Contiene:
matricola
orario ingresso
orario uscita
stato (prenotato / no-show / attesa)
Serve per:
generare report
Motivo:
cresce dinamicamente

## Progettazione

La progettazione completa del sistema e disponibile qui:
- [docs/progettazione.md](docs/progettazione.md)
