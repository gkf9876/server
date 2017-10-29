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

MYSQL_RES * selectSql_UserInfo(int number)
{
	char query[255];

	sprintf(query, "SELECT NAME, XPOS, YPOS, FIELD FROM USERS WHERE SOCK = '%d'", number);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

int insertSql_chatting(int field, char * name, char * content)
{
	char query[255];

	if(name == NULL || content == NULL)
	{
		fprintf(stderr, "Mysql insert error : %s", mysql_error(&conn));
		return -1;
	}

	sprintf(query, "insert into chatting(inputdate, name, content) values (SYSDATE(), '%s', '%s')", name, content);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

int deleteSql_chatting(int field)
{
}

int updateSql_chatting(int field)
{
}

MYSQL_RES * selectSql_chatting(int field)
{
	char query[255];

	sprintf(query, "SELECT SOCK, NAME, XPOS, YPOS, FIELD FROM USERS WHERE FIELD = '%d'", field);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
	}

	sql_result = mysql_store_result(connection);

	return sql_result;
}

int insertSql_UserInfo(User user)
{
	char query[255];

	sprintf(query, "INSERT INTO USERS(SOCK, NAME, PASSWORD, XPOS, YPOS, FIELD) VALUES ('%d', '%s', '%s', '%d', '%d', '%d')"
		, user.sock, user.name, user.password, user.xpos, user.ypos, user.field);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}

int deleteSql_UserInfo(int sock)
{
	char query[255];

	sprintf(query, "delete from users where sock = '%d'", sock);

	query_stat = mysql_query(connection, query);

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql insert query error : %s", mysql_error(&conn));
		fprintf(stderr, "Sql : %s", query);
		return -1;
	}

	return 1;
}