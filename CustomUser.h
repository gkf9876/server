#ifndef __CUSTOM_USER_H_
#define __CUSTOM_USER_H_

#include <stdio.h>

#define ACTION_MAP_IN		0
#define ACTION_MAP_MOVE		1
#define ACTION_MAP_OUT		2

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

#endif
