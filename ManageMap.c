#include "ManageMap.h"
#include "dumper.h"

MYSQL       	*manageMap_connection=NULL, manageMap_conn;
MYSQL_RES   	*manageMap_sql_result;
MYSQL_ROW   	manageMap_sql_row;
int 		manageMap_query_stat;

int openMySQL_manageMap()
{
	mysql_init(&manageMap_conn);
	mysql_options(&manageMap_conn, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&manageMap_conn, MYSQL_INIT_COMMAND, "SET NAMES utf8");

	manageMap_connection = mysql_real_connect(&manageMap_conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if (manageMap_connection == NULL)
	{
		fprintf(stderr, "Manage Map Mysql connection error : %s\n", mysql_error(&manageMap_conn));

		return -1;
	}

	return 1;
}

int closeMySQL_manageMap()
{
	if(manageMap_connection != NULL)
	{
		mysql_close(manageMap_connection);
		return 1;
	}
	else
		return -1;	
}

//모든맵의 몬스터 마리수와 최대 마리수 확인
MYSQL_RES * selectSql_mapMonsterList()
{
	char query[QUERY_BUF_SIZE];
	strcpy(query, "SELECT A.FIELD, ");
	strcat(query, "COUNT(IF(B.NAME = A.MONSTER1, TRUE, NULL)) AS MONSTER1, ");
	strcat(query, "COUNT(IF(B.NAME = A.MONSTER2, TRUE, NULL)) AS MONSTER2, ");
	strcat(query, "COUNT(IF(B.NAME = A.MONSTER3, TRUE, NULL)) AS MONSTER3, ");
	strcat(query, "IFNULL(A.MONSTER1_COUNT, 0) AS MONSTER1_COUNT, ");
	strcat(query, "IFNULL(A.MONSTER2_COUNT, 0) AS MONSTER2_COUNT, ");
	strcat(query, "IFNULL(A.MONSTER3_COUNT, 0) AS MONSTER3_COUNT ");
	strcat(query, "FROM MAP_LIST A ");
	strcat(query, "LEFT JOIN(SELECT * FROM MAP_INFO) B ");
	strcat(query, "ON A.FIELD = B.FIELD ");
	strcat(query, "GROUP BY A.FIELD, A.MONSTER1_COUNT, A.MONSTER2_COUNT, A.MONSTER3_COUNT ");

	manageMap_query_stat = mysql_query(manageMap_connection, query);
	if (manageMap_query_stat != 0)
	{
		fprintf(stderr, "Manage Map Mysql select query error : %s\n", mysql_error(&manageMap_conn));
		fprintf(stderr, "Manage Map Sql : %s\n", query);
	}

	manageMap_sql_result = mysql_store_result(manageMap_connection);

	return manageMap_sql_result;
}

int insertMapMonster(char * field, char * name, int xpos, int ypos)
{
	char query[QUERY_BUF_SIZE];

	sprintf(query, "INSERT INTO MAP_INFO(FIELD, IDX, NAME, TYPE, XPOS, YPOS, FILE_DIR) ");
	sprintf(&query[strlen(query)], "SELECT '%s' AS FIELD, IDX, NAME, ", field);
	sprintf(&query[strlen(query)], "'monster' AS TYPE, '%d' AS XPOS, '%d' AS YPOS, FILE_DIR ", xpos, ypos);
	sprintf(&query[strlen(query)], "FROM MONSTER_LIST ");
	sprintf(&query[strlen(query)], "WHERE NAME = '%s'", name);

	manageMap_query_stat = mysql_query(manageMap_connection, query);

	if (manageMap_query_stat != 0)
	{
		fprintf(stderr, "Manage Map Mysql insert query error : %s\n", mysql_error(&manageMap_conn));
		fprintf(stderr, "Sql : %s\n", query);
		return -1;
	}

	return 1;
}

//맵의 몬스터 정보를 확인
MYSQL_RES * selectSql_MapMonster(char * field)
{
	char query[QUERY_BUF_SIZE];
	sprintf(query, "SELECT * FROM MAP_LIST WHERE FIELD = '%s'", field);

	manageMap_query_stat = mysql_query(manageMap_connection, query);
	if (manageMap_query_stat != 0)
	{
		fprintf(stderr, "Manage Map Mysql select query error : %s\n", mysql_error(&manageMap_conn));
		fprintf(stderr, "Manage Map Sql : %s\n", query);
	}

	manageMap_sql_result = mysql_store_result(manageMap_connection);

	return manageMap_sql_result;
}

//맵관리 쓰레드
void * manageMapThread_main(void * arg)
{
	MYSQL_RES   	*manageMap_sql_result;
	MYSQL_ROW   	manageMap_sql_row;
	MYSQL_RES   	*imsiManageMap_sql_result;
	MYSQL_ROW   	imsiManageMap_sql_row;

	char field[100];
	char file_dir[100];
	int currentMonster1Count;
	int currentMonster2Count;
	int currentMonster3Count;
	int monster1Count;
	int monster2Count;
	int monster3Count;

	tmx_map *m = NULL;
	tmx_tileset_manager *ts_mgr = NULL;

	tmx_alloc_func = dbg_alloc; /* alloc/free dbg */
	tmx_free_func = dbg_free;

	srand(time(NULL));

	while (openMySQL_manageMap() == -1)
	{
		printf("MySQL Connectioning...\n");
	}

	while (1)
	{
		printf("manageMapThread_main run!\n");

		//현재 맵에 있는 유저 목록 출력
		manageMap_sql_result = selectSql_mapMonsterList();

		while ((manageMap_sql_row = mysql_fetch_row(manageMap_sql_result)) != NULL)
		{
			strcpy(field, manageMap_sql_row[0]);
			currentMonster1Count = atoi(manageMap_sql_row[1]);
			currentMonster2Count = atoi(manageMap_sql_row[2]);
			currentMonster3Count = atoi(manageMap_sql_row[3]);
			monster1Count = atoi(manageMap_sql_row[4]);
			monster2Count = atoi(manageMap_sql_row[5]);
			monster3Count = atoi(manageMap_sql_row[6]);

			sprintf(file_dir, "Resources/%s", field);

			//맵 파일을 열어본다.
			if (isMap(file_dir))
			{
				m = tmx_tsmgr_load(ts_mgr, file_dir);

				//현재 맵의 몬스터 목록을 불러온다. 그리고 맵에 몬스터를 넣어준다.
				imsiManageMap_sql_result = selectSql_MapMonster(field);

				while ((imsiManageMap_sql_row = mysql_fetch_row(imsiManageMap_sql_result)) != NULL)
				{
					int x;
					int y;

					//첫번째 몬스터를 맵에 구현한다.
					for (int i = currentMonster1Count; i < monster1Count; i++)
					{
						//맵에 놓을만한 자리에다가 몬스터를 놓는다.
						x = rand() % m->width;
						y = rand() % m->height;

						if (dump_map(m, 3, x, y) == 0 && dump_map(m, 0, x, y) == 130)
							insertMapMonster(field, imsiManageMap_sql_row[2], x, y);
						else
							i--;
					}

					//두번째 몬스터를 맵에 구현한다.
					for (int i = currentMonster2Count; i < monster2Count; i++)
					{
						//맵에 놓을만한 자리에다가 몬스터를 놓는다.
						x = rand() % m->width;
						y = rand() % m->height;

						if (dump_map(m, 3, x, y) == 0 && dump_map(m, 0, x, y) == 130)
							insertMapMonster(field, imsiManageMap_sql_row[3], x, y);
						else
							i--;
					}

					//세번째 몬스터를 맵에 구현한다.
					for (int i = currentMonster3Count; i < monster3Count; i++)
					{
						//맵에 놓을만한 자리에다가 몬스터를 놓는다.
						x = rand() % m->width;
						y = rand() % m->height;

						if (dump_map(m, 3, x, y) == 0 && dump_map(m, 0, x, y) == 130)
							insertMapMonster(field, imsiManageMap_sql_row[4], x, y);
						else
							i--;
					}
				}

				tmx_map_free(m);
				m = NULL;
			}

			if (ts_mgr)
			{
				tmx_free_tileset_manager(ts_mgr);
			}
		}
		mysql_free_result(manageMap_sql_result);

		sleep(5);
	}

	closeMySQL_manageMap();
}