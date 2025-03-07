-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: May 21, 2024 at 12:03 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `crossfit`
--

-- --------------------------------------------------------

--
-- Table structure for table `abonamente`
--

CREATE TABLE `abonamente` (
  `idab` int(11) NOT NULL,
  `nume` text NOT NULL,
  `tip` text NOT NULL,
  `descriere` text NOT NULL,
  `pret` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `abonamente`
--

INSERT INTO `abonamente` (`idab`, `nume`, `tip`, `descriere`, `pret`) VALUES
(9, 'KARATE Copii si Adulti', 'grup', 'Fii activ si invata sa te apere la C.S Shinobi\r\nL-V: 18.30-20.00', 130),
(10, 'Ninja Fitness', 'personal', 'Antrenamente intense, focus pe rezistență și agilitate\r\nS-D:20.00-21.00', 150),
(11, 'Abonamentul CrossFit VIP', 'personal', 'Antrenament personalizat de antrenori nostri pentru rezultate exceptionale.\r\n24/7-O intrare pe zi!', 250),
(12, 'Atletism', 'grup', 'Antrenamente intense pentru performante athletice de top.\r\nL-V: 15.00-17.00', 80),
(13, 'IGYM PASS', 'personal', 'Acces la toate activitatile prestate de IGym\r\n24/7', 600),
(14, 'GYM ', 'personal', 'Acces la sala de fitness IGym si la sauna din cadrul IGym.\r\n24/7- O intrare pe zi!', 100),
(15, 'IGYM POOL', 'grup', 'Acces la piscina IGym si la Jacuzzi din cadrul IGym.\r\nL-D:10.00-22.00', 160);

-- --------------------------------------------------------

--
-- Table structure for table `antrenori`
--

CREATE TABLE `antrenori` (
  `ida` int(11) NOT NULL,
  `nume` text NOT NULL,
  `varsta` date NOT NULL,
  `descriere` text NOT NULL,
  `spec` text NOT NULL,
  `cale` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `antrenori`
--

INSERT INTO `antrenori` (`ida`, `nume`, `varsta`, `descriere`, `spec`, `cale`) VALUES
(14, 'Brezuleanu Giuliano', '2005-06-27', '    Giuliano, un antrenor de karate și personal trainer de excepție, face parte din echipa IGym. \r\n\r\n    Cu o experiență de 12 ani în karate, el îmbină disciplina și determinarea artelor marțiale cu cunoștințele solide în fitness. Calm și perseverent, Giuliano te ghidează cu răbdare și încurajare către obiectivele tale de fitness. Generos și prietenos, creează un mediu de antrenament plin de energie pozitivă. Cu înțelegere profundă a anatomiei, te ajută să construiești un corp puternic și un stil de viață sănătos. \r\n\r\n     Cu Giuliano în echipa IGym, fiecare antrenament devine o călătorie de transformare personală și împlinire.', 'Personal/Karate Trainer', 'Poze\\Giuliano.jpg'),
(15, 'Ciobanu Calin', '2005-11-29', '   Kinetoterapeutul echipei IGym, este alaturi de clientii nostri pentru a creste calitatea vietii acestora, pentru a ameliora durerea si a aduce o stare generala de bine, prin miscare, kinetoterapie, gimnastica medicala precum si masaj.\n\n   Experienta dobandita in lucrul cu pacientii din sectiile de Neurologie, Reumatologie si chiar Terapie Intensiva i-a adus o mai buna intelegere in importanta care trebuie acordata miscarii, si ingrijirii functionalitatii propriului nostru corp precum si o rabdare si un calm natural, esentiale in lucrul in acest domeniu.\n\n   Intrat in lumea sportului de mic, mereu sociabil si implicat in activitati interactive este o prezenta mereu cu zambetul pe buze si stie foarte bine sa rezoneze cu copiii in lucrul pentru corectarea posturii cat si in sedintele de gimnastica medicala.', 'Personal Trainer/Kinetoterapeut', 'Poze\\Calin.jpg'),
(16, 'Brezuleanu Stefan', '2007-12-05', '    Stefan este un antrenor remote online specializat în calistenie și antrenament la domiciliu, membru al echipei IGym. Cu o pasiune arzătoare pentru fitness și o expertiză solidă în calisthenics, el oferă programe personalizate și motivație constantă pentru clienții săi. Prin intermediul sesiunilor online, Stefan îi îndrumă pe clienții săi să-și atingă obiectivele de fitness, indiferent de locație sau program. \r\n    Cu un accent deosebit pe tehnica corectă și progresul gradual, el îi ajută pe clienții săi să-și dezvolte forța, flexibilitatea și controlul corporalului. Energic și inspirațional, Stefan creează o atmosferă de antrenament motivantă și plină de entuziasm. Cu Stefan ca antrenor remote în echipa IGym, fiecare antrenament devine o oportunitate de a-ți transforma corpul și de a-ți îmbunătăți sănătatea și starea de bine.', 'Remote Trainer', 'Poze\\Stefan.jpg');

-- --------------------------------------------------------

--
-- Table structure for table `clienti`
--

CREATE TABLE `clienti` (
  `idc` int(11) NOT NULL,
  `nume` text NOT NULL,
  `datan` date NOT NULL,
  `telefon` text NOT NULL,
  `email` text NOT NULL,
  `parola` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `clienti`
--

INSERT INTO `clienti` (`idc`, `nume`, `datan`, `telefon`, `email`, `parola`) VALUES
(24, 'Gavriluţă Ionuţ', '2004-01-15', '0745406115', 'gavrilutaionut10@gmail.com', 'ionutpas'),
(25, 'Adi', '2004-05-27', '0736654990', 'adrian@gmail.com', 'adrianpas'),
(26, 'Brezuleanu Petru', '2005-06-27', '0771518956', 'brezuleanugiuliano@gmail.com', 'Giulianopas10'),
(27, 'Brezuleanu Petronel', '1954-05-26', '0748373085', 'giulianobrezuleanu@gmail.com', 'brezuleanupas10'),
(29, 'Ciobanu Andrei', '2005-11-28', '0742376133', 'andreiciobanu_23@gmail.com', 'acica');

-- --------------------------------------------------------

--
-- Table structure for table `evenimente`
--

CREATE TABLE `evenimente` (
  `ide` int(11) NOT NULL,
  `nume` text NOT NULL,
  `data` datetime NOT NULL,
  `descriere` text NOT NULL,
  `cale` text NOT NULL,
  `pret` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `evenimente`
--

INSERT INTO `evenimente` (`ide`, `nume`, `data`, `descriere`, `cale`, `pret`) VALUES
(18, 'Cupa Shinobi', '2024-05-26 10:00:00', 'Cupa Shinobi este un eveniment de prestigiu în lumea artelor marțiale.\r\nAduce împreună luptători talentați din diverse discipline.\r\nUnde își demonstrează abilitățile de a concura în fața unei audiențe entuziaste.', 'Poze\\C.S Shinobi.jpg', 30),
(19, 'Semi-Marathon Iasi', '2024-06-01 10:00:00', 'Semi-maratonul din Iași este o competiție de alergare pe distanțe medii.\r\nAceasta atrage alergători pasionați din întreaga regiune.\r\nEvenimentul oferă o oportunitate unică de a experimenta trasee pitorești în jurul orașului.\r\nTodata şi împărtășirea pasiunii pentru alergare cu alți participanți entuziaști.\r\nIGym partener oficial', 'Poze\\semi marathon iasi.jpg', 100),
(20, 'Concurs PowerLifting', '2024-05-14 18:00:00', 'Masoara-ti forta fi cel mai bun dintre cei mai buni.\r\nConcursul de powerlifting este o competiție intensă în care atleții își demonstrează puterea și \r\ndeterminarea ridicând greutăți impresionante în trei discipline: împins la piept, genuflexiuni \r\nși tracțiuni. Este un spectacol al forței brute și al concentrării mentale, atrăgând atenția \r\npublicului și a admiratorilor sportului din întreaga lume.\r\nInscriete acum la PowerLifting Contest by IGym', 'Poze\\contestgym.jpg', 30);

-- --------------------------------------------------------

--
-- Table structure for table `rezabonamente`
--

CREATE TABLE `rezabonamente` (
  `idra` int(11) NOT NULL,
  `idc` int(11) NOT NULL,
  `idab` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `rezabonamente`
--

INSERT INTO `rezabonamente` (`idra`, `idc`, `idab`) VALUES
(18, 21, 5),
(20, 22, 2),
(35, 20, 2),
(36, 20, 6),
(37, 20, 5),
(38, 26, 9),
(39, 26, 10),
(40, 26, 14),
(41, 24, 10),
(42, 24, 12),
(43, 24, 14),
(44, 27, 11),
(45, 27, 14),
(46, 25, 15),
(47, 29, 13);

-- --------------------------------------------------------

--
-- Table structure for table `rezevenimente`
--

CREATE TABLE `rezevenimente` (
  `idre` int(11) NOT NULL,
  `idc` int(11) NOT NULL,
  `ide` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `rezevenimente`
--

INSERT INTO `rezevenimente` (`idre`, `idc`, `ide`) VALUES
(25, 20, 16),
(26, 21, 9),
(27, 21, 16),
(28, 22, 9),
(29, 23, 9),
(30, 26, 18),
(31, 26, 20),
(32, 24, 19),
(33, 27, 19),
(34, 29, 18),
(35, 29, 19),
(36, 29, 20);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `abonamente`
--
ALTER TABLE `abonamente`
  ADD PRIMARY KEY (`idab`);

--
-- Indexes for table `antrenori`
--
ALTER TABLE `antrenori`
  ADD PRIMARY KEY (`ida`);

--
-- Indexes for table `clienti`
--
ALTER TABLE `clienti`
  ADD PRIMARY KEY (`idc`);

--
-- Indexes for table `evenimente`
--
ALTER TABLE `evenimente`
  ADD PRIMARY KEY (`ide`);

--
-- Indexes for table `rezabonamente`
--
ALTER TABLE `rezabonamente`
  ADD PRIMARY KEY (`idra`);

--
-- Indexes for table `rezevenimente`
--
ALTER TABLE `rezevenimente`
  ADD PRIMARY KEY (`idre`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `abonamente`
--
ALTER TABLE `abonamente`
  MODIFY `idab` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT for table `antrenori`
--
ALTER TABLE `antrenori`
  MODIFY `ida` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;

--
-- AUTO_INCREMENT for table `clienti`
--
ALTER TABLE `clienti`
  MODIFY `idc` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=30;

--
-- AUTO_INCREMENT for table `evenimente`
--
ALTER TABLE `evenimente`
  MODIFY `ide` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;

--
-- AUTO_INCREMENT for table `rezabonamente`
--
ALTER TABLE `rezabonamente`
  MODIFY `idra` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=48;

--
-- AUTO_INCREMENT for table `rezevenimente`
--
ALTER TABLE `rezevenimente`
  MODIFY `idre` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=37;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
