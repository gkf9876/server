﻿#include "ChattingDB.h"

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
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));

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

MYSQL_RES * selectSql_isUser(char * user)
{
	char query[255];

	sprintf(query, "SELECT COUNT(ID) AS COUNT FROM USER_LIST WHERE ID = BINARY('%s') AND LOGIN = 0", user);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

MYSQL_RES * selectSql_UserInfo(int sock)
{
	char query[255];

	sprintf(query, "SELECT ID, XPOS, YPOS, FIELD, SEEDIRECTION FROM USER_LIST WHERE SOCK = '%d'", sock);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

int insertSql_chatting(char * field, char * name, char * content)
{
	char query[255];

	if(name == NULL || content == NULL)
	{
		fprintf(stderr, "Mysql insert error : %s", mysql_error(&conn));
		return -1;
	}

	sprintf(query, "INSERT INTO CHATTING(INPUTDATE, NAME, CONTENT, FIELD) VALUES (SYSDATE(), '%s', '%s', '%s')", name, content, field);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
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

MYSQL_RES * selectSql_chatting(char * userName)
{
	char query[255];

	sprintf(query, "SELECT A.SOCK, A.ID, A.XPOS, A.YPOS, A.FIELD FROM USER_LIST A, (SELECT * FROM USER_LIST WHERE ID = BINARY('%s')) B WHERE A.FIELD = B.FIELD", userName);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

int updateSql_UserLogin(User user)
{
	char query[255];

	sprintf(query, "UPDATE USER_LIST SET SOCK = '%d', LOGIN = '1', LAST_LOGIN = SYSDATE() WHERE ID = BINARY('%s')", user.sock, user.name);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

int updateSql_UserLogout(int sock)
{
	char query[255];

	sprintf(query, "UPDATE USER_LIST SET LOGIN = '0', SOCK = '0' WHERE SOCK = '%d' AND LOGIN = '1'", sock);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

int updateUserMove(char * userName, int xpos, int ypos, char * field, int seeDirection)
{
	char query[255];

	sprintf(query, "UPDATE USER_LIST SET XPOS = '%d', YPOS = '%d', FIELD = '%s', SEEDIRECTION = '%d' WHERE ID = BINARY('%s') AND LOGIN = '1'", xpos, ypos, field, seeDirection, userName);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

MYSQL_RES * selectSql_fieldUsers(int sock)
{
	char query[255];

	sprintf(query, "SELECT A.SOCK, A.ID, A.XPOS, A.YPOS, A.SEEDIRECTION FROM USER_LIST A, (SELECT ID, FIELD FROM USER_LIST WHERE SOCK = '%d') B WHERE A.FIELD = B.FIELD AND A.ID <> B.ID AND A.LOGIN = 1", sock);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

MYSQL_RES * selectSql_User(int sock)
{
	char query[255];

	sprintf(query, "SELECT ID,XPOS,YPOS FROM USER_LIST WHERE SOCK = '%d'", sock);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

int updateDate(int idx)
{
	char query[255];

	sprintf(query, "UPDATE SERVER_INFO SET INPUTDATE = SYSDATE() WHERE IDX = '%d'", idx);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

int insertUserInfo(char * userName)
{
	char query[255];

	//중복되는 아이디인지 확인
	sprintf(query, "SELECT count(ID) FROM USER_LIST WHERE ID = '%s'", userName);
	query_stat = mysql_query(connection, query);
	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		if (atoi(sql_row[0]) > 0)
		{
			printf("중복되는 아이디입니다.\n");
			return -1;
		}
	}

	//아이디 등록
	sprintf(query, "INSERT INTO USER_LIST(ID, XPOS, YPOS, FIELD, SEEDIRECTION, JOIN_DATE) VALUE('%s', '18', '11', 'TileMaps/KonyangUniv.Daejeon/JukhunDigitalFacilitie/floor_08/floor.tmx', '29', SYSDATE())", userName);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

int updateLogoutDateTime(int sock)
{
	char query[255];

	sprintf(query, "UPDATE USER_LIST SET LAST_LOGOUT = SYSDATE() WHERE SOCK = '%d'", sock);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

int updateLoginDateTime(int sock)
{
	char query[255];

	sprintf(query, "UPDATE USER_LIST SET LAST_LOGIN = SYSDATE() WHERE SOCK = '%d'", sock);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql update query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

MYSQL_RES * selectSql_comfirmTrueNowLoginUser()
{
	char query[255];

	sprintf(query, "SELECT SOCK, IF(DATE_ADD(SYSDATE(), INTERVAL -10 SECOND) <= LAST_LOGIN, TRUE, FALSE) AS LOGIN FROM user_list WHERE LOGIN = '1'");

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

MYSQL_RES * selectSql_field_info(char * field)
{
	char query[255];

	sprintf(query, "SELECT A.idx, A.name, A.type, A.xpos, A.ypos, A.order, A.file_dir, A.count FROM MAP_INFO A WHERE FIELD = '%s'", field);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}