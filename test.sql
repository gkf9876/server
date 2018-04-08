/*
Navicat MySQL Data Transfer

Source Server         : 버추얼박스 우분투
Source Server Version : 50721
Source Host           : 192.168.56.101:3306
Source Database       : test

Target Server Type    : MYSQL
Target Server Version : 50721
File Encoding         : 65001

Date: 2018-03-17 15:53:40
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `chatting`
-- ----------------------------
DROP TABLE IF EXISTS `chatting`;
CREATE TABLE `chatting` (
  `idx` int(10) NOT NULL AUTO_INCREMENT,
  `inputdate` datetime NOT NULL,
  `name` varchar(50) NOT NULL DEFAULT '',
  `content` varchar(100) DEFAULT '',
  `field` varchar(100) DEFAULT '0',
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=294 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of chatting
-- ----------------------------
INSERT INTO `chatting` VALUES ('1', '2017-11-25 12:05:11', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('2', '2017-11-25 12:05:13', 'GKF1234', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('3', '2017-11-25 12:55:25', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('4', '2017-11-25 12:55:26', 'GKF1234', 'bb', '0');
INSERT INTO `chatting` VALUES ('5', '2017-11-25 23:17:43', 'GKF1234', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('6', '2017-11-25 23:18:48', 'GKF1234', 'zz', '0');
INSERT INTO `chatting` VALUES ('7', '2017-11-25 23:19:24', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('8', '2017-11-25 23:21:09', 'GKF1234', 'add', '0');
INSERT INTO `chatting` VALUES ('9', '2017-11-25 23:24:54', 'GKF1234', 'add', '0');
INSERT INTO `chatting` VALUES ('10', '2017-11-25 23:29:47', 'GKF1234', 'add', '0');
INSERT INTO `chatting` VALUES ('11', '2017-11-26 01:44:52', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('12', '2017-11-26 01:48:19', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('13', '2017-11-26 01:51:08', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('14', '2017-11-26 01:55:26', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('15', '2017-11-26 01:58:04', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('16', '2017-11-26 01:59:54', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('17', '2017-11-26 02:01:19', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('18', '2017-11-26 02:10:31', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('19', '2017-11-26 02:12:12', 'GKF1234', 'we’re', '0');
INSERT INTO `chatting` VALUES ('20', '2017-11-26 02:12:16', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('21', '2017-11-26 02:12:47', 'GKF1234', 'asde', '0');
INSERT INTO `chatting` VALUES ('22', '2017-11-26 02:12:51', 'GKF1234', 'fff', '0');
INSERT INTO `chatting` VALUES ('23', '2017-11-26 02:14:38', 'GKF1234', 'asde]', '0');
INSERT INTO `chatting` VALUES ('24', '2017-11-26 02:15:42', 'GKF1234', 'asde', '0');
INSERT INTO `chatting` VALUES ('25', '2017-11-26 02:18:37', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('26', '2017-11-26 02:18:59', 'GKF1234', 'qwe', '0');
INSERT INTO `chatting` VALUES ('27', '2017-11-26 02:19:04', 'GKF1234', 'dry', '0');
INSERT INTO `chatting` VALUES ('28', '2017-11-26 02:20:12', 'GKF1234', 'asde', '0');
INSERT INTO `chatting` VALUES ('29', '2017-11-26 02:20:15', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('30', '2017-11-26 02:20:18', 'GKF1234', 'we', '0');
INSERT INTO `chatting` VALUES ('31', '2017-11-26 02:21:08', 'GKF1234', 'asde', '0');
INSERT INTO `chatting` VALUES ('32', '2017-11-26 02:21:10', 'GKF1234', 'gggg', '0');
INSERT INTO `chatting` VALUES ('33', '2017-11-26 02:21:12', 'GKF1234', 'rrr', '0');
INSERT INTO `chatting` VALUES ('34', '2017-11-26 02:22:26', 'GKF1234', 'sss', '0');
INSERT INTO `chatting` VALUES ('35', '2017-11-26 02:22:29', 'GKF1234', 'zz', '0');
INSERT INTO `chatting` VALUES ('36', '2017-11-26 02:26:35', 'GKF9797', 'sd', '0');
INSERT INTO `chatting` VALUES ('37', '2017-11-26 02:26:41', 'GKF9797', 'aa', '0');
INSERT INTO `chatting` VALUES ('38', '2017-11-26 02:26:44', 'GKF9797', 'ff', '0');
INSERT INTO `chatting` VALUES ('39', '2017-11-26 02:26:57', 'GKF9797', 'zz', '0');
INSERT INTO `chatting` VALUES ('40', '2017-11-26 02:27:00', 'GKF9797', 'gg', '0');
INSERT INTO `chatting` VALUES ('41', '2017-11-26 02:49:05', 'GKF9876', 'asd', '0');
INSERT INTO `chatting` VALUES ('42', '2017-11-26 02:49:07', 'GKF9876', 'zz', '0');
INSERT INTO `chatting` VALUES ('43', '2017-11-26 02:49:10', 'GKF9876', '야임마', '0');
INSERT INTO `chatting` VALUES ('44', '2017-11-26 02:49:12', 'GKF9876', '들리냐', '0');
INSERT INTO `chatting` VALUES ('45', '2017-11-26 02:49:13', 'GKF9876', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('46', '2017-11-26 02:49:15', 'GKF9876', '굿', '0');
INSERT INTO `chatting` VALUES ('47', '2017-11-26 02:49:19', 'GKF1234', 'zz', '0');
INSERT INTO `chatting` VALUES ('48', '2017-11-26 02:49:24', 'GKF1234', '오케이', '0');
INSERT INTO `chatting` VALUES ('49', '2017-11-26 02:49:30', 'GKF1234', '잘 보인다', '0');
INSERT INTO `chatting` VALUES ('50', '2017-11-27 18:38:00', 'GKF1234', 'ss', '0');
INSERT INTO `chatting` VALUES ('51', '2017-11-27 18:38:03', 'GKF1234', 'fv', '0');
INSERT INTO `chatting` VALUES ('52', '2017-11-27 18:38:11', 'GKF1234', 'cv', '0');
INSERT INTO `chatting` VALUES ('53', '2017-11-30 14:12:04', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('54', '2017-11-30 14:12:06', 'GKF1234', '굿', '0');
INSERT INTO `chatting` VALUES ('55', '2017-11-30 14:12:08', 'GKF1234', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('56', '2017-12-01 11:23:01', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('57', '2017-12-01 11:23:02', 'GKF9876', 'asd', '0');
INSERT INTO `chatting` VALUES ('58', '2017-12-01 11:23:03', 'GKF9876', 'zzxc', '0');
INSERT INTO `chatting` VALUES ('59', '2017-12-14 11:41:53', 'GKF1234', '하이', '0');
INSERT INTO `chatting` VALUES ('60', '2017-12-14 11:45:23', 'GKF9876', 'ss', '0');
INSERT INTO `chatting` VALUES ('61', '2017-12-14 13:46:11', 'GKF1234', 'ad', '0');
INSERT INTO `chatting` VALUES ('62', '2017-12-14 13:46:12', 'GKF1234', 'ww', '0');
INSERT INTO `chatting` VALUES ('63', '2017-12-14 13:46:41', 'GKF1234', 'qwe', '0');
INSERT INTO `chatting` VALUES ('64', '2017-12-14 13:47:31', 'GKF1234', 'jj', '0');
INSERT INTO `chatting` VALUES ('65', '2017-12-14 13:54:22', 'GKF1234', 'asdasd', '0');
INSERT INTO `chatting` VALUES ('66', '2017-12-14 13:54:23', 'GKF1234', 'qweqwe', '0');
INSERT INTO `chatting` VALUES ('67', '2017-12-14 14:00:31', 'GKF1234', 'asd', '0');
INSERT INTO `chatting` VALUES ('68', '2017-12-14 14:00:33', 'GKF1234', 'qwe', '0');
INSERT INTO `chatting` VALUES ('69', '2017-12-14 14:00:36', 'GKF1234', 'hh', '0');
INSERT INTO `chatting` VALUES ('70', '2017-12-14 14:15:43', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('71', '2017-12-14 14:16:01', 'GKF1234', 'dd', '0');
INSERT INTO `chatting` VALUES ('72', '2017-12-14 14:17:17', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('73', '2017-12-14 14:17:37', 'GKF9876', '음핫핫', '0');
INSERT INTO `chatting` VALUES ('74', '2017-12-14 14:17:52', 'GKF9876', '굿굿 베리굿', '0');
INSERT INTO `chatting` VALUES ('75', '2017-12-14 14:20:53', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('76', '2017-12-14 14:21:02', 'GKF9876', 'zz', '0');
INSERT INTO `chatting` VALUES ('77', '2017-12-14 14:21:05', 'GKF9876', '시발', '0');
INSERT INTO `chatting` VALUES ('78', '2017-12-14 14:23:26', 'GKF9876', 'qq', '0');
INSERT INTO `chatting` VALUES ('79', '2017-12-14 14:23:31', 'GKF9876', '댭바', '0');
INSERT INTO `chatting` VALUES ('80', '2017-12-14 14:23:36', 'GKF9876', '댭123123', '0');
INSERT INTO `chatting` VALUES ('81', '2017-12-14 14:23:36', 'GKF9876', 'ㅂㅈㄷㅂㅈㄷ', '0');
INSERT INTO `chatting` VALUES ('82', '2017-12-14 14:23:38', 'GKF9876', 'ㅁㄴㅇㅇㅁ', '0');
INSERT INTO `chatting` VALUES ('83', '2017-12-14 14:23:40', 'GKF9876', '5l1kr', '0');
INSERT INTO `chatting` VALUES ('84', '2017-12-14 14:23:44', 'GKF1234', 'zz', '0');
INSERT INTO `chatting` VALUES ('85', '2017-12-14 14:23:48', 'GKF1234', '시발', '0');
INSERT INTO `chatting` VALUES ('86', '2017-12-14 19:24:16', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('87', '2017-12-14 19:24:20', 'GKF9876', '얌마', '0');
INSERT INTO `chatting` VALUES ('88', '2017-12-14 22:28:18', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('89', '2017-12-14 22:28:20', 'GKF1234', '야', '0');
INSERT INTO `chatting` VALUES ('90', '2017-12-14 23:21:13', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('91', '2017-12-14 23:21:28', 'GKF1234', '야', '0');
INSERT INTO `chatting` VALUES ('92', '2017-12-14 23:21:31', 'GKF1234', 'ㅁㅁ', '0');
INSERT INTO `chatting` VALUES ('93', '2017-12-15 00:16:46', 'GKF9876', 'dd', '0');
INSERT INTO `chatting` VALUES ('94', '2017-12-15 06:33:27', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('95', '2017-12-15 06:33:32', 'GKF9876', 'ff', '0');
INSERT INTO `chatting` VALUES ('96', '2017-12-18 17:59:00', 'GKF9876', 'ddf', '0');
INSERT INTO `chatting` VALUES ('97', '2017-12-19 00:01:23', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('98', '2017-12-19 00:01:31', 'GKF9876', '시발', '0');
INSERT INTO `chatting` VALUES ('99', '2017-12-19 00:01:35', 'GKF9876', 'ㅣㅣ', '0');
INSERT INTO `chatting` VALUES ('100', '2017-12-19 08:18:52', 'GKF1234', 'dd', '0');
INSERT INTO `chatting` VALUES ('101', '2017-12-19 08:18:53', 'GKF1234', 'a', '0');
INSERT INTO `chatting` VALUES ('102', '2017-12-22 16:24:15', 'GKF9797', 'a', '0');
INSERT INTO `chatting` VALUES ('103', '2017-12-22 16:28:44', 'abcd1', 'a', '0');
INSERT INTO `chatting` VALUES ('104', '2017-12-22 16:28:50', 'abcd1', 'zz', '0');
INSERT INTO `chatting` VALUES ('105', '2017-12-22 16:29:24', 'abcd2', 'a', '0');
INSERT INTO `chatting` VALUES ('106', '2017-12-22 16:29:30', '', 'a', '0');
INSERT INTO `chatting` VALUES ('107', '2017-12-23 20:10:48', 'abcd2', 'aa', '0');
INSERT INTO `chatting` VALUES ('108', '2017-12-23 20:11:05', 'abcd2', 'nn', '0');
INSERT INTO `chatting` VALUES ('109', '2017-12-23 20:11:07', 'abcd2', 'bb', '0');
INSERT INTO `chatting` VALUES ('110', '2017-12-23 20:11:10', 'abcd2', '얌마', '0');
INSERT INTO `chatting` VALUES ('111', '2017-12-28 13:45:32', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('112', '2018-01-02 21:26:48', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('113', '2018-01-02 21:26:51', 'GKF9876', 'bb', '0');
INSERT INTO `chatting` VALUES ('114', '2018-01-02 21:26:53', 'GKF9876', 'cc', '0');
INSERT INTO `chatting` VALUES ('115', '2018-01-02 21:26:54', 'GKF9876', 'dd', '0');
INSERT INTO `chatting` VALUES ('116', '2018-01-02 21:26:55', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('117', '2018-01-02 21:28:22', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('118', '2018-01-02 21:28:24', 'GKF9876', '야', '0');
INSERT INTO `chatting` VALUES ('119', '2018-01-02 21:28:26', 'GKF9876', '임마', '0');
INSERT INTO `chatting` VALUES ('120', '2018-01-02 21:30:48', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('121', '2018-01-02 21:30:49', 'GKF9876', 'bb', '0');
INSERT INTO `chatting` VALUES ('122', '2018-01-02 21:30:50', 'GKF9876', 'cc', '0');
INSERT INTO `chatting` VALUES ('123', '2018-01-02 21:30:51', 'GKF9876', '야', '0');
INSERT INTO `chatting` VALUES ('124', '2018-01-02 21:30:53', 'GKF9876', '임마', '0');
INSERT INTO `chatting` VALUES ('125', '2018-01-02 21:31:02', 'GKF9876', 'ㅁㄴㅇㅁㄴㅇㅂㅈㄷㅂㅈㄷㅂㅈㅇㅂㅈㅇㅂㅈ', '0');
INSERT INTO `chatting` VALUES ('126', '2018-01-02 21:31:05', 'GKF9876', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('127', '2018-01-02 22:24:47', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('128', '2018-01-02 22:24:49', 'GKF1234', '얌마', '0');
INSERT INTO `chatting` VALUES ('129', '2018-01-02 23:00:17', 'abcd5', 'aa', '0');
INSERT INTO `chatting` VALUES ('130', '2018-01-02 23:00:19', 'abcd5', 'bb', '0');
INSERT INTO `chatting` VALUES ('131', '2018-01-02 23:00:24', 'abcd5', 'cc', '0');
INSERT INTO `chatting` VALUES ('132', '2018-01-02 23:00:25', 'abcd5', 'dd', '0');
INSERT INTO `chatting` VALUES ('133', '2018-01-02 23:00:26', 'abcd5', 'ee', '0');
INSERT INTO `chatting` VALUES ('134', '2018-01-02 23:00:29', 'abcd5', 'abcd', '0');
INSERT INTO `chatting` VALUES ('135', '2018-01-02 23:00:32', 'abcd5', '임마', '0');
INSERT INTO `chatting` VALUES ('136', '2018-01-02 23:00:34', 'abcd5', '하하', '0');
INSERT INTO `chatting` VALUES ('137', '2018-01-02 23:00:35', 'abcd5', '젠장', '0');
INSERT INTO `chatting` VALUES ('138', '2018-01-02 23:07:52', 'abcd4', 'aa', '0');
INSERT INTO `chatting` VALUES ('139', '2018-01-02 23:07:54', 'abcd4', 'bb', '0');
INSERT INTO `chatting` VALUES ('140', '2018-01-02 23:07:55', 'abcd4', 'cc', '0');
INSERT INTO `chatting` VALUES ('141', '2018-01-02 23:07:56', 'abcd4', 'dd', '0');
INSERT INTO `chatting` VALUES ('142', '2018-01-02 23:07:56', 'abcd4', 'ee', '0');
INSERT INTO `chatting` VALUES ('143', '2018-01-02 23:07:58', 'abcd4', 'ff', '0');
INSERT INTO `chatting` VALUES ('144', '2018-01-02 23:07:59', 'abcd4', 'gg', '0');
INSERT INTO `chatting` VALUES ('145', '2018-01-02 23:11:14', 'abcd2', 'a', '0');
INSERT INTO `chatting` VALUES ('146', '2018-01-02 23:13:37', 'abcd2', 'a', '0');
INSERT INTO `chatting` VALUES ('147', '2018-01-02 23:15:08', 'abcd2', 'a', '0');
INSERT INTO `chatting` VALUES ('148', '2018-01-02 23:15:10', 'abcd2', 'b', '0');
INSERT INTO `chatting` VALUES ('149', '2018-01-02 23:15:11', 'abcd2', 'c', '0');
INSERT INTO `chatting` VALUES ('150', '2018-01-02 23:19:04', 'abcd2', 'a', '0');
INSERT INTO `chatting` VALUES ('151', '2018-01-02 23:19:05', 'abcd2', 'b', '0');
INSERT INTO `chatting` VALUES ('152', '2018-01-02 23:19:41', 'abcd1', 'aa', '0');
INSERT INTO `chatting` VALUES ('153', '2018-01-02 23:33:42', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('154', '2018-01-02 23:33:45', 'GKF9876', 'di', '0');
INSERT INTO `chatting` VALUES ('155', '2018-01-02 23:33:50', 'GKF9876', '야', '0');
INSERT INTO `chatting` VALUES ('156', '2018-01-02 23:33:59', 'GKF9876', 'ㅁㅁ', '0');
INSERT INTO `chatting` VALUES ('157', '2018-01-02 23:34:02', 'GKF9876', 'zz', '0');
INSERT INTO `chatting` VALUES ('158', '2018-01-02 23:34:03', 'GKF9876', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('159', '2018-01-02 23:34:09', 'GKF9876', '글자수제한 어떻게 못하냐', '0');
INSERT INTO `chatting` VALUES ('160', '2018-01-02 23:34:29', 'GKF9876', '음', '0');
INSERT INTO `chatting` VALUES ('161', '2018-01-09 08:51:23', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('162', '2018-01-09 08:51:24', 'GKF1234', 'bb', '0');
INSERT INTO `chatting` VALUES ('163', '2018-01-09 08:55:32', 'GKF9797', 'aa', '0');
INSERT INTO `chatting` VALUES ('164', '2018-01-09 21:08:34', 'abcd7', 'aa', '0');
INSERT INTO `chatting` VALUES ('165', '2018-01-09 21:08:36', 'abcd7', 'diaak', '0');
INSERT INTO `chatting` VALUES ('166', '2018-01-09 21:08:38', 'abcd7', '얌마', '0');
INSERT INTO `chatting` VALUES ('167', '2018-01-09 21:08:39', 'abcd7', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('168', '2018-01-09 21:08:42', 'abcd7', '잘 되네', '0');
INSERT INTO `chatting` VALUES ('169', '2018-01-09 21:09:29', 'abcd1', 'aa', '0');
INSERT INTO `chatting` VALUES ('170', '2018-01-09 21:09:33', 'abcd1', '얌마들아', '0');
INSERT INTO `chatting` VALUES ('171', '2018-01-09 21:09:34', 'abcd1', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('172', '2018-01-09 21:09:36', 'abcd1', '젠장할', '0');
INSERT INTO `chatting` VALUES ('173', '2018-01-09 21:11:29', 'abcd7', 'z', '0');
INSERT INTO `chatting` VALUES ('174', '2018-01-09 21:11:38', 'abcd7', 'zz', '0');
INSERT INTO `chatting` VALUES ('175', '2018-01-09 21:11:40', 'abcd7', '굿', '0');
INSERT INTO `chatting` VALUES ('176', '2018-01-09 21:11:44', 'abcd7', '조용하네', '0');
INSERT INTO `chatting` VALUES ('177', '2018-01-09 21:11:50', 'abcd7', 'ㅋㅋ', '0');
INSERT INTO `chatting` VALUES ('178', '2018-01-17 16:08:09', 'GKF1234', 'aa', '0');
INSERT INTO `chatting` VALUES ('179', '2018-01-17 16:08:12', 'GKF1234', '얌마', '0');
INSERT INTO `chatting` VALUES ('180', '2018-01-17 23:14:21', 'GKF9876', 'aa', '0');
INSERT INTO `chatting` VALUES ('181', '2018-01-17 23:17:30', 'GKF9876', 'zz', '0');
INSERT INTO `chatting` VALUES ('182', '2018-01-25 00:03:37', 'GKF1234', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('183', '2018-01-25 20:24:03', 'GKF1234', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('184', '2018-01-25 20:24:05', 'GKF1234', 'bb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('185', '2018-01-25 20:24:06', 'GKF1234', 'cc', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('186', '2018-01-25 20:24:07', 'GKF1234', 'dd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('187', '2018-01-25 20:24:08', 'GKF1234', 'ee', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('188', '2018-01-25 20:24:09', 'GKF1234', 'ff', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('189', '2018-01-25 20:24:09', 'GKF1234', 'gg', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('190', '2018-01-25 20:25:01', 'GKF1234', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('191', '2018-01-25 20:25:03', 'GKF1234', 'bb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('192', '2018-01-25 20:25:05', 'GKF1234', '얌마', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('193', '2018-01-25 20:25:08', 'GKF9876', 'dd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('194', '2018-01-25 20:31:08', 'GKF1234', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('195', '2018-01-25 20:31:09', 'GKF1234', 'bb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('196', '2018-01-25 20:31:10', 'GKF1234', 'cc', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('197', '2018-01-25 20:31:45', 'GKF1234', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('198', '2018-01-25 20:31:46', 'GKF1234', 'bb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('199', '2018-01-25 20:31:47', 'GKF1234', 'cc', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('200', '2018-01-25 20:31:48', 'GKF1234', 'dd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('201', '2018-01-25 20:33:12', 'GKF1234', 'kk', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('202', '2018-01-25 20:33:14', 'GKF1234', '얌마', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('203', '2018-01-25 20:33:16', 'GKF1234', 'zz', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('204', '2018-01-25 20:33:18', 'GKF1234', 'ㅋㅋ', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('205', '2018-01-25 20:40:49', 'GKF9876', 'll', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('206', '2018-01-25 20:40:53', 'GKF1234', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('207', '2018-01-25 20:41:22', 'GKF1234', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('208', '2018-01-25 20:41:24', 'GKF1234', 'bb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('209', '2018-01-25 20:41:27', 'GKF9876', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('210', '2018-01-25 20:41:30', 'GKF9876', 'bb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('211', '2018-01-25 20:41:32', 'GKF9876', 'nn', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('212', '2018-01-25 20:41:34', 'GKF9876', 'asdqwe', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('213', '2018-01-25 20:41:40', 'GKF1234', 'qdwdqwd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('214', '2018-01-25 20:41:43', 'GKF1234', 'sdbebarewb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('215', '2018-01-25 20:41:44', 'GKF1234', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('216', '2018-01-25 20:41:47', 'GKF1234', 'asd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('217', '2018-01-25 20:50:52', 'GKF9876', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('218', '2018-01-25 20:50:56', 'GKF9876', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('219', '2018-01-25 20:50:57', 'GKF9876', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('220', '2018-01-25 20:50:58', 'GKF9876', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('221', '2018-01-25 20:51:03', 'GKF9876', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('222', '2018-01-25 20:51:05', 'GKF9876', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('223', '2018-01-25 20:51:07', 'GKF9876', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('224', '2018-01-25 20:51:09', 'GKF1234', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('225', '2018-01-25 20:51:11', 'GKF1234', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('226', '2018-01-25 20:51:13', 'GKF1234', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('227', '2018-01-25 20:54:08', 'GKF9876', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('228', '2018-01-25 20:54:20', 'GKF1234', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('229', '2018-01-25 20:54:22', 'GKF1234', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('230', '2018-01-25 20:54:24', 'GKF1234', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('231', '2018-01-25 20:54:31', 'GKF1234', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('232', '2018-01-25 20:54:32', 'GKF1234', 'e', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('233', '2018-01-25 20:54:36', 'GKF9876', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('234', '2018-01-25 20:54:41', 'GKF9876', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('235', '2018-01-25 20:54:44', 'GKF9876', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('236', '2018-01-25 20:54:46', 'GKF9876', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('237', '2018-01-25 20:54:47', 'GKF9876', 'e', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('238', '2018-01-25 20:54:50', 'GKF9876', 'asd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('239', '2018-01-25 20:54:52', 'GKF9876', 'asdqwe', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('240', '2018-01-25 20:54:53', 'GKF9876', 'asdasd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('241', '2018-01-25 20:54:56', 'GKF9876', 'dfgdfg', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('242', '2018-01-25 20:54:58', 'GKF9876', 'sdfsdf', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('243', '2018-01-25 20:54:59', 'GKF9876', 'zxczxc', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('244', '2018-01-25 20:55:00', 'GKF9876', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('245', '2018-01-25 20:55:01', 'GKF9876', 'e', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('246', '2018-01-25 20:55:02', 'GKF9876', 'w', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('247', '2018-01-25 20:55:06', 'GKF1234', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('248', '2018-01-25 20:55:07', 'GKF1234', 'z', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('249', '2018-01-25 20:55:08', 'GKF1234', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('250', '2018-01-25 20:55:09', 'GKF1234', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('251', '2018-01-25 20:55:11', 'GKF1234', 'e', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('252', '2018-01-25 20:57:24', 'GKF9876', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('253', '2018-01-25 20:57:26', 'GKF9876', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('254', '2018-01-25 20:57:27', 'GKF9876', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('255', '2018-01-25 20:57:29', 'GKF1234', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('256', '2018-01-25 20:57:30', 'GKF1234', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('257', '2018-01-25 20:57:31', 'GKF1234', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('258', '2018-01-25 22:49:27', 'GKF9876', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('259', '2018-01-25 22:49:30', 'GKF9876', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('260', '2018-01-25 22:49:32', 'GKF9876', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('261', '2018-01-25 22:49:40', 'GKF9876', '얌마', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('262', '2018-01-25 22:49:43', 'GKF9876', 'ㅋㅋ', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('263', '2018-01-25 22:49:46', 'abcd2', 'dd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('264', '2018-01-27 16:58:17', 'GKF9876', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('265', '2018-01-27 16:58:18', 'GKF9876', 'bb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('266', '2018-01-27 16:58:19', 'GKF9876', 'cc', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('267', '2018-01-28 10:17:24', 'GKF1234', 'aa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('268', '2018-01-28 10:17:25', 'GKF1234', 'bb', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('269', '2018-01-28 10:17:26', 'GKF1234', 'cc', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('270', '2018-01-28 10:17:26', 'GKF1234', 'dd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('271', '2018-01-28 10:17:27', 'GKF1234', 'ee', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('272', '2018-01-28 10:17:28', 'GKF1234', 'gg', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('273', '2018-01-28 10:17:29', 'GKF1234', 'ff', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('274', '2018-01-28 10:17:29', 'GKF1234', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('275', '2018-01-28 10:17:30', 'GKF1234', 's', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('276', '2018-01-28 10:17:30', 'GKF1234', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('277', '2018-01-28 10:17:30', 'GKF1234', 'w', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('278', '2018-01-28 10:17:31', 'GKF1234', 'e', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('279', '2018-01-28 10:17:31', 'GKF1234', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('280', '2018-01-28 10:17:32', 'GKF1234', 's', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('281', '2018-01-28 10:17:32', 'GKF1234', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('282', '2018-01-28 10:23:51', 'GKF1234', 'a', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('283', '2018-01-28 10:23:51', 'GKF1234', 'b', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('284', '2018-01-28 10:23:52', 'GKF1234', 'c', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('285', '2018-01-28 10:23:53', 'GKF1234', 'd', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('286', '2018-01-28 10:23:54', 'GKF1234', 'e', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('287', '2018-01-28 10:23:55', 'GKF1234', 'f', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('288', '2018-01-28 10:23:56', 'GKF1234', 'g', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('289', '2018-01-28 10:23:57', 'GKF1234', 'h', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('290', '2018-02-18 16:03:23', 'GKF1234', '\r', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('291', '2018-02-18 16:03:33', 'GKF1234', '\r', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('292', '2018-02-18 18:34:52', 'GKF1234', 'aaaaaaaaaaaaaaaaaaaa', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');
INSERT INTO `chatting` VALUES ('293', '2018-02-23 19:09:43', 'GKF9797', 'AA', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx');

-- ----------------------------
-- Table structure for `inventory_info`
-- ----------------------------
DROP TABLE IF EXISTS `inventory_info`;
CREATE TABLE `inventory_info` (
  `idx` int(11) NOT NULL,
  `name` varchar(50) CHARACTER SET utf8 NOT NULL DEFAULT 'nameless',
  `user` varchar(50) CHARACTER SET utf8 DEFAULT NULL,
  `type` varchar(20) CHARACTER SET utf8 DEFAULT '',
  `xpos` int(11) DEFAULT NULL,
  `ypos` int(11) DEFAULT NULL,
  `order` int(11) DEFAULT '1',
  `file_dir` varchar(100) CHARACTER SET utf8 DEFAULT NULL,
  `count` int(11) DEFAULT '0',
  PRIMARY KEY (`idx`,`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ----------------------------
-- Records of inventory_info
-- ----------------------------
INSERT INTO `inventory_info` VALUES ('1', 'nameless1', 'GKF1234', 'item', '0', '2', '1', 'items/a.png', '364');
INSERT INTO `inventory_info` VALUES ('2', 'nameless2', 'GKF1234', 'item', '2', '2', '1', 'items/b.png', '192');
INSERT INTO `inventory_info` VALUES ('4', 'nameless4', 'GKF1234', 'item', '1', '2', '1', 'items/d.png', '162');
INSERT INTO `inventory_info` VALUES ('5', 'nameless5', 'GKF9876', 'item', '0', '2', '1', 'items/e.png', '30');

-- ----------------------------
-- Table structure for `map_info`
-- ----------------------------
DROP TABLE IF EXISTS `map_info`;
CREATE TABLE `map_info` (
  `object_number` int(11) NOT NULL AUTO_INCREMENT,
  `field` varchar(100) NOT NULL DEFAULT '',
  `idx` int(11) DEFAULT NULL,
  `name` varchar(50) DEFAULT 'nameless',
  `type` varchar(20) DEFAULT '',
  `xpos` int(11) DEFAULT NULL,
  `ypos` int(11) DEFAULT NULL,
  `z_order` int(11) DEFAULT '1',
  `file_dir` varchar(100) DEFAULT NULL,
  `count` int(11) DEFAULT '1',
  `hp` int(11) DEFAULT NULL,
  PRIMARY KEY (`object_number`,`field`)
) ENGINE=InnoDB AUTO_INCREMENT=667 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of map_info
-- ----------------------------
INSERT INTO `map_info` VALUES ('528', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '1', 'squirrel', 'monster', '29', '3', '1', 'monster/squirrel', '1', '50');
INSERT INTO `map_info` VALUES ('529', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '1', 'squirrel', 'monster', '1', '11', '1', 'monster/squirrel', '1', '50');
INSERT INTO `map_info` VALUES ('622', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '28', '9', '1', 'monster/deer', '1', '100');
INSERT INTO `map_info` VALUES ('625', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '39', '13', '1', 'monster/deer', '1', '100');
INSERT INTO `map_info` VALUES ('648', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '3', '12', '1', 'monster/deer', '1', '100');
INSERT INTO `map_info` VALUES ('651', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '17', '2', '1', 'monster/deer', '1', '30');
INSERT INTO `map_info` VALUES ('652', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '29', '10', '1', 'monster/deer', '1', '100');
INSERT INTO `map_info` VALUES ('657', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '39', '12', '1', 'monster/deer', '1', '100');
INSERT INTO `map_info` VALUES ('660', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '1', 'squirrel', 'monster', '38', '12', '1', 'monster/squirrel', '1', '50');
INSERT INTO `map_info` VALUES ('661', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '17', '2', '1', 'monster/deer', '1', '100');
INSERT INTO `map_info` VALUES ('662', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '1', 'squirrel', 'monster', '16', '5', '1', 'monster/squirrel', '1', '50');
INSERT INTO `map_info` VALUES ('663', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '40', '13', '1', 'monster/deer', '1', '100');
INSERT INTO `map_info` VALUES ('664', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '1', 'squirrel', 'monster', '14', '13', '1', 'monster/squirrel', '1', '50');
INSERT INTO `map_info` VALUES ('665', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '38', '10', '1', 'monster/deer', '1', '100');
INSERT INTO `map_info` VALUES ('666', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '2', 'deer', 'monster', '19', '9', '1', 'monster/deer', '1', '100');

-- ----------------------------
-- Table structure for `map_list`
-- ----------------------------
DROP TABLE IF EXISTS `map_list`;
CREATE TABLE `map_list` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `field` varchar(100) CHARACTER SET utf8 NOT NULL,
  `monster1` varchar(50) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `monster2` varchar(50) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `monster3` varchar(50) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `monster1_count` int(11) DEFAULT NULL,
  `monster2_count` int(11) DEFAULT NULL,
  `monster3_count` int(11) DEFAULT NULL,
  PRIMARY KEY (`idx`,`field`)
) ENGINE=InnoDB AUTO_INCREMENT=145 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ----------------------------
-- Records of map_list
-- ----------------------------
INSERT INTO `map_list` VALUES ('1', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('2', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_02/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('3', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_03/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('4', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_04/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('5', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_05/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('6', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_06/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('7', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_07/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('8', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', 'squirrel', 'deer', null, '5', '10', null);
INSERT INTO `map_list` VALUES ('9', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('10', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('12', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('13', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('14', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('15', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('16', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('17', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('18', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('19', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('20', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('71', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_07/007.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('72', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_07/008.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('73', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_07/009.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('74', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('75', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/002.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('76', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/003.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('77', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/004.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('78', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/005.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('79', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/006.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('80', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/007.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('81', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/008.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('82', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/009.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('83', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('84', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/002.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('85', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/003.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('86', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/004.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('87', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/005.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('88', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/006.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('89', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/007.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('90', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/008.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('91', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/009.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('92', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('93', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/002.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('94', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/003.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('95', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/004.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('96', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/005.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('97', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/006.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('98', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/007.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('99', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/008.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('100', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/009.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('101', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('102', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_02/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('103', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_03/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('104', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_04/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('105', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_05/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('106', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_06/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('107', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_07/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('108', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('109', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('110', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('111', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_01/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('112', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_02/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('113', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_03/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('114', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_04/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('115', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_05/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('116', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_06/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('117', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_07/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('118', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('119', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_09/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('120', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_10/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('121', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('122', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('123', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/002.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('124', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/003.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('125', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/004.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('126', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/005.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('127', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/006.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('128', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/007.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('129', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/008.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('130', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/009.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('131', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('132', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_B1/toiret.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('133', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/floor.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('134', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/001.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('135', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/002.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('136', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/003.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('137', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/004.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('138', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/005.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('139', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/006.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('140', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/007.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('141', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/008.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('142', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/009.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('143', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/stair.tmx', null, null, null, null, null, null);
INSERT INTO `map_list` VALUES ('144', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_L/toiret.tmx', null, null, null, null, null, null);

-- ----------------------------
-- Table structure for `monster_list`
-- ----------------------------
DROP TABLE IF EXISTS `monster_list`;
CREATE TABLE `monster_list` (
  `idx` int(11) NOT NULL,
  `name` varchar(50) DEFAULT 'nameless',
  `type` varchar(20) DEFAULT '',
  `file_dir` varchar(100) DEFAULT NULL,
  `hp` int(11) DEFAULT NULL,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of monster_list
-- ----------------------------
INSERT INTO `monster_list` VALUES ('1', 'squirrel', 'monster', 'monster/squirrel', '50');
INSERT INTO `monster_list` VALUES ('2', 'deer', 'monster', 'monster/deer', '100');

-- ----------------------------
-- Table structure for `server_info`
-- ----------------------------
DROP TABLE IF EXISTS `server_info`;
CREATE TABLE `server_info` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `INPUTDATE` datetime NOT NULL,
  PRIMARY KEY (`idx`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of server_info
-- ----------------------------
INSERT INTO `server_info` VALUES ('1', '2018-03-17 15:53:42');

-- ----------------------------
-- Table structure for `user_list`
-- ----------------------------
DROP TABLE IF EXISTS `user_list`;
CREATE TABLE `user_list` (
  `idx` int(11) NOT NULL AUTO_INCREMENT,
  `ID` varchar(50) NOT NULL,
  `xpos` int(11) DEFAULT NULL,
  `ypos` int(11) DEFAULT NULL,
  `field` varchar(100) DEFAULT '',
  `login` tinyint(1) DEFAULT '0',
  `sock` int(11) DEFAULT NULL,
  `seeDirection` int(11) NOT NULL DEFAULT '29',
  `last_login` datetime DEFAULT NULL,
  `last_logout` datetime DEFAULT NULL,
  `join_date` datetime DEFAULT NULL,
  PRIMARY KEY (`idx`,`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of user_list
-- ----------------------------
INSERT INTO `user_list` VALUES ('3', 'GKF9876', '17', '3', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-03-17 00:42:57', '2018-03-17 00:43:00', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('4', 'GKF1234', '18', '7', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-03-17 15:36:47', '2018-03-17 15:36:49', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('5', 'GKF9797', '18', '6', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '28', '2018-03-17 00:43:01', '2018-03-17 00:43:01', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('6', 'gkf7676', '21', '12', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:11:01', '2018-01-25 23:11:12', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('7', 'abcd1', '18', '7', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:58', '2018-01-25 23:11:09', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('8', 'abcd2', '18', '8', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '26', '2018-01-25 23:11:01', '2018-01-25 23:11:12', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('9', 'abcd3', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:11:00', '2018-01-25 23:11:11', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('10', 'abcd4', '20', '4', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:58', '2018-01-25 23:11:09', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('11', 'abcd5', '19', '8', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '28', '2018-01-25 23:11:01', '2018-01-25 23:11:12', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('12', 'abcd6', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:58', '2018-01-25 23:11:09', '2018-01-01 00:00:00');
INSERT INTO `user_list` VALUES ('13', 'abcd7', '16', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '28', '2018-01-25 23:10:59', '2018-01-25 23:11:10', '2018-01-02 09:43:07');
INSERT INTO `user_list` VALUES ('14', 'abcd8', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:11:02', '2018-01-25 23:11:13', '2018-01-25 22:54:41');
INSERT INTO `user_list` VALUES ('15', 'abcd9', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:11:02', '2018-01-25 23:11:13', '2018-01-25 22:54:46');
INSERT INTO `user_list` VALUES ('16', 'abcd10', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:11:10', '2018-01-25 23:11:10', '2018-01-25 22:55:02');
INSERT INTO `user_list` VALUES ('17', 'abcd11', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:11:02', '2018-01-25 23:11:13', '2018-01-25 22:55:07');
INSERT INTO `user_list` VALUES ('18', 'abcd12', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:11:01', '2018-01-25 23:11:12', '2018-01-25 22:55:11');
INSERT INTO `user_list` VALUES ('19', 'abcd13', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:59', '2018-01-25 23:11:10', '2018-01-25 22:55:15');
INSERT INTO `user_list` VALUES ('20', 'abcd14', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:59', '2018-01-25 23:11:10', '2018-01-25 22:55:19');
INSERT INTO `user_list` VALUES ('21', 'abcd15', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:59', '2018-01-25 23:11:10', '2018-01-25 22:55:24');
INSERT INTO `user_list` VALUES ('22', 'abcd16', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:58', '2018-01-25 23:11:09', '2018-01-25 22:55:28');
INSERT INTO `user_list` VALUES ('23', 'abcd17', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:58', '2018-01-25 23:11:09', '2018-01-25 22:55:34');
INSERT INTO `user_list` VALUES ('24', 'abcd18', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:57', '2018-01-25 23:11:08', '2018-01-25 22:55:39');
INSERT INTO `user_list` VALUES ('25', 'abcd19', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '29', '2018-01-25 23:10:57', '2018-01-25 23:11:08', '2018-01-25 22:56:01');
INSERT INTO `user_list` VALUES ('26', 'abcd20', '19', '10', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '0', '0', '28', '2018-01-25 23:11:52', '2018-01-25 23:11:54', '2018-01-25 22:56:07');
