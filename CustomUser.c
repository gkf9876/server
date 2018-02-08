#include "CustomUser.h"

void initStructCustomUserList(StructCustomUserList * structCustomUserList)
{
	structCustomUserList->value = NULL;
	structCustomUserList->next = NULL;
}

void insertStructCustomUserList(StructCustomUserList * list, StructCustomUser * user)
{
	StructCustomUserList * imsi = list;

	while (1)
	{
		if (imsi->next == NULL)
		{
			imsi->next = (StructCustomUserList*)malloc(sizeof(StructCustomUserList));
			imsi = imsi->next;

			imsi->value = user;
			imsi->next = NULL;
			return;
		}
		else
			imsi = imsi->next;
	}
}

StructCustomUser * getStructCustomUserList(StructCustomUserList * structCustomUserList)
{
	StructCustomUserList * imsi = structCustomUserList;

	if (imsi->next == NULL)
		return NULL;
	else
	{
		StructCustomUserList * front = imsi->next;
		StructCustomUser * result = front->value;
		imsi->next = front->next;
		front->next = NULL;
		free(front);
		return result;
	}
}

void clearStructCustomUserList(StructCustomUserList * structCustomUserList)
{
	StructCustomUserList * imsi = structCustomUserList;
	StructCustomUser * deleteInfo;

	while ((deleteInfo = getStructCustomUserList(imsi)) != NULL)
	{
		free(deleteInfo);
	}
}