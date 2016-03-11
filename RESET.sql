CREATE DATABASE  IF NOT EXISTS `PWS` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `PWS`;
-- MySQL dump 10.13  Distrib 5.6.19, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: PWS
-- ------------------------------------------------------
-- Server version	5.6.19-1~exp1ubuntu2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `status_household`
--

DROP TABLE IF EXISTS `status_household`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `status_household` (
  `idUser` int(11) NOT NULL AUTO_INCREMENT,
  `HouseholdName` varchar(45) DEFAULT NULL,
  `Balance` int(11) DEFAULT '0',
  `Lock` int(11) DEFAULT '0',
  `Status` int(11) DEFAULT '0',
  `Store` int(11) NOT NULL DEFAULT '0',
  `Shutdown` int(11) NOT NULL DEFAULT '0',
  `idAppServer` int(8) NOT NULL DEFAULT '0',
  `idEncrypt` binary(4) DEFAULT NULL,
  `is_source` tinyint(1)NOT NULL DEFAULT '0',
  `source_id` int(11)DEFAULT NULL,
  PRIMARY KEY (`idUser`),
  UNIQUE KEY `HouseholdName` (`HouseholdName`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `transaction_paymentcenter`
--

DROP TABLE IF EXISTS `transaction_paymentcenter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transaction_paymentcenter` (
  `idUser` int(11) NOT NULL,
  `idTransaction` int(11) NOT NULL AUTO_INCREMENT,
  `AmountPaid` int(11) DEFAULT NULL,
  `idHousehold` int(11) DEFAULT NULL,
  `DateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`idTransaction`,`idUser`)
) ENGINE=InnoDB AUTO_INCREMENT=104 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
--
-- Table structure for table `transactions_household`
--

DROP TABLE IF EXISTS `transactions_household`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transactions_household` (
  `idUser` int(11) NOT NULL,
  `idTransaction` int(11) NOT NULL,
  `AmountPaid` int(11) DEFAULT NULL,
  `idPaymentCenter` int(11) DEFAULT NULL,
  `DateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`idTransaction`,`idUser`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transactions_household`
--

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `idUser` int(11) NOT NULL AUTO_INCREMENT,
  `idHousehold` int(11) NOT NULL,
  `Username` varchar(45) DEFAULT NULL,
  `Password` varchar(45) DEFAULT NULL,
  `Address` varchar(45) DEFAULT NULL,
  `UserType` int(11) DEFAULT NULL,
  `Email` varchar(200) DEFAULT NULL,
  `LastName` varchar(100) NOT NULL,
  `FirstName` varchar(100) NOT NULL,
  `x_y` varchar(9) NOT NULL,
  PRIMARY KEY (`idUser`),
  UNIQUE KEY `idUser_UNIQUE` (`idUser`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (22,0,'admin','21232f297a57a5a743894a0e4a801fc3','admin',1,'admin@yahoo.com','','',''),
(23,0,'payment','f83c2a85d972a89238f31296c63f0dbc','University of San Carlos, Cabancalan',2,'payment@yahoo.com','Payments','Paymentss',''),
(24, 25, 'source1', '011a04639b919a7ef99bdc38f65d2ee8', 'source1', 3, 'source@yahoo.com', 'Source', '1', '0600-0250'),
(25, 26, 'checkpoint1', 'd35c873e575816f824d37c1ac0dc6c28', 'checkpoint1', 3, 'checkpoint1@yahoo.com', 'Checkpoint', '1', '0450-0250'),
(26, 27, 'earl', 'f44152ed4438e5c60ffd0d5e67f7aae7', 'Brgy. Lagtang Talisay City', 3, 'earljohn_004@yahoo.com', 'Abaquita', 'Earl John', '0200-0085'),
(27, 28, 'clark', '4019a6a75a58f96cfb6a73a883c2f5ba', 'Brgy. Tisa Labangon Cebu City', 3, 'clarksherwin@gmail.com', 'Mantilla', 'Clark Sherwin', '0200-0400');
UNLOCK TABLES;


LOCK TABLES `status_household` WRITE;
INSERT INTO `status_household` (`idUser`, `HouseholdName`, `Balance`, `Lock`, `Status`, `Store`, `Shutdown`, `idAppServer`, `idEncrypt`, `is_source`, `source_id`) VALUES
(25, 'source1', 2000, 0, 0, 0, 0, 10, 0x01010118, 1, NULL),
(26, 'checkpoint1', 2000, 0, 0, 0, 0, 10, 0x01010119, 1, 25),
(27, 'earl', 400, 0, 0, 0, 0, 10, 0x0101011a, 0, 26),
(28, 'clark', 400, 0, 0, 0, 0, 10, 0x0101011b, 0, 26);
UNLOCK TABLES;


--
-- Table structure for table `waterusage_household`
--

DROP TABLE IF EXISTS `waterusage_household`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `waterusage_household` (
  `idUser` int(11) NOT NULL,
  `idWaterUsage` int(11) NOT NULL AUTO_INCREMENT,
  `Volume` double DEFAULT '0',
  `DateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`idWaterUsage`,`idUser`)
) ENGINE=InnoDB AUTO_INCREMENT=113 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `waterusage_household`
--

/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-12-28 21:28:09
