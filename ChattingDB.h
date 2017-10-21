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

int openMySQL_chatting();
int closeMySQL_chatting();

int insertSql_chatting(int field, char * name, char * content);
int deleteSql_chatting(int field);
int updateSql_chatting(int field);
int selectSql_chatting(int field);



#endif
