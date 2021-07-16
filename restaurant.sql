-- phpMyAdmin SQL Dump
-- version 5.0.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jul 16, 2021 at 09:25 PM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.4.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `restaurant`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `AdminID` int(10) NOT NULL,
  `AdminUsername` varchar(20) NOT NULL,
  `AdminPw` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`AdminID`, `AdminUsername`, `AdminPw`) VALUES
(1, 'Admin', 'admin123');

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `CustID` int(10) NOT NULL,
  `CustPhone` int(10) NOT NULL,
  `CustAddress` varchar(50) NOT NULL,
  `CustUsername` varchar(10) NOT NULL,
  `CustPw` varchar(10) NOT NULL,
  `CustName` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`CustID`, `CustPhone`, `CustAddress`, `CustUsername`, `CustPw`, `CustName`) VALUES
(9, 165217006, '75, Kg Sg Ramal Luar, 43000, Kajang, Selangor', 'Ally776', 'ally776', 'Alicia'),
(10, 196787991, 'No 17, 449-B, Jalan 5, 17499, Kl', 'Moo2', 'moomoo222', 'Moosy'),
(11, 165204006, '36, Persiaran Bekor 17, Taman Pertama, 30100, ', 'J123', 'jass1234', 'Jassvine'),
(12, 135634612, '9, Jalan USJ, Taman Seafield Jaya, 46700', 'LukeR87', 'luke909', 'Luke Ryan'),
(13, 12576110, '3A, Plaza Mont Kiara, Block C-2, Jalan 1/70C, 5048', 'Alexaaa99', 'ally0101', 'Alexa '),
(14, 176534781, 'Jalan SS 21/39, Damansara Utama, 47400', 'tk98', 'w1898', 'Taasha K'),
(15, 175207009, 'new yorks', 'mira', 'mira15', 'Amirah'),
(20, 175217006, 'Deltroid, Conneticut', 'maya', 'maya20', 'Maya'),
(22, 176253890, 'Puchong indah', 'logi2', 'logi2', 'Logi'),
(31, 98766543, 'hulu perak langat, kl', 'rosh', 'rosh31', 'rosh'),
(32, 19872636, 'rawang, selangor', 'renu', 'renu', 'renu'),
(45, 175279006, '36, first agrden, ipoh', 'oli5', 'oli5', 'Olivia'),
(86, 729339, 'johor', 'resh', 'resh', 'esh');

-- --------------------------------------------------------

--
-- Table structure for table `menu`
--

CREATE TABLE `menu` (
  `MenuID` int(10) NOT NULL,
  `MenuName` varchar(50) NOT NULL,
  `MenuDescription` varchar(100) NOT NULL,
  `MenuPrice` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `menu`
--

INSERT INTO `menu` (`MenuID`, `MenuName`, `MenuDescription`, `MenuPrice`) VALUES
(2, 'Nachos Chili Con', 'Starters', '19.00'),
(3, 'Calamari Rings', 'Starters', '19.00'),
(4, 'Spicy Chicken Wings', 'Starters', '15.00'),
(5, 'DEVIL\'S CURRY', 'Local Fav', '13.00'),
(6, 'SEA BASS CURRY', 'Local Fav', '13.00'),
(7, 'CHILLI PADI CHICKEN', 'Local Fav', '15.00'),
(8, 'PASTA Oglio Olio', 'Pasta', '17.00'),
(9, 'PASTA Carbonara', 'Pasta', '13.00'),
(10, 'Spicy Bacon Pizza', 'Pizza', '17.00'),
(11, 'Molten Lava', 'Dessert', '10.00'),
(12, 'Ice cream', 'DESSERT', '10.00'),
(28, 'Orange', 'FRUIT', '2.00');

-- --------------------------------------------------------

--
-- Table structure for table `ordering`
--

CREATE TABLE `ordering` (
  `OrderID` int(11) NOT NULL,
  `OrderDate` date NOT NULL,
  `CustID` int(11) NOT NULL,
  `Quantity` int(11) NOT NULL,
  `MenuID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `ordering`
--

INSERT INTO `ordering` (`OrderID`, `OrderDate`, `CustID`, `Quantity`, `MenuID`) VALUES
(8, '1999-08-03', 10, 2, 10),
(21, '2021-01-18', 15, 2, 12),
(23, '2021-01-09', 20, 3, 8),
(26, '2021-01-18', 32, 3, 7),
(28, '2021-01-18', 10, 1, 11),
(29, '2021-01-09', 10, 2, 28),
(31, '2021-01-19', 45, 3, 2);

-- --------------------------------------------------------

--
-- Table structure for table `rate`
--

CREATE TABLE `rate` (
  `ID` int(11) NOT NULL,
  `rating` int(10) NOT NULL,
  `comments` varchar(10000) NOT NULL,
  `CustID` int(11) NOT NULL,
  `AdminID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `rate`
--

INSERT INTO `rate` (`ID`, `rating`, `comments`, `CustID`, `AdminID`) VALUES
(2, 3, 'good. fast.', 10, 1),
(5, 3, 'good', 10, 1),
(6, 5, 'good!', 6, 1),
(8, 5, 'great!', 17, 1),
(9, 4, 'good.', 17, 1),
(10, 4, 'none', 10, 1),
(11, 5, '-', 10, 1),
(12, 1, '-', 10, 1),
(14, 3, 'good', 10, 1),
(15, 5, 'good!', 44, 1),
(16, 2, 'not too great', 88, 1),
(17, 4, 'ok', 90, 1),
(19, 3, '-', 20, 1),
(20, 4, 'average', 22, 1),
(21, 5, 'good', 32, 1),
(22, 2, '-', 10, 1),
(23, 4, 'none', 45, 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`AdminID`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`CustID`),
  ADD UNIQUE KEY `CustID` (`CustID`);

--
-- Indexes for table `menu`
--
ALTER TABLE `menu`
  ADD PRIMARY KEY (`MenuID`);

--
-- Indexes for table `ordering`
--
ALTER TABLE `ordering`
  ADD PRIMARY KEY (`OrderID`),
  ADD UNIQUE KEY `OrderID` (`OrderID`),
  ADD KEY `CustID` (`CustID`),
  ADD KEY `MenuID` (`MenuID`);

--
-- Indexes for table `rate`
--
ALTER TABLE `rate`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `AdminID` (`AdminID`),
  ADD KEY `CustID` (`CustID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `AdminID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `menu`
--
ALTER TABLE `menu`
  MODIFY `MenuID` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=30;

--
-- AUTO_INCREMENT for table `ordering`
--
ALTER TABLE `ordering`
  MODIFY `OrderID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=32;

--
-- AUTO_INCREMENT for table `rate`
--
ALTER TABLE `rate`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=24;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `ordering`
--
ALTER TABLE `ordering`
  ADD CONSTRAINT `ordering_ibfk_1` FOREIGN KEY (`CustID`) REFERENCES `customer` (`CustID`),
  ADD CONSTRAINT `ordering_ibfk_2` FOREIGN KEY (`MenuID`) REFERENCES `menu` (`MenuID`);

--
-- Constraints for table `rate`
--
ALTER TABLE `rate`
  ADD CONSTRAINT `rate_ibfk_1` FOREIGN KEY (`AdminID`) REFERENCES `admin` (`AdminID`),
  ADD CONSTRAINT `rate_ibfk_2` FOREIGN KEY (`CustID`) REFERENCES `customer` (`CustID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
