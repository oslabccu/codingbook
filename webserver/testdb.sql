-- phpMyAdmin SQL Dump
-- version 5.0.1
-- https://www.phpmyadmin.net/
--
-- 主機： db
-- 產生時間： 2020 年 05 月 13 日 03:14
-- 伺服器版本： 10.4.12-MariaDB-1:10.4.12+maria~bionic-log
-- PHP 版本： 7.4.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫： `testdb`
--

-- --------------------------------------------------------

--
-- 資料表結構 `click`
--

CREATE TABLE `click` (
  `time` timestamp NOT NULL DEFAULT current_timestamp(),
  `studentid` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- 資料表結構 `test`
--

CREATE TABLE `test` (
  `id` varchar(30) NOT NULL,
  `chName` varchar(30) NOT NULL,
  `school` varchar(30) NOT NULL,
  `department` varchar(30) NOT NULL,
  `schDept` varchar(30) NOT NULL,
  `deptLevel` varchar(30) NOT NULL,
  `studentID` varchar(30) NOT NULL,
  `examSchool` varchar(30) NOT NULL,
  `examPlace` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 資料表結構 `user`
--

CREATE TABLE `user` (
  `studentid` varchar(15) CHARACTER SET utf8 NOT NULL,
  `password` varchar(30) CHARACTER SET utf8 NOT NULL,
  `name` varchar(10) CHARACTER SET utf8 NOT NULL,
  `class` varchar(5) CHARACTER SET utf8 NOT NULL,
  `major` varchar(5) CHARACTER SET utf8 NOT NULL,
  `email` varchar(40) CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- 資料表結構 `userip`
--

CREATE TABLE `userip` (
  `studentid` varchar(15) CHARACTER SET utf8 NOT NULL,
  `ip` varchar(20) CHARACTER SET utf8 NOT NULL,
  `port` varchar(6) CHARACTER SET utf8 NOT NULL,
  `time` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- 已傾印資料表的索引
--

--
-- 資料表索引 `click`
--
ALTER TABLE `click`
  ADD PRIMARY KEY (`time`,`studentid`);

--
-- 資料表索引 `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`studentid`);

--
-- 資料表索引 `userip`
--
ALTER TABLE `userip`
  ADD PRIMARY KEY (`studentid`);

--
-- 已傾印資料表的限制式
--

--
-- 資料表的限制式 `userip`
--
ALTER TABLE `userip`
  ADD CONSTRAINT `userip_ibfk_1` FOREIGN KEY (`studentid`) REFERENCES `user` (`studentid`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
