    /*APPUNTI SQL*/
    /*MANUALE IN CONTINUO AGGIORNAMENTO*/

    /*comando SELECT: usato per interrogazioni con sintassi*/
    SELECT DISTINCT [attributes] FROM (TABLE) WHERE (CONDIZIONE)

    /*attributi:  *= tutti gli attributi presenti nelle tabelle
                campo1, campo2 = seleziona solo i campi selezionati  
                tabella1, tabella2 = per relazionare due tabelle
    */
    /*EX*/ SELECT DISTINCT a1, a2, a3, ... FROM t1, t2, t3, ... WHERE c

    /*EX: VEDERE INDIRIZZO E NUMERO DI TELEFONO DELLO STUDENTE TEO VERDI*/
    SELECT indirizzo, telefono FROM studenti WHERE nome= 'TEO VERDI'

    /*I COMANDI DI SQL NON SONO CASE SENSITIVE
    POSSONON ESSERE DISTRIBUITE IN UNO O PIÚ RIGHE
    LE CHIAVI NON POSSONO ESSERE SPEZZETTATE DA UN RIGO E L'ALTRO
    */

    /*POSSIAMO CREARE OPERAZIONI TRAMITE OPERATORI ARITMETICI: +, -, *, /, ecc.*/

    /*RINOMINARE UN ATTRIBUTO QUANDO CI CONVIENE*/
    SELECT ename AS name, sal (AS) salary FROM emp
    /*POSSIAMO OMETTERE AS, PER PURISMO LO INSERIAMO*/

    /*POSSIAMO RINOMINARE ANCHE LE TABELLE*/
    SELECT professore FORM corsi (AS) p, esami (AS) e WHERE p.corso = e.corso AND matricola = "123456"
    /*professori con cui la matricola ha fatto esami*/

    /*ELIMINAZIONE DELLE RIGHE DUPLICATE*/
    SELECT DISTINCT deptno FROM emp
    /*RESTITUISCE TUTTE LE RIGHE HANNO depnot TUTTE DIVERSE*/

    /*LIMITARE LE RIGHE SELEZIONATE*/
    SELECT ename, job, deptno FROM emp WHERE sal<=comm
    /*confronto tra due attributi (sal e comm)*/

    /*OPERARTORI CONFRONTO OPERAZIONALI*/
    BETWEEN ... AND .... /*CONSENTE DI RESTITUIRE I RECORD SU UN INTERVALLO*/
    IN (list) /*SPECIFICARE UNA SERIE DI VALORI PER RESTITUIRE QUEL VALORE SPECIFICATO*/
    LIKE /*OPERATORE PATTERN MATCHING, ASSOMIGLIA A*/
    IS NULL /*VALORE NULLO*/

    /*EX*/ SELECT ename, sal FROM emp WHERE sal BETWEEN 1000 AND 1500
    /*restituisce tutti i record ename sal, con sal compreso tra 1000 e 1500*/

    /*EX*/ SELECT empno, ename, sal, mgr, FORM emp WHERE mgr IN (7902, 7566, 7788)
    /*seleziona i record con mgr uguale ai valori forniti*/

    /*EX*/ SELECT ename FROM emp WHERE ename LIKE 'S%'
    /*restituisce tutti i nomi che iniziano per S o solamente S*/
    /*ricerche wildcard:      %= denota zero o più caratteri; _=uno e un solo carattere*/
    /*S__ = stringa con iniziale S + due caratteri*/
    /*%S% = stringa con in mezzo S, non posizione esatta*/
    /*\% = cercami la stringa con %*, \= annulla il comando/

    /*EX*/ SELECT ename FROM emp WHERE sal IS (NOT) NULL
    /*SALARIO NULLO, NOT NULLO*/

    /*TUTTI STI ATTRIBUTI, CONDIZIONI, PREDICATI POSSONO ESSERE UNITI TRA DI LORO*/
    /*EX*/ SELECT ename, job, sal FROM emp WHERE job='salesman' OR job="president" AND sal>=1600

    /*ORDER BY: CONSENTE DI EFFETTUARE UN ORDINAMENTE A SECONDO DI UNO O PIÚ ATTRIBUTI*/
    /*EX*/ SELECT ename, job, deptno, hiredate FROM emp ORDER BY DESC (discendente) ASC (ascendente)
    /*EX*/ SELECT ename, job, deptno, hiredate, sal*12 (AS) annsal FROM emp ORDER BY annsal
    /*EX*/ SELECT ename, deptno FROM emp ORDER BY deptno, sal

    /*NATURAL JOIN: GIUNZIONE, RELAZIONE TRA PIÚ TABELLE IN MODO NATURALE, TRAMITE UN CAMPO COMUNE*/
    SELECT T1.C1, T2.C2 FROM T1, T2 WHERE T1.C1 = T2.C2
    /*EX*/SELECT madre, paternita.figlio, padre FROM maternita WHERE paternita.figlio = maternita.figlio
    
    /*JOIN ON: TRAMITE OPERATORE JOIN ON*/
    SELECT C1, T1.C2, C2 FROM T2 JOIN T1 ON T1.C2 = T2.C3  /*C2 = C3, DIVERSE TABELLE*/
    /*EX*/SELECT madre, paternita.figlio, padre FROM maternita JOIN paternita ON paternita.figlio = maternita.figlio
    
    /*VEDERE ALTRE JOIN NEL 7° PDF*/
    

    /*UNION: OPERATORE UNIONE*/
    SELECT C1, C2 FROM T1 WHERE (*) UNION SELECT C3, C4 FROM T2 WHERE (*)
    /*EX*/SELECT padre FROM paternita UNION SELECT madre FROM maternita

    /*OPERATORI VARI*/
    AVG /*MEDIA*/
    COUNT /*CONTATORE ELEMENTI*/
    MAX /*MASSIMO*/
    MIN /*MINIMO*/
    SUM /*SOMMA*/ 

    /*HAVING: FILTRO AGGIUNTIVO*/
    HAVING (CONDIZIONE AGGIUNTIVA)

    /*GROUP BY: RAGGRUPPAMENTO PER CAMPO*/
    GROUP BY (CAMPO)

    /*VEDERE PDF 8*/

    