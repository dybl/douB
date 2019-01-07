-- MySQL dump 10.13  Distrib 5.5.46, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: library
-- ------------------------------------------------------
-- Server version	5.5.46-0ubuntu0.14.04.2

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
-- Table structure for table `admin`
--

DROP TABLE IF EXISTS `admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `admin` (
  `ano` varchar(50) DEFAULT NULL,
  `aname` varchar(20) DEFAULT NULL,
  `asex` char(3) DEFAULT '密',
  `akey` varchar(20) DEFAULT NULL,
  `atel` varchar(15) DEFAULT NULL,
  `acareer` varchar(20) DEFAULT NULL,
  UNIQUE KEY `uk_ano` (`ano`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin`
--

LOCK TABLES `admin` WRITE;
/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
INSERT INTO `admin` VALUES ('0000','root','','0000','0000','root');
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 trigger asex_rule after insert 
on admin for each row
begin
    if ((select admin.asex from admin, new 
    where admin.ano = new.ano) not in ('男', '女', '密')) then
        delete from admin where asex = new.asex;
    end if;
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `book`
--

DROP TABLE IF EXISTS `book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `book` (
  `bno` char(7) NOT NULL,
  `bname` varchar(50) DEFAULT NULL,
  `btno` varchar(50) DEFAULT NULL,
  `bprint` varchar(50) DEFAULT NULL,
  `bauthor` varchar(50) DEFAULT NULL,
  `bnum` int(11) DEFAULT NULL,
  `ano` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`bno`),
  UNIQUE KEY `uk_bno` (`bno`),
  KEY `book_index` (`bno`),
  KEY `bano` (`ano`),
  CONSTRAINT `bano` FOREIGN KEY (`ano`) REFERENCES `admin` (`ano`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `book`
--

LOCK TABLES `book` WRITE;
/*!40000 ALTER TABLE `book` DISABLE KEYS */;
INSERT INTO `book` VALUES ('0000','ROS机器人程序设计','TP','机械工业出版社','Aaron Martinez',5,'0000'),('0001','开源机器人操作系统ROS','TP','科学出版社','张建伟',3,'0000'),('0002','CPU自制入门','TP','人民邮电出版社','水头一寿',3,'0000'),('0003','自己动手写CPU','TP','电子工业出版社','雷思磊',4,'0000'),('0004','自己设计制作CPU与单片机','TP','人民邮电出版社','姜咏江',4,'0000'),('0005','Linux高级程序设计','TP','高等教育出版社','罗怡桂',4,'0000'),('0006','Linux就是这个范儿','TP','人民邮电出版社','赵鑫磊',4,'0000'),('0007','Linux C编程从入门到精通','TP','人民邮电出版社','宋磊',4,'0000'),('0008','Linux内核设计与实现','TP','机械工业出版社','Robert Love',5,'0000'),('0009','Linux环境下Qt4图形界面与MySQL编程','TP','机械工业出版社','邱铁',5,'0000'),('0010','UNIX环境高级编程','TP','人民邮电出版社','W.Richard Stevens',3,'0000'),('0011','UNIX网络程序设计','TP','科学出版社','吴念',4,'0000'),('0012','C++ Primer中文版','TP','电子工业出版社','Lippman, Stanley B',5,'0000'),('0013','C专家编程','TP','人民邮电出版社','Peter Van der Linden',2,'0000'),('0014','Verilog数字系统设计教程','TP','北京航空航天大学出版社','夏宇闻',4,'0000');
/*!40000 ALTER TABLE `book` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `borrow`
--

DROP TABLE IF EXISTS `borrow`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `borrow` (
  `rno` varchar(20) DEFAULT NULL,
  `bno` char(7) DEFAULT NULL,
  `sdate` date DEFAULT NULL,
  `edate` date DEFAULT NULL,
  `rdate` date DEFAULT NULL,
  `flag` varchar(20) DEFAULT NULL,
  KEY `bno` (`bno`),
  KEY `borrow_index` (`rno`),
  CONSTRAINT `bno` FOREIGN KEY (`bno`) REFERENCES `book` (`bno`),
  CONSTRAINT `rno` FOREIGN KEY (`rno`) REFERENCES `reader` (`rno`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `borrow`
--

LOCK TABLES `borrow` WRITE;
/*!40000 ALTER TABLE `borrow` DISABLE KEYS */;
/*!40000 ALTER TABLE `borrow` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 trigger borrow_return after insert
on borrow for each row
begin
    if ((select min(borrow.edate) from borrow
    where borrow.rno = new.rno) < current_date()) then
        delete from borrow where edate = new.edate;
    end if;
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `borrow_view`
--

DROP TABLE IF EXISTS `borrow_view`;
/*!50001 DROP VIEW IF EXISTS `borrow_view`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `borrow_view` (
  `rno` tinyint NOT NULL,
  `bno` tinyint NOT NULL,
  `bname` tinyint NOT NULL,
  `bprint` tinyint NOT NULL,
  `bauthor` tinyint NOT NULL,
  `sdate` tinyint NOT NULL,
  `rdate` tinyint NOT NULL
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `reader`
--

DROP TABLE IF EXISTS `reader`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `reader` (
  `rno` varchar(20) NOT NULL,
  `rname` varchar(20) DEFAULT NULL,
  `rkey` varchar(20) DEFAULT NULL,
  `rtel` varchar(15) DEFAULT NULL,
  `rsex` char(3) DEFAULT '密',
  `ano` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`rno`),
  UNIQUE KEY `uk_rno` (`rno`),
  KEY `reader_index` (`rno`),
  KEY `rano` (`ano`),
  CONSTRAINT `rano` FOREIGN KEY (`ano`) REFERENCES `admin` (`ano`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reader`
--

LOCK TABLES `reader` WRITE;
/*!40000 ALTER TABLE `reader` DISABLE KEYS */;
INSERT INTO `reader` VALUES ('0000','李刚','1000','17392817495','男','0000'),('0001','张伟','1001','13528576392','男','0000'),('0002','王芳','1002','13223050038','女','0000'),('0003','李伟','1003','18946937338','男','0000'),('0004','张丽','1004','18893392735','女','0000'),('0005','李强','1005','19387492324','男','0000'),('0006','王磊','1006','18392893823','男','0000'),('0007','刘洋','1007','12338978937','男','0000'),('0008','王军','1008','18383268423','男','0000'),('0009','张杰','1009','19171717163','男','0000'),('0010','黄博','1010','18726251534','男','0000'),('0011','赵婷','1011','16348792981','女','0000'),('0012','杨广','1012','13627181782','男','0000'),('0013','梦嫣','1013','18763831834','女','0000'),('0014','孙悦','1014','18733616370','男','0000');
/*!40000 ALTER TABLE `reader` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 trigger rsex_rule after insert 
on reader for each row
begin
    if ((select reader.rsex from reader
    where reader.rno = new.rno) not in ('男', '女', '密')) then
        delete from reader where rsex = new.rsex;
    end if;
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `type`
--

DROP TABLE IF EXISTS `type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `type` (
  `tno` char(3) DEFAULT NULL,
  `tname` varchar(20) DEFAULT NULL,
  `tloc` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `type`
--

LOCK TABLES `type` WRITE;
/*!40000 ALTER TABLE `type` DISABLE KEYS */;
INSERT INTO `type` VALUES ('T','工业技术','图书馆四层'),('TP','计算机技术','图书馆四层'),('TN','电子技术','图书馆四层'),('TM','电工技术','图书馆四层'),('TK','能源与动力工程','图书馆四层'),('TH','机械仪表工业','图书馆四层'),('TG','金属工艺','图书馆四层'),('TB','一般工业技术','图书馆四层'),('TQ','化学工业','图书馆四层'),('TU','建筑科学','图书馆四层'),('TV','水利工程','图书馆四层'),('U','交通运输','图书馆四层'),('V','航空航天','图书馆四层'),('X','环境科学','图书馆四层'),('M','科技工具书','图书馆四层'),('H','语言文字','图书馆三层'),('N','自然科学总论','图书馆三层'),('O','数理科学','图书馆三层'),('P','天文学','图书馆三层'),('Q','生理科学','图书馆三层'),('R','医药卫生','图书馆三层'),('S','农业科学','图书馆三层');
/*!40000 ALTER TABLE `type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Final view structure for view `borrow_view`
--

/*!50001 DROP TABLE IF EXISTS `borrow_view`*/;
/*!50001 DROP VIEW IF EXISTS `borrow_view`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `borrow_view` AS select `borrow`.`rno` AS `rno`,`book`.`bno` AS `bno`,`book`.`bname` AS `bname`,`book`.`bprint` AS `bprint`,`book`.`bauthor` AS `bauthor`,`borrow`.`sdate` AS `sdate`,`borrow`.`rdate` AS `rdate` from (`book` join `borrow`) where (`book`.`bno` = `borrow`.`bno`) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-12-11 16:56:59
