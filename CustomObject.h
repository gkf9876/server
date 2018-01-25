#ifndef __CUSTOM_OBJECT_H_
#define __CUSTOM_OBJECT_H_

#include <stdio.h>

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

#endif
