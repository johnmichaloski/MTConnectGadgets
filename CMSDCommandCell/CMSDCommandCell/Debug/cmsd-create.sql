CREATE SCHEMA IF NOT EXISTS `Factory` DEFAULT CHARACTER SET latin1;
USE Factory;


DROP TABLE IF EXISTS `Factory`.Properties;
CREATE  TABLE IF NOT EXISTS `Factory`.Properties(
identifier  CHAR(255) NOT NULL,
name CHAR(255)  NOT NULL DEFAULT '',
value CHAR(255)NOT NULL DEFAULT '', 
units CHAR(255) NULL DEFAULT '',
description CHAR(255) NULL DEFAULT '',

PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Part
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Part;
CREATE  TABLE IF NOT EXISTS `Factory`.Part(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`name` VARCHAR(255) NULL DEFAULT '', 
`processplanidentifier` VARCHAR(255) NULL DEFAULT '', 
`width` VARCHAR(255) NULL DEFAULT '', 
`depth` VARCHAR(255) NULL DEFAULT '', 
`height` VARCHAR(255) NULL DEFAULT '', 
`sizeunits` VARCHAR(255) NULL DEFAULT '', 
`weight` VARCHAR(255) NULL DEFAULT '', 
`weightunits` VARCHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
`description` VARCHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Resource
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Resource;
CREATE  TABLE IF NOT EXISTS `Factory`.Resource(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`type` VARCHAR(255) NULL DEFAULT '', 
`mtbfid` VARCHAR(255) NULL DEFAULT '', 
`mttrid` VARCHAR(255) NULL DEFAULT '', 
`hourlyRate` VARCHAR(255) NULL DEFAULT '', 
`hourlyRateUnit` VARCHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
`description` VARCHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.ProcessPlan
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.ProcessPlan;
CREATE  TABLE IF NOT EXISTS `Factory`.ProcessPlan(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`partsProduced` CHAR(255) NULL DEFAULT '', 
`partsConsumed` CHAR(255) NULL DEFAULT '', 
`processIds` CHAR(255) NULL DEFAULT '', 
`steps` CHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Job
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Job;
CREATE  TABLE IF NOT EXISTS `Factory`.Job(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`name` VARCHAR(255) NULL DEFAULT '', 
`partIds` CHAR(255) NULL DEFAULT '', 
`partQuantity` CHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Schedule
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Schedule;
CREATE  TABLE IF NOT EXISTS `Factory`.Schedule(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`description` VARCHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Shift
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Shift;
CREATE  TABLE IF NOT EXISTS `Factory`.Shift(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`startTime` VARCHAR(255) NULL DEFAULT '', 
`duration` VARCHAR(255) NULL DEFAULT '', 
`applicableDay` VARCHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
`description` VARCHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Calendar
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Calendar;
CREATE  TABLE IF NOT EXISTS `Factory`.Calendar(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`shiftIds` CHAR(255) NULL DEFAULT '', 
`startdate` VARCHAR(255) NULL DEFAULT '', 
`enddate` VARCHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
`description` VARCHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Cell
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Cell;
CREATE  TABLE IF NOT EXISTS `Factory`.Cell(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`name` VARCHAR(255) NULL DEFAULT '', 
`type` VARCHAR(255) NULL DEFAULT '', 
`resourceIds` CHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
`description` VARCHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Process
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Process;
CREATE  TABLE IF NOT EXISTS `Factory`.Process(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`type` VARCHAR(255) NULL DEFAULT '', 
`resourcesRequired` CHAR(255) NULL DEFAULT '', 
`description` VARCHAR(255) NULL DEFAULT '', 
`repetitionCount` VARCHAR(255) NULL DEFAULT '', 
`machineProgramInformation` VARCHAR(255) NULL DEFAULT '', 
`operationTime_time` VARCHAR(255) NULL DEFAULT '', 
`operationTime_units` VARCHAR(255) NULL DEFAULT '', 
`setupTime_time` VARCHAR(255) NULL DEFAULT '', 
`setupTime_units` VARCHAR(255) NULL DEFAULT '', 
`partsProducedId` CHAR(255) NULL DEFAULT '', 
`partsProducedQuantity` VARCHAR(255) NULL DEFAULT '', 
`partsConsumedId` VARCHAR(255) NULL DEFAULT '', 
`partsConsumedQuantity` VARCHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Layout
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Layout;
CREATE  TABLE IF NOT EXISTS `Factory`.Layout(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`name` VARCHAR(255) NULL DEFAULT '', 
`associatedResource` VARCHAR(255) NULL DEFAULT '', 
`unit` VARCHAR(255) NULL DEFAULT '', 
`boundaryWidth` VARCHAR(255) NULL DEFAULT '', 
`boundaryDepth` VARCHAR(255) NULL DEFAULT '', 
`CoordinateSystem` VARCHAR(255) NULL DEFAULT '', 
`placementX` VARCHAR(255) NULL DEFAULT '', 
`placementY` VARCHAR(255) NULL DEFAULT '', 
`properties` CHAR(255) NULL DEFAULT '', 
`description` VARCHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- -----------------------------------------------------
-- Table `Factory`.Distribution
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Factory`.Distribution;
CREATE  TABLE IF NOT EXISTS `Factory`.Distribution(
`identifier` VARCHAR(255) NOT NULL DEFAULT '', 
`name` VARCHAR(255) NULL DEFAULT '', 
`distname` VARCHAR(255) NULL DEFAULT '', 
`units` VARCHAR(255) NULL DEFAULT '', 
`name1` VARCHAR(255) NULL DEFAULT '', 
`value1` VARCHAR(255) NULL DEFAULT '', 
`name2` VARCHAR(255) NULL DEFAULT '', 
`value2` VARCHAR(255) NULL DEFAULT '', 
`name3` VARCHAR(255) NULL DEFAULT '', 
`value3` VARCHAR(255) NULL DEFAULT '', 
PRIMARY KEY (`identifier`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
