-- phpMyAdmin SQL Dump
-- version 4.8.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Creato il: Giu 18, 2021 alle 10:48
-- Versione del server: 10.0.28-MariaDB-0+deb8u1
-- Versione PHP: 7.0.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `borsellino`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `borsellino_prodotto`
--

CREATE TABLE `borsellino_prodotto` (
  `prodotto` varchar(255) NOT NULL,
  `prezzo` decimal(11,2) NOT NULL,
  `disponibile` int(1) NOT NULL,
  `id_prodotto` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `borsellino_prodotto`
--

INSERT INTO `borsellino_prodotto` (`prodotto`, `prezzo`, `disponibile`, `id_prodotto`) VALUES
('Ricarica', '0.00', 1, 3),
('Cornetto', '1.00', 1, 14),
('CaffÃ¨', '0.80', 1, 15),
('Brioches', '0.70', 1, 16),
('Gelato', '1.70', 1, 17),
('Pizza', '10.00', 1, 19);

-- --------------------------------------------------------

--
-- Struttura della tabella `borsellino_transazione`
--

CREATE TABLE `borsellino_transazione` (
  `tipologia` int(1) NOT NULL,
  `data_ora` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `importo` decimal(11,2) NOT NULL,
  `utente` int(11) NOT NULL,
  `operatore` int(11) NOT NULL,
  `prod` int(11) DEFAULT NULL,
  `id_transazione` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `borsellino_transazione`
--

INSERT INTO `borsellino_transazione` (`tipologia`, `data_ora`, `importo`, `utente`, `operatore`, `prod`, `id_transazione`) VALUES
(0, '2021-06-12 16:19:21', '100.00', 24, 24, 3, 59),
(0, '2021-06-12 16:19:26', '100.00', 32, 24, 3, 60),
(0, '2021-06-12 16:19:31', '100.00', 33, 24, 3, 61),
(1, '2021-06-12 17:27:47', '-1.00', 0, 32, 14, 64),
(1, '2021-06-12 17:31:12', '-1.00', 33, 32, 14, 65),
(1, '2021-06-12 17:45:41', '0.00', 33, 32, 14, 66),
(1, '2021-06-12 17:45:47', '-1.00', 33, 32, 14, 67),
(1, '2021-06-12 18:14:01', '-0.70', 33, 32, 16, 68),
(0, '2021-06-12 18:18:03', '10.00', 33, 24, 3, 69),
(0, '2021-06-12 18:28:34', '100.00', 40, 40, 3, 70),
(1, '2021-06-12 18:50:09', '-0.70', 33, 32, 15, 71),
(1, '2021-06-12 18:58:54', '-1.70', 40, 32, 17, 72),
(1, '2021-06-13 11:26:52', '-1.70', 33, 32, 17, 73),
(1, '2021-06-13 12:14:31', '-0.80', 33, 32, 15, 74),
(1, '2021-06-13 12:30:11', '-0.70', 40, 32, 16, 75),
(1, '2021-06-14 15:00:01', '-1.70', 40, 32, 17, 76),
(1, '2021-06-14 15:57:54', '-0.80', 40, 32, 15, 77),
(0, '2021-06-14 17:38:35', '10.00', 33, 40, 3, 78),
(1, '2021-06-14 17:43:56', '0.00', 0, 0, 0, 79),
(1, '2021-06-14 18:07:27', '-10.00', 32, 32, 18, 80),
(1, '2021-06-14 18:07:53', '-1.00', 40, 32, 17, 81),
(1, '2021-06-14 18:10:09', '-1.00', 33, 32, 18, 82),
(1, '2021-06-14 18:25:10', '0.00', 0, 0, 0, 83),
(0, '2021-06-14 18:26:54', '1.00', 32, 40, 3, 84),
(0, '2021-06-14 18:27:38', '1.00', 32, 40, 3, 85),
(0, '2021-06-14 18:27:51', '1.00', 32, 40, 3, 86),
(0, '2021-06-14 18:28:07', '2.00', 40, 40, 3, 87),
(0, '2021-06-14 18:28:55', '1.00', 40, 40, 3, 88),
(0, '2021-06-14 18:29:27', '0.00', 0, 40, 3, 89),
(0, '2021-06-14 18:30:08', '0.00', 0, 40, 3, 90),
(0, '2021-06-14 18:30:40', '0.00', 0, 40, 3, 91),
(0, '2021-06-14 18:30:58', '12.00', 33, 40, 3, 92),
(0, '2021-06-14 18:33:41', '0.00', 0, 40, 3, 93),
(0, '2021-06-14 18:33:54', '0.00', 0, 40, 3, 94),
(0, '2021-06-14 18:34:01', '0.00', 0, 40, 3, 95),
(0, '2021-06-14 18:34:16', '0.00', 0, 40, 3, 96),
(0, '2021-06-14 18:34:30', '0.00', 0, 40, 3, 97),
(0, '2021-06-14 18:34:33', '0.00', 0, 40, 3, 98),
(0, '2021-06-14 18:34:35', '0.00', 0, 40, 3, 99),
(0, '2021-06-14 18:34:37', '0.00', 0, 40, 3, 100),
(0, '2021-06-14 18:34:41', '0.00', 0, 40, 3, 101),
(0, '2021-06-14 18:34:57', '0.00', 0, 40, 3, 102),
(0, '2021-06-14 18:35:25', '20.00', 40, 40, 3, 103),
(0, '2021-06-14 18:38:36', '2.00', 40, 40, 3, 104),
(0, '2021-06-14 18:39:12', '1.00', 40, 40, 3, 105),
(0, '2021-06-14 18:39:24', '1.00', 40, 40, 3, 106),
(0, '2021-06-14 18:39:33', '1.00', 40, 40, 3, 107),
(0, '2021-06-14 18:40:06', '100.00', 40, 40, 3, 108),
(0, '2021-06-14 18:40:27', '-100.00', 40, 40, 3, 109),
(1, '2021-06-15 15:47:29', '0.00', 0, 0, 0, 110),
(0, '2021-06-15 16:13:46', '0.00', 0, 33, 3, 111),
(0, '2021-06-15 16:14:03', '10.00', 33, 33, 3, 112),
(0, '2021-06-15 16:19:10', '0.00', 0, 33, 3, 113),
(0, '2021-06-15 16:19:55', '10.00', 33, 33, 3, 114),
(0, '2021-06-15 16:21:33', '0.00', 0, 33, 3, 115),
(0, '2021-06-15 16:21:49', '0.00', 0, 33, 3, 116),
(0, '2021-06-15 16:21:59', '0.00', 0, 33, 3, 117),
(0, '2021-06-15 16:22:06', '0.00', 0, 33, 3, 118),
(0, '2021-06-15 16:23:43', '10.00', 33, 33, 3, 119),
(0, '2021-06-15 16:26:10', '0.00', 0, 33, 3, 120),
(0, '2021-06-15 16:26:22', '1.00', 33, 33, 3, 121),
(1, '2021-06-15 16:30:58', '0.00', 0, 0, 0, 122),
(1, '2021-06-15 16:31:03', '0.00', 0, 0, 0, 123),
(1, '2021-06-15 16:35:37', '10.00', 33, 24, 3, 124),
(1, '2021-06-15 16:40:11', '10.00', 33, 24, 3, 125),
(1, '2021-06-15 16:40:15', '10.00', 33, 24, 3, 126),
(1, '2021-06-15 16:40:18', '10.00', 33, 24, 3, 127),
(1, '2021-06-15 16:40:23', '-100.00', 33, 24, 3, 128),
(1, '2021-06-15 16:46:23', '0.00', 0, 24, 3, 129),
(1, '2021-06-15 16:47:22', '10.00', 33, 24, 14, 130),
(1, '2021-06-15 16:47:37', '10.00', 33, 24, 0, 131),
(1, '2021-06-15 16:47:46', '10.00', 33, 24, 0, 132),
(1, '2021-06-15 16:47:56', '10.00', 33, 24, 3, 133),
(1, '2021-06-15 16:55:40', '-1.00', 33, 24, 14, 134),
(1, '2021-06-16 14:30:40', '-2.00', 33, 24, 16, 135),
(1, '2021-06-16 22:17:34', '-1.00', 33, 24, 14, 136),
(1, '2021-06-16 22:17:55', '-1.00', 33, 24, 14, 137),
(1, '2021-06-17 16:26:00', '-0.80', 40, 32, 15, 138),
(1, '2021-06-17 16:45:40', '0.00', 32, 24, 18, 139),
(1, '2021-06-18 09:52:24', '-1.00', 40, 24, 14, 140),
(1, '2021-06-18 09:58:39', '-1.70', 40, 24, 17, 141),
(1, '2021-06-18 10:09:55', '-0.70', 40, 24, 16, 142),
(1, '2021-06-18 10:17:21', '-0.80', 40, 24, 15, 143),
(1, '2021-06-18 10:33:18', '-1.70', 33, 24, 17, 144);

-- --------------------------------------------------------

--
-- Struttura della tabella `borsellino_utenti`
--

CREATE TABLE `borsellino_utenti` (
  `nome` varchar(255) NOT NULL,
  `cognome` varchar(255) NOT NULL,
  `data_nascita` date NOT NULL,
  `telefono` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `livello` int(11) NOT NULL,
  `classe` varchar(255) DEFAULT NULL,
  `foto` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `id_utente` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `borsellino_utenti`
--

INSERT INTO `borsellino_utenti` (`nome`, `cognome`, `data_nascita`, `telefono`, `email`, `livello`, `classe`, `foto`, `password`, `id_utente`) VALUES
('Peppe', 'Tasca', '2001-10-05', '123456', 'peppetasca@gmail.com', 2, '5^C ITI', 'peppe.jpg', 'e10adc3949ba59abbe56e057f20f883e', 32),
('Omar', 'Mejri', '2021-04-28', '123456', '  omj@gmail.com', 3, '5^C ITI', 'utente.png', '202cb962ac59075b964b07152d234b70', 33),
('Samuele', 'Cucuzza', '2002-12-20', '3913908615', 's.cucuzza@outlook.com', 1, '5^C ITI', 'samuele.jpg', '7f522e54608e425dac997f8bf5c2efae', 40);

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `borsellino_prodotto`
--
ALTER TABLE `borsellino_prodotto`
  ADD PRIMARY KEY (`id_prodotto`);

--
-- Indici per le tabelle `borsellino_transazione`
--
ALTER TABLE `borsellino_transazione`
  ADD PRIMARY KEY (`id_transazione`),
  ADD KEY `alunno` (`utente`),
  ADD KEY `prod` (`prod`),
  ADD KEY `oper` (`operatore`);

--
-- Indici per le tabelle `borsellino_utenti`
--
ALTER TABLE `borsellino_utenti`
  ADD PRIMARY KEY (`id_utente`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `borsellino_prodotto`
--
ALTER TABLE `borsellino_prodotto`
  MODIFY `id_prodotto` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;

--
-- AUTO_INCREMENT per la tabella `borsellino_transazione`
--
ALTER TABLE `borsellino_transazione`
  MODIFY `id_transazione` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=145;

--
-- AUTO_INCREMENT per la tabella `borsellino_utenti`
--
ALTER TABLE `borsellino_utenti`
  MODIFY `id_utente` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=41;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
