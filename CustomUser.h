#ifndef __CUSTOM_USER_H_
#define __CUSTOM_USER_H_

#include <stdio.h>
#include <stdlib.h>

#define ACTION_MAP_IN		0
#define ACTION_MAP_MOVE		1
#define ACTION_MAP_OUT		2
#define ACTION_MAP_POTAL	3
#define ACTION_MAP_MOVE_END	4
#define ACTION_ATTACK       5
#define ACTION_ATTACK_END   6

typedef struct
{
	int sock;
	char name[50];
	char password[50];
	int xpos;
	int ypos;
	char field[100];
	int seeDirection;
	int action;
}StructCustomUser;

typedef struct structCustomUserList
{
	StructCustomUser * value;
	struct structCustomUserList * next;
}StructCustomUserList;

void initStructCustomUserList(StructCustomUserList * structCustomUserList);

void insertStructCustomUserList(StructCustomUserList * list, StructCustomUser * user);

StructCustomUser * getStructCustomUserList(StructCustomUserList * structCustomUserList);

void clearStructCustomUserList(StructCustomUserList * structCustomUserList);

#endif
