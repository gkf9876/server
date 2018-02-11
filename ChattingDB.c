#include "ChattingDB.h"

MYSQL       	*connection=NULL, conn;
MYSQL_RES   	*sql_result;
MYSQL_ROW   	sql_row;
int 		query_stat; 

int openMySQL_chatting()
{
	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES utf8");

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));

		return -1;
	}

	return 1;
}

int closeMySQL_chatting()
{
	if(connection != NULL)
	{
		mysql_close(connection);
		return 1;
	}
	else
		return -1;	
}

int selectSql_isUser(char * user)
{
	char query[QUERY_BUF_SIZE];
	int result;

	sprintf(query, "SELECT COUNT(ID) AS COUNT FROM USER_LIST WHERE ID = BINARY('%s') AND LOGIN = 0", user);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	sql_result = mysql_store_result(connection);
	sql_row = mysql_fetch_row(sql_result);

	result = atoi(sql_row[0]);

	mysql_free_result(sql_result);

	return result;
}

StructCustomUser * selectSql_UserInfo(int sock)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "SELECT ID, XPOS, YPOS, FIELD, SEEDIRECTION FROM USER_LIST WHERE SOCK = '%d'", sock);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return NULL;
	}

	sql_result = mysql_store_result(connection);
	sql_row = mysql_fetch_row(sql_result);

	StructCustomUser * user = (StructCustomUser*)malloc(sizeof(StructCustomUser));
	user->sock = sock;
	strcpy(user->name, sql_row[0]);
	user->xpos = atoi(sql_row[1]);
	user->ypos = atoi(sql_row[2]);
	strcpy(user->field, sql_row[3]);
	user->seeDirection = atoi(sql_row[4]);

	mysql_free_result(sql_result);

	return user;
}

int insertSql_chatting(char * field, char * name, char * content)
{
	char query[QUERY_BUF_SIZE];

	if(name == NULL || content == NULL)
	{
		fprintf(stderr, "Mysql insert error : %s\n", mysql_error(&conn));
		return -1;
	}

	sprintf(query, "INSERT INTO CHATTING(INPUTDATE, NAME, CONTENT, FIELD) VALUES (SYSDATE(), '%s', '%s', '%s')", name, content, field);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int deleteSql_chatting(char * field)
{
}

int updateSql_chatting(char * field)
{
}

int updateSql_UserLogin(int sock, char * name)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "UPDATE USER_LIST SET SOCK = '%d', LOGIN = '1', LAST_LOGIN = SYSDATE() WHERE ID = BINARY('%s')", sock, name);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int updateSql_UserLogout(int sock)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "UPDATE USER_LIST SET LOGIN = '0', SOCK = '0' WHERE SOCK = '%d' AND LOGIN = '1'", sock);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int updateUserMove(StructCustomUser structCustomUser)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "UPDATE USER_LIST SET XPOS = '%d', YPOS = '%d', FIELD = '%s', SEEDIRECTION = '%d' WHERE ID = BINARY('%s') AND LOGIN = '1'", structCustomUser.xpos, structCustomUser.ypos, structCustomUser.field, structCustomUser.seeDirection, structCustomUser.name);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

StructCustomUserList * selectSql_fieldUsers(int sock)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "SELECT A.SOCK, A.ID, A.XPOS, A.YPOS, A.SEEDIRECTION FROM USER_LIST A, (SELECT ID, FIELD FROM USER_LIST WHERE SOCK = '%d') B WHERE A.FIELD = B.FIELD AND A.ID <> B.ID AND A.LOGIN = 1", sock);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return NULL;
	}

	sql_result = mysql_store_result(connection);

	StructCustomUserList * userList = (StructCustomUserList *)malloc(sizeof(StructCustomUserList));
	initStructCustomUserList(userList);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		StructCustomUser * user = (StructCustomUser*)malloc(sizeof(StructCustomUser));
		user->sock = atoi(sql_row[0]);
		strcpy(user->name, sql_row[1]);
		user->xpos = atoi(sql_row[2]);
		user->ypos = atoi(sql_row[3]);
		user->seeDirection = atoi(sql_row[4]);

		insertStructCustomUserList(userList, user);
	}

	mysql_free_result(sql_result);

	return userList;
}

int updateDate(int idx)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "UPDATE SERVER_INFO SET INPUTDATE = SYSDATE() WHERE IDX = '%d'", idx);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int insertUserInfo(char * userName)
{
	char query[QUERY_BUF_SIZE];

	//중복되는 아이디인지 확인
	sprintf(query, "SELECT count(ID) FROM USER_LIST WHERE ID = '%s'", userName);
	query_stat = mysql_query(connection, query);
	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		if (atoi(sql_row[0]) > 0)
		{
			printf("Duplicate ID error\n");
			return -1;
		}
	}

	//아이디 등록
	sprintf(query, "INSERT INTO USER_LIST(ID, XPOS, YPOS, FIELD, SEEDIRECTION, JOIN_DATE) VALUE('%s', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '29', SYSDATE())", userName);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int updateLogoutDateTime(int sock)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "UPDATE USER_LIST SET LAST_LOGOUT = SYSDATE() WHERE SOCK = '%d'", sock);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int updateLoginDateTime(int sock)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "UPDATE USER_LIST SET LAST_LOGIN = SYSDATE() WHERE SOCK = '%d'", sock);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

MYSQL_RES * selectSql_comfirmTrueNowLoginUser()
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "SELECT SOCK, IF(DATE_ADD(SYSDATE(), INTERVAL -10 SECOND) <= LAST_LOGIN, TRUE, FALSE) AS LOGIN FROM user_list WHERE LOGIN = '1'");

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

StructCustomObjectList * selectSql_field_info(char * field)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "SELECT A.idx, A.name, A.type, A.xpos, A.ypos, A.z_order, A.file_dir, A.count FROM MAP_INFO A WHERE FIELD = '%s'", field);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
	}

	sql_result = mysql_store_result(connection);

	StructCustomObjectList * objectList = (StructCustomObjectList*)malloc(sizeof(StructCustomObjectList));
	initStructCustomObjectList(objectList);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		StructCustomObject * object = (StructCustomObject*)malloc(sizeof(StructCustomObject));
		object->idx = atoi(sql_row[0]);
		strcpy(object->name, sql_row[1]);
		strcpy(object->type, sql_row[2]);
		object->xpos = atoi(sql_row[3]);
		object->ypos = atoi(sql_row[4]);
		object->order = atoi(sql_row[5]);
		strcpy(object->fileDir, sql_row[6]);
		object->count = atoi(sql_row[7]);

		insertStructCustomObjectList(objectList, object);
	}
	mysql_free_result(sql_result);

	return objectList;
}

int deleteMapObject(int idx)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "DELETE FROM MAP_INFO WHERE IDX = '%d'", idx);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int insertInventoryItem(int sock, StructCustomObject structCustomObject)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "INSERT INTO INVENTORY_INFO(IDX, NAME, USER, TYPE, XPOS, YPOS, FILE_DIR, COUNT) ");
	sprintf(&query[strlen(query)], "SELECT '%d' AS IDX, '%s' AS NAME, A.ID AS USER, '%s' AS TYPE, ", structCustomObject.idx, structCustomObject.name, structCustomObject.type);
	sprintf(&query[strlen(query)], "'%d' AS XPOS, '%d' AS YPOS, '%s' AS FILE_DIR, '%d' AS COUNT ", structCustomObject.xpos, structCustomObject.ypos, structCustomObject.fileDir, structCustomObject.count);
	sprintf(&query[strlen(query)], "FROM USER_LIST A WHERE SOCK = '%d' AND LOGIN = 1 ", sock);
	sprintf(&query[strlen(query)], "ON DUPLICATE KEY UPDATE IDX = '%d', NAME = '%s', USER = A.ID, TYPE = '%s', ", structCustomObject.idx, structCustomObject.name, structCustomObject.type);
	sprintf(&query[strlen(query)], "FILE_DIR = '%s', COUNT = COUNT + '%d' ", structCustomObject.fileDir, structCustomObject.count);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

StructCustomObjectList * selectSql_inventory_info(char * userName)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "SELECT A.IDX, A.NAME, A.TYPE, A.XPOS, A.YPOS, A.ORDER, A.FILE_DIR, A.COUNT FROM INVENTORY_INFO A WHERE A.USER = '%s'", userName);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
	}

	sql_result = mysql_store_result(connection);

	StructCustomObjectList * objectList = (StructCustomObjectList*)malloc(sizeof(StructCustomObjectList));
	initStructCustomObjectList(objectList);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		StructCustomObject * object = (StructCustomObject*)malloc(sizeof(StructCustomObject));
		object->idx = atoi(sql_row[0]);
		strcpy(object->name, sql_row[1]);
		strcpy(object->type, sql_row[2]);
		object->xpos = atoi(sql_row[3]);
		object->ypos = atoi(sql_row[4]);
		object->order = atoi(sql_row[5]);
		strcpy(object->fileDir, sql_row[6]);
		object->count = atoi(sql_row[7]);

		insertStructCustomObjectList(objectList, object);
	}
	mysql_free_result(sql_result);

	return objectList;
}

int updateInventoryItem(int sock, StructCustomObject structCustomObject)
{
	char query[QUERY_BUF_SIZE];
	int xpos = structCustomObject.xpos;
	int ypos = structCustomObject.ypos;
	int count = structCustomObject.count;
	int idx = structCustomObject.idx;
	char name[50];
	strcpy(name, structCustomObject.name);

	sprintf(query, "UPDATE INVENTORY_INFO SET XPOS = '%d', YPOS = '%d', COUNT = '%d' WHERE IDX = '%d' AND NAME = '%s' AND USER = (SELECT ID FROM USER_LIST WHERE SOCK = '%d' AND LOGIN = '1')", xpos, ypos, count, idx, name, sock);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql Update query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int insertSql_mapObject(char * field, StructCustomObject structCustomObject)
{
	char query[QUERY_BUF_SIZE];

	int idx = structCustomObject.idx;
	char name[50];
	strcpy(name, structCustomObject.name);
	char type[50];
	strcpy(type, structCustomObject.type);
	int xpos = structCustomObject.xpos;
	int ypos = structCustomObject.ypos;
	int order = structCustomObject.order;
	char fileDir[100];
	strcpy(fileDir, structCustomObject.fileDir);
	int count = structCustomObject.count;

	sprintf(query, "INSERT INTO MAP_INFO(IDX, NAME, TYPE, XPOS, YPOS, Z_ORDER, FILE_DIR, FIELD, COUNT) VALUES('%d', '%s', '%s', '%d', '%d', '%d', '%s', '%s', '%d')", idx, name, type, xpos, ypos, order, fileDir, field, count);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql Insert query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

int deleteSql_inventoryItem(StructCustomObject structCustomObject)
{
	char query[QUERY_BUF_SIZE];

	int idx = structCustomObject.idx;
	char name[50];
	strcpy(name, structCustomObject.name);
	char type[50];
	strcpy(type, structCustomObject.type);
	int xpos = structCustomObject.xpos;
	int ypos = structCustomObject.ypos;
	int order = structCustomObject.order;
	char fileDir[100];
	strcpy(fileDir, structCustomObject.fileDir);
	int count = structCustomObject.count;

	sprintf(query, "DELETE FROM INVENTORY_INFO WHERE IDX = '%d'", idx);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql Delete query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

char * selectSql_userField_info(int sock)
{
	char query[QUERY_BUF_SIZE];
	char * result;

	sprintf(query, "SELECT FIELD FROM USER_LIST WHERE SOCK = '%d'", sock);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s\n", mysql_error(&conn));
		fprintf(stderr, "Sql : %s\n", query);
		return NULL;
	}

	sql_result = mysql_store_result(connection);
	sql_row = mysql_fetch_row(sql_result);

	result = (char*)malloc(strlen(sql_row[0]) + 1);
	strcpy(result, sql_row[0]);

	mysql_free_result(sql_result);

	return result;
}