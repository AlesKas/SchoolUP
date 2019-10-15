-- phpMyAdmin SQL Dump
-- version 4.2.11
-- http://www.phpmyadmin.net
--
-- Počítač: 127.0.0.1
-- Vytvořeno: Ned 03. kvě 2015, 19:11
-- Verze serveru: 5.6.21
-- Verze PHP: 5.6.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Databáze: `test`
--

-- --------------------------------------------------------

--
-- Struktura tabulky `menu`
--

CREATE TABLE IF NOT EXISTS `menu` (
`id` int(11) NOT NULL,
  `controller` varchar(100) COLLATE utf8_czech_ci NOT NULL,
  `value` varchar(100) COLLATE utf8_czech_ci NOT NULL
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `menu`
--

INSERT INTO `menu` (`id`, `controller`, `value`) VALUES
(1, 'page', 'Úvodní stránka'),
(2, 'users', 'Uživatelé'),
(3, 'contact', 'Kontakt');

-- --------------------------------------------------------

--
-- Struktura tabulky `studenti`
--

CREATE TABLE IF NOT EXISTS `studenti` (
`id` int(10) unsigned NOT NULL,
  `firstname` varchar(30) COLLATE utf8_czech_ci NOT NULL,
  `lastname` varchar(40) COLLATE utf8_czech_ci NOT NULL,
  `created` datetime NOT NULL
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `studenti`
--

INSERT INTO `studenti` (`id`, `firstname`, `lastname`, `created`) VALUES
(3, 'Tonda', 'Rákoska', '2015-05-03 19:10:25'),
(4, 'Monika', 'Plačková', '2015-05-03 19:10:58');

--
-- Klíče pro exportované tabulky
--

--
-- Klíče pro tabulku `menu`
--
ALTER TABLE `menu`
 ADD PRIMARY KEY (`id`);

--
-- Klíče pro tabulku `studenti`
--
ALTER TABLE `studenti`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pro tabulky
--

--
-- AUTO_INCREMENT pro tabulku `menu`
--
ALTER TABLE `menu`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT pro tabulku `studenti`
--
ALTER TABLE `studenti`
MODIFY `id` int(10) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
