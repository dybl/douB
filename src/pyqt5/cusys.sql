/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE DATABASE IF NOT EXISTS `cusys` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `cusys`;

CREATE TABLE IF NOT EXISTS `admin` (
  `username` char(100) NOT NULL,
  `password` char(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
INSERT INTO `admin` (`username`, `password`) VALUES
	('dev', 'test'),
	('me', '1234');
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;

CREATE TABLE IF NOT EXISTS `cuinfo` (
  `name` varchar(255) NOT NULL,
  `age` char(50) NOT NULL,
  `num` char(50) NOT NULL,
  `oc` char(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*!40000 ALTER TABLE `cuinfo` DISABLE KEYS */;
INSERT INTO `cuinfo` (`name`, `age`, `num`, `oc`) VALUES
	('aa', '20', '11611910001', 'SoftwareEngineer'),
	('bb', '20', '11611910002', 'SoftwareEngineer'),
	('陈磊', '227929', '18921256776', 'Engineer'),
	('郭斌', '227870', '18921256763', 'Engineer'),
	('薛卫良', '227871', '18921246763', 'Engineer'),
	('cc', '20', '11611910003', 'SoftwareEngineer'),
	('dd', '20', '11611910004', 'SoftwareEngineer'),
	('ee', '20', '11611910005', 'SoftwareEngineer'),
	('ff', '20', '11611910006', 'SoftwareEngineer'),
	('徐盟', '226946', '18921256829', 'Engineer'),
	('徐洪正', '227065', '15261627896', 'Engineer'),
	('孙相忠', '227066', '15261627895', 'Engineer'),
	('杨军健', '226848', '18921256083', 'Engineer'),
	('朱劲冬', '226498', '18921256090', 'Engineer'),
	('gg', '19', '11611910007', 'SoftwareEngineer'),
	('hh', '21', '11611910008', 'HardwareEngineer'),
	('ii', '21', '11611910009', 'Analysts'),
	('jj', '21', '11611910010', 'SoftwareEngineer'),
	('周峰', '227907', '18921256819', 'Engineer'),
	('吴宁', '227427', '18921256827', 'Engineer'),
	('陆国胜', '227905', '18921256818', 'Engineer'),
	('薛刚达', '227856', '18921256817', 'Engineer'),
	('kk', '19', '11611910011', 'SoftwareEngineer'),
	('ll', '21', '11611910012', 'HardwareEngineer'),
	('mm', '21', '11611910013', 'SoftwareEngineer'),
	('nn', '20', '11611910014', 'Designer'),
	('oo', '21', '11611910015', 'SoftwareEngineer'),
	('pp', '21', '11611910016', 'SoftwareEngineer'),
	('qq', '21', '11611910017', 'SoftwareEngineer'),
	('rr', '20', '11611910018', 'TestEngineer'),
	('ss', '21', '11611910019', 'SoftwareEngineer'),
	('tt', '21', '11611910020', 'SoftwareEngineer'),
	('楼华军', '226432', '18921256089', 'Engineer'),
	('许晓冬', '227878', '18921256768', 'Engineer'),
	('夏克俭', '226837', '18921256766', 'Engineer'),
	('叶正泉', '227871', '18921256762', 'Engineer'),
	('uu', '18', '11611910021', 'HardwareEngineer'),
	('vv', '21', '11611910022', 'HardwareEngineer'),
	('ww', '22', '11611910023', 'SoftwareEngineer'),
	('xx', '21', '11611910024', 'SoftwareEngineer'),
	('yy', '21', '11611910025', 'SoftwareEngineer'),
	('郁军丰', '227879', '18921256769', 'Engineer'),
	('赵心刚', '227872', '18921256765', 'Engineer');
/*!40000 ALTER TABLE `cuinfo` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
