#ifndef __MANAGE_MAP_H_
#define __MANAGE_MAP_H_



#include "mysql/mysql.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "dumper.h"

#define DB_HOST "127.0.0.1"
#define DB_USER "gkf9876"
#define DB_PASS "9109382616@"
#define DB_NAME "test"

#define QUERY_BUF_SIZE 1024

int openMySQL_manageMap();
int closeMySQL_manageMap();

//모든맵의 몬스터 마리수와 최대 마리수 확인
MYSQL_RES * selectSql_mapMonsterList();

//맵에 몬스터를 넣어준다.
int insertMapMonster(char * field, char * name, int xpos, int ypos);

//맵의 몬스터 정보를 확인
MYSQL_RES * selectSql_MapMonster(char * field);

//맵관리 쓰레드
void * manageMapThread_main(void * arg);

#endif
