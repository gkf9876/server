#ifndef __CHATTING_DB_H_
#define __CHATTING_DB_H_



#include "mysql/mysql.h"
#include <string.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "doeltms08"
#define DB_NAME "test"

//MYSQL       	*connection=NULL, conn;
//MYSQL_RES   	*sql_result;
//MYSQL_ROW   	sql_row;
//int 		query_stat; 

typedef struct user
{
	int sock;
	char name[50];
	char password[50];
	int xpos;
	int ypos;
	int field;
}User;

int openMySQL_chatting();
int closeMySQL_chatting();

MYSQL_RES * selectSql_UserInfo(int number);

int insertSql_chatting(int field, char * name, char * content);
int deleteSql_chatting(int field);
int updateSql_chatting(int field);
MYSQL_RES * selectSql_chatting(int field);

int insertSql_UserInfo(User user);
int deleteSql_UserInfo(int sock);


#endif
