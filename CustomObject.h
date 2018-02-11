#ifndef __CUSTOM_OBJECT_H_
#define __CUSTOM_OBJECT_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int idx;
	char name[50];
	char type[50];
	int xpos;
	int ypos;
	int order;
	char fileDir[100];
	int count;
}StructCustomObject;

typedef struct structCustomObjectList
{
	StructCustomObject * value;
	struct structCustomObjectList * next;
}StructCustomObjectList;

void initStructCustomObjectList(StructCustomObjectList * structCustomUserList);

void insertStructCustomObjectList(StructCustomObjectList * list, StructCustomObject * user);

StructCustomObject * getStructCustomObjectList(StructCustomObjectList * structCustomUserList);

void clearStructCustomObjectList(StructCustomObjectList * structCustomUserList);

int getObjectCount(StructCustomObjectList * structCustomObjectList);

#endif
