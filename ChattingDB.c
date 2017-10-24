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

int selectSql_chatting(int field)
{
	char query[255];

	sprintf(query, "select idx, name, content from chatting where field = '%d'", field);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql select query error : %s", mysql_error(&conn));
		return -1;
	}

	sql_result = mysql_store_result(connection);

	printf("%s %s %s\n", "IDX", "작성자", "내용");

	while ( (sql_row = mysql_fetch_row(sql_result)) != NULL )
	{
		printf("%s %s %s\n", sql_row[0], sql_row[1], sql_row[2]);
	}

	mysql_free_result(sql_result);

	return 1;
}
