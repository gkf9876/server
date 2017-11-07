#ifndef __CHATTING_DB_H_
#define __CHATTING_DB_H_



#include "mysql/mysql.h"
#include <string.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "gkf9876"
#define DB_PASS "9109382616@"
#define DB_NAME "test"

typedef struct user
{
	int sock;
	char name[50];
	char password[50];
	int xpos;
	int ypos;
	char field[100];
}User;

int openMySQL_chatting();
int closeMySQL_chatting();

MYSQL_RES * selectSql_isUser(char * user);
MYSQL_RES * selectSql_UserInfo(int sock);

int insertSql_chatting(int field, char * name, char * content);
int deleteSql_chatting(int field);
int updateSql_chatting(int field);
MYSQL_RES * selectSql_chatting(char * userName);

int insertSql_UserInfo(User user);
int deleteSql_UserInfo(int sock);

int updateUserMove(char * userName, int xpos, int ypos, char * field);
MYSQL_RES * selectSql_fieldUsers(char * userName);
MYSQL_RES * selectSql_User(int sock);

#endif
