#ifndef __MANAGE_MAP_H_
#define __MANAGE_MAP_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <pthread.h>

#include "mysql/mysql.h"
#include "dumper.h"
#include "CustomUser.h"
#include "CustomObject.h"

#define DB_HOST "127.0.0.1"
#define DB_USER "gkf9876"
#define DB_PASS "9109382616@"
#define DB_NAME "test"

#define QUERY_BUF_SIZE 1024
#define BUF_SIZE 1024

#define REQUEST_USER_INFO				1
#define REQUEST_LOGIN					2
#define CHATTING_PROCESS				3
#define USER_MOVE_UPDATE				4
#define OTHER_USER_MAP_MOVE				5
#define REQUEST_JOIN					6
#define UPDATE_LOGIN_TIME				7
#define REQUEST_TILED_MAP				8
#define REQUEST_IMAGE					9
#define DELETE_FIELD_ITEM				10
#define REQUEST_FIELD_INFO				11
#define REQUEST_INVENTORY_ITEM_INFO		12
#define MOVE_INVENTORY_ITEM				13
#define THROW_ITEM						14
#define REGEN_MONSTER					15
#define ATTACK_FILED_OBJECT				16

void thread_error_handling(char * message);
int thread_sendCommand(int sock, int code, char * message, int size);
int thread_readCommand(int sock, int * code, char * buf);

void thread_IntToChar(int value, char * result);
void thread_CharToInt(char * value, int * result);

int openMySQL_manageMap();
int closeMySQL_manageMap();

//모든맵의 몬스터 마리수와 최대 마리수 확인
MYSQL_RES * selectSql_mapMonsterList();

//맵에 몬스터를 넣어준다.
int insertMapMonster(char * field, char * name, int xpos, int ypos);

//맵의 몬스터 정보를 확인
MYSQL_RES * selectSql_MapMonster(char * field);

//맵의 유저리스트 확인
StructCustomUserList * selectSql_loginUserList(char * field);

//몬스터 정보 확인
StructCustomObject * selectSql_monsterInfo(char * name);

//유저 로그아웃처리
int updateSql_threadUserLogout(int sock);

//맵관리 쓰레드
void * manageMapThread_main(void * arg);

#endif
