﻿#ifndef __CHATTING_DB_H_
#define __CHATTING_DB_H_



#include "mysql/mysql.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CustomObject.h"

#define DB_HOST "127.0.0.1"
#define DB_USER "gkf9876"
#define DB_PASS "9109382616@"
#define DB_NAME "test"

#define QUERY_BUF_SIZE 1024

typedef struct user
{
	int sock;
	char name[50];
	char password[50];
	int xpos;
	int ypos;
	char field[100];
	int seeDirection;
}User;

int openMySQL_chatting();
int closeMySQL_chatting();

MYSQL_RES * selectSql_isUser(char * user);
MYSQL_RES * selectSql_UserInfo(int sock);

int insertSql_chatting(char * field, char * name, char * content);
int deleteSql_chatting(char * field);
int updateSql_chatting(char * field);
MYSQL_RES * selectSql_chatting(char * userName);

int updateSql_UserLogin(User user);
int updateSql_UserLogout(int sock);

int updateUserMove(char * userName, int xpos, int ypos, char * field, int seeDirection);
MYSQL_RES * selectSql_fieldUsers(int sock);
MYSQL_RES * selectSql_User(int sock);

int updateDate(int idx);

int insertUserInfo(char * userName);

//최근에 로그아웃한 시간
int updateLogoutDateTime(int sock);

//지금 찐짜로 접속한 유저 확인
MYSQL_RES * selectSql_comfirmTrueNowLoginUser();

//맵 정보를 가져옴.
MYSQL_RES * selectSql_field_info(char * field);

//맵의 아이템을 지움
int deleteMapObject(int idx);

//인벤토리에 아이템을 넣어준다.
int insertInventoryItem(int sock, StructCustomObject structCustomObject);

//인벤토리 정보를 불러온다.
MYSQL_RES * selectSql_inventory_info(char * userName);

//인벤토리의 아이템정보를 업데이트
int updateInventoryItem(int sock, StructCustomObject structCustomObject);

//맵에 아이템을 추가한다.
int insertSql_mapObject(char * field, StructCustomObject structCustomObject);

//인벤토리의 아이템을 지움
int deleteSql_inventoryItem(StructCustomObject structCustomObject);

//유저가 위치한 맵 이름을 불러온다.
MYSQL_RES * selectSql_userField_info(int sock);

#endif
