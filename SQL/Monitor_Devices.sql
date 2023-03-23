SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `Monitor_Devices`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `DISPOSITIVI`
--

CREATE TABLE `DISPOSITIVI` (
  `nome` varchar(255) NOT NULL,
  `descrizione` varchar(255) NOT NULL,
  `stato` varchar(7) NOT NULL DEFAULT 'ATTESA',
  `id_dispositivo` int(11) NOT NULL,
  `utente` int(11) NOT NULL,
  `tipo` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `DISPOSITIVI`
--

INSERT INTO `DISPOSITIVI` (`nome`, `descrizione`, `stato`, `id_dispositivo`, `utente`, `tipo`) VALUES
('SATELLITE PRO', 'LAPTOP ', 'SPENTO', 3, 1, 2),
('XBOX ONE', 'CONSOLE', 'SPENTO', 4, 1, 2),
('OPPO A74', 'CELLULARE', 'SPENTO', 5, 1, 2),
('THINKCENTRE', 'PC', 'SPENTO', 6, 1, 1),
('SAMSUNG S20', 'CELLULARE', 'SPENTO', 7, 2, 2),
('XBOX 360', 'CONSOLE', 'SPENTO', 8, 2, 1);

--
-- Trigger `DISPOSITIVI`
--
DELIMITER $$
CREATE TRIGGER `TURN` AFTER UPDATE ON `DISPOSITIVI` FOR EACH ROW BEGIN
	DECLARE tempo1 float;
    DECLARE tempo2 float;
    DECLARE diff int;
    DECLARE end_ TIMESTAMP;
    DECLARE start_ TIMESTAMP;
	IF (NEW.stato = 'ACCESO') AND (OLD.stato != 'ACCESO') THEN
    INSERT INTO UTILIZZO (`start_use`, `dispositivo`, `utente`, `tipo`) VALUES (CURRENT_TIMESTAMP, NEW.id_dispositivo, NEW.utente, 1);
    ELSE IF (NEW.stato = 'SPENTO') AND (OLD.stato != 'SPENTO') AND (OLD.stato != "STANDBY") THEN
    UPDATE UTILIZZO SET `end_use` = CURRENT_TIMESTAMP WHERE id_utilizzo = (select id_utilizzo from UTILIZZO getLastRecord WHERE dispositivo = new.id_dispositivo ORDER BY id_utilizzo DESC LIMIT 1);
	set end_ = (select `end_use` from UTILIZZO getLastRecord WHERE dispositivo = new.id_dispositivo ORDER BY id_utilizzo DESC LIMIT 1);
    set start_ = (select `start_use` from UTILIZZO getLastRecord WHERE dispositivo = new.id_dispositivo ORDER BY id_utilizzo DESC LIMIT 1);
    
    IF(date(end_) != date(start_)) THEN 
    set diff = date(end_) - date(start_);
    set tempo1 = (HOUR(end_) + (MINUTE(end_)/60)) + (24 * diff);
    ELSE set tempo1 = HOUR(end_) + (MINUTE(end_)/60);
    END IF;
    
	set tempo2 = HOUR(start_) + (MINUTE(start_)/60);    
    IF tempo1 < tempo2 THEN
    set tempo2 = tempo2*-1;
    set tempo1 = tempo1*-1;
    END IF;
    UPDATE UTILIZZO SET `ore` = tempo1-tempo2 WHERE id_utilizzo = (select id_utilizzo from UTILIZZO getLastRecord WHERE dispositivo = new.id_dispositivo ORDER BY id_utilizzo DESC LIMIT 1);
    ELSE IF (NEW.stato = 'STANDBY') AND (OLD.stato != 'STANDBY') AND (OLD.stato != "SPENTO") THEN
	    UPDATE UTILIZZO SET `end_use` = CURRENT_TIMESTAMP WHERE id_utilizzo = (select id_utilizzo from UTILIZZO getLastRecord WHERE dispositivo = new.id_dispositivo ORDER BY id_utilizzo DESC LIMIT 1);
	set end_ = (select `end_use` from UTILIZZO getLastRecord WHERE dispositivo = new.id_dispositivo ORDER BY id_utilizzo DESC LIMIT 1);
    set start_ = (select `start_use` from UTILIZZO getLastRecord WHERE dispositivo = new.id_dispositivo ORDER BY id_utilizzo DESC LIMIT 1);
    
    IF(date(end_) != date(start_)) THEN 
    set diff = date(end_) - date(start_);
    set tempo1 = (HOUR(end_) + (MINUTE(end_)/60)) + (24 * diff);
    ELSE set tempo1 = HOUR(end_) + (MINUTE(end_)/60);
    END IF;
    
	set tempo2 = HOUR(start_) + (MINUTE(start_)/60);    
    IF tempo1 < tempo2 THEN
    set tempo2 = tempo2*-1;
    set tempo1 = tempo1*-1;
    END IF;
    UPDATE UTILIZZO SET `ore` = tempo1-tempo2 WHERE id_utilizzo = (select id_utilizzo from UTILIZZO getLastRecord WHERE dispositivo = new.id_dispositivo ORDER BY id_utilizzo DESC LIMIT 1);
    END IF;
    END IF;
    END IF;
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Struttura della tabella `TIPOLOGIA_DISPOSITIVO`
--

CREATE TABLE `TIPOLOGIA_DISPOSITIVO` (
  `nome` varchar(6) NOT NULL,
  `id_tipologia_d` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `TIPOLOGIA_DISPOSITIVO`
--

INSERT INTO `TIPOLOGIA_DISPOSITIVO` (`nome`, `id_tipologia_d`) VALUES
('FISSO', 1),
('MOBILE', 2);

-- --------------------------------------------------------

--
-- Struttura della tabella `TIPOLOGIA_UTILIZZO`
--

CREATE TABLE `TIPOLOGIA_UTILIZZO` (
  `nome` varchar(255) NOT NULL,
  `id_tipologia_u` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `TIPOLOGIA_UTILIZZO`
--

INSERT INTO `TIPOLOGIA_UTILIZZO` (`nome`, `id_tipologia_u`) VALUES
('LAVORATIVO', 1),
('LUDICO', 2),
('INFORMATIVO', 3);

-- --------------------------------------------------------

--
-- Struttura della tabella `UTENTI`
--

CREATE TABLE `UTENTI` (
  `nome` varchar(255) NOT NULL,
  `cognome` varchar(255) NOT NULL,
  `nickname` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `id_utente` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `UTENTI`
--

INSERT INTO `UTENTI` (`nome`, `cognome`, `nickname`, `password`, `id_utente`) VALUES
('Samuele', 'Cucuzza', 'samueleccz', 'PASSWORD1', 1),
('Giovanni', 'Ricci', 'GiovyRicci121', 'PASSWORD2', 2);

-- --------------------------------------------------------

--
-- Struttura della tabella `UTILIZZO`
--

CREATE TABLE `UTILIZZO` (
  `start_use` timestamp NULL DEFAULT NULL,
  `end_use` timestamp NULL DEFAULT '0000-00-00 00:00:00',
  `ore` float(100,2) DEFAULT NULL,
  `utente` int(11) NOT NULL,
  `dispositivo` int(11) NOT NULL,
  `tipo` int(11) NOT NULL,
  `id_utilizzo` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dump dei dati per la tabella `UTILIZZO`
--

INSERT INTO `UTILIZZO` (`start_use`, `end_use`, `ore`, `utente`, `dispositivo`, `tipo`, `id_utilizzo`) VALUES
('2023-02-09 18:10:52', '2023-02-27 18:11:23', 432.02, 1, 3, 1, 16),
('2023-02-27 10:12:46', '2023-02-27 18:13:55', 8.02, 1, 3, 1, 17),
('2023-02-27 09:12:53', '2023-02-27 18:13:58', 9.02, 1, 4, 1, 18),
('2023-02-27 09:00:24', '2023-02-27 18:18:16', 9.30, 1, 4, 1, 19),
('2023-02-27 05:00:24', '2023-02-27 18:18:19', 13.30, 1, 5, 1, 20),
('2023-02-27 15:00:24', '2023-02-27 18:18:22', 3.30, 1, 6, 1, 21),
('2023-02-27 17:18:54', '2023-02-27 18:20:31', 1.03, 1, 5, 1, 22),
('2023-02-27 04:20:02', '2023-02-27 18:20:34', 14.00, 1, 6, 1, 23),
('2023-02-27 13:19:06', '2023-02-27 18:20:27', 5.02, 1, 4, 1, 24),
('2023-02-27 11:30:08', '2023-02-27 18:20:23', 6.83, 1, 3, 1, 25),
('2023-02-27 18:23:43', '2023-02-27 18:24:01', 0.02, 1, 5, 1, 26),
('2023-02-27 18:58:20', '2023-02-27 19:00:25', 0.03, 2, 8, 1, 29),
('2023-02-27 18:58:24', '2023-02-27 19:00:21', 0.03, 2, 7, 1, 30);

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `DISPOSITIVI`
--
ALTER TABLE `DISPOSITIVI`
  ADD PRIMARY KEY (`id_dispositivo`,`utente`,`tipo`) USING BTREE,
  ADD KEY `utente_FK` (`utente`),
  ADD KEY `tipo_FK` (`tipo`);

--
-- Indici per le tabelle `TIPOLOGIA_DISPOSITIVO`
--
ALTER TABLE `TIPOLOGIA_DISPOSITIVO`
  ADD PRIMARY KEY (`id_tipologia_d`);

--
-- Indici per le tabelle `TIPOLOGIA_UTILIZZO`
--
ALTER TABLE `TIPOLOGIA_UTILIZZO`
  ADD PRIMARY KEY (`id_tipologia_u`);

--
-- Indici per le tabelle `UTENTI`
--
ALTER TABLE `UTENTI`
  ADD PRIMARY KEY (`id_utente`);

--
-- Indici per le tabelle `UTILIZZO`
--
ALTER TABLE `UTILIZZO`
  ADD PRIMARY KEY (`id_utilizzo`),
  ADD KEY `use_dispositivo_FK` (`dispositivo`),
  ADD KEY `use_tipo_FK` (`tipo`),
  ADD KEY `use_utente_FK` (`utente`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `DISPOSITIVI`
--
ALTER TABLE `DISPOSITIVI`
  MODIFY `id_dispositivo` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT per la tabella `TIPOLOGIA_DISPOSITIVO`
--
ALTER TABLE `TIPOLOGIA_DISPOSITIVO`
  MODIFY `id_tipologia_d` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT per la tabella `TIPOLOGIA_UTILIZZO`
--
ALTER TABLE `TIPOLOGIA_UTILIZZO`
  MODIFY `id_tipologia_u` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `UTENTI`
--
ALTER TABLE `UTENTI`
  MODIFY `id_utente` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT per la tabella `UTILIZZO`
--
ALTER TABLE `UTILIZZO`
  MODIFY `id_utilizzo` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;

--
-- Limiti per le tabelle scaricate
--

--
-- Limiti per la tabella `DISPOSITIVI`
--
ALTER TABLE `DISPOSITIVI`
  ADD CONSTRAINT `tipo_FK` FOREIGN KEY (`tipo`) REFERENCES `TIPOLOGIA_DISPOSITIVO` (`id_tipologia_d`),
  ADD CONSTRAINT `utente_FK` FOREIGN KEY (`utente`) REFERENCES `UTENTI` (`id_utente`);

--
-- Limiti per la tabella `UTILIZZO`
--
ALTER TABLE `UTILIZZO`
  ADD CONSTRAINT `use_dispositivo_FK` FOREIGN KEY (`dispositivo`) REFERENCES `DISPOSITIVI` (`id_dispositivo`),
  ADD CONSTRAINT `use_tipo_FK` FOREIGN KEY (`tipo`) REFERENCES `TIPOLOGIA_UTILIZZO` (`id_tipologia_u`),
  ADD CONSTRAINT `use_utente_FK` FOREIGN KEY (`utente`) REFERENCES `DISPOSITIVI` (`utente`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
