#ifndef __CUSTOM_USER_H_
#define __CUSTOM_USER_H_

#include <stdio.h>

#define ACTION_MAP_IN		0
#define ACTION_MAP_MOVE		1
#define ACTION_MAP_OUT		2
#define ACTION_MAP_POTAL	3

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

typedef struct
{
	StructCustomUser * value;
	struct StructCustomUserList * next;
}StructCustomUserList;

void initStructCustomUserList(StructCustomUserList * structCustomUserList);

void insertStructCustomUserList(StructCustomUserList * list, StructCustomUser * user);

StructCustomUser * getStructCustomUserList(StructCustomUserList * structCustomUserList);

void clearStructCustomUserList(StructCustomUserList * structCustomUserList);

#endif
