#include "CustomObject.h"

void initStructCustomObjectList(StructCustomObjectList * structCustomObjectList)
{
	structCustomObjectList->value = NULL;
	structCustomObjectList->next = NULL;
}

void insertStructCustomObjectList(StructCustomObjectList * list, StructCustomObject * Object)
{
	StructCustomObjectList * imsi = list;

	while (1)
	{
		if (imsi->next == NULL)
		{
			imsi->next = (StructCustomObjectList*)malloc(sizeof(StructCustomObjectList));
			imsi = imsi->next;

			imsi->value = Object;
			imsi->next = NULL;
			return;
		}
		else
			imsi = imsi->next;
	}
}

StructCustomObject * getStructCustomObjectList(StructCustomObjectList * structCustomObjectList)
{
	StructCustomObjectList * imsi = structCustomObjectList;

	if (imsi->next == NULL)
		return NULL;
	else
	{
		StructCustomObjectList * front = imsi->next;
		StructCustomObject * result = front->value;
		imsi->next = front->next;
		front->next = NULL;
		free(front);
		return result;
	}
}

void clearStructCustomObjectList(StructCustomObjectList * structCustomObjectList)
{
	StructCustomObjectList * imsi = structCustomObjectList;
	StructCustomObject * deleteInfo;

	while ((deleteInfo = getStructCustomObjectList(imsi)) != NULL)
	{
		free(deleteInfo);
	}
}