#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <pthread.h>
#include <time.h>

#include "ChattingDB.h"
#include "CustomObject.h"
#include "CustomUser.h"
#include "ManageMap.h"

#define BUF_SIZE 1024
#define EPOLL_SIZE 50

#define REQUEST_USER_INFO				1
#define REQUEST_LOGIN					2
#define CHATTING_PROCESS				3
#define USER_MOVE_UPDATE				4
#define OTHER_USER_MAP_MOVE				5
#define REQUEST_JOIN					6
#define UPDATE_LOGIN_TIME				7
#define REQUEST_TILED_MAP				8
#define REQUEST_IMAGE					9
#define DELETE_FIELD_ITEM				10
#define REQUEST_FIELD_INFO				11
#define REQUEST_INVENTORY_ITEM_INFO		12
#define MOVE_INVENTORY_ITEM				13
#define THROW_ITEM						14
#define REGEN_MONSTER					15
#define ATTACK_FILED_OBJECT				16

#define CUR_PATH						"/home/gkf9876/server/Resources/"
//#define CUR_PATH						"/home/pi/server/Resources/"

void error_handling(char * message);
int sendCommand(int sock, int code, char * message, int size);
int readCommand(int sock, int * code, char * buf);

//같은맵, 다른 유저와의 상호작용 알고리즘. 특정 유저의 행동을 같은필드, 다른 사람들에게 알림
void userInteraction(int sock, int code, char * message, int size);

int SeparateString(char * str, char(*arr)[BUF_SIZE], int arrLen, char flag);
void IntToChar(int value, char * result);
void CharToInt(char * value, int * result);

int sendFileData(int sock, int code, char * filename);

int logout_exitUser(int sock);

pthread_mutex_t mutex;

int main(int argc, char * argv[])
{
	int serv_sock, cInt_sock;
	struct sockaddr_in serv_adr, cInt_adr;
	socklen_t adr_sz;
	char sendBuf[BUF_SIZE];
	char readBuf[BUF_SIZE];
	int code;
	int dateCount = 0;

	MYSQL_RES   	*sql_result;
	MYSQL_ROW   	sql_row;


	struct epoll_event * ep_events;
	struct epoll_event event;
	int epfd, event_cnt;

	//맵 관리 쓰레드 변수
	pthread_t mapManagementThread;

	while(openMySQL_chatting() == -1)
	{
		printf("MySQL Connectioning...\n");
	}

	if (pthread_create(&mapManagementThread, NULL, manageMapThread_main, NULL) != 0)
	{
		puts("pthread_create() error");
		return -1;
	}

	pthread_mutex_init(&mutex, NULL);

	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	epfd = epoll_create(EPOLL_SIZE);
	ep_events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);

	event.events = EPOLLIN;
	event.data.fd = serv_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

	while(1)
	{
		event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, 10);

		if (dateCount / 100 == 0)
		{
			pthread_mutex_lock(&mutex);

			//1초마다 DB시간 업데이트
			if (updateDate(1) == -1)
				error_handling("updateDate error");

			pthread_mutex_unlock(&mutex);
		}
        
		if(dateCount / 1000 == 0)
		{
			pthread_mutex_lock(&mutex);

			//10초마다 접속한 유저 확인
			sql_result = selectSql_comfirmTrueNowLoginUser();

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				int sock = atoi(sql_row[0]);
				int login = atoi(sql_row[1]);
                
				if (login == 0)
				{
                    if(logout_exitUser(sock) == -1)
                        error_handling("10update error");
				}
			}
			mysql_free_result(sql_result);

			dateCount = 0;

			pthread_mutex_unlock(&mutex);
		}
        
		if(event_cnt == -1)
		{
			puts("epoll_wait() error");
			break;
		}

		for(int i=0; i<event_cnt; i++)
		{
			if(ep_events[i].data.fd == serv_sock)
			{
				adr_sz = sizeof(cInt_adr);
				cInt_sock = accept(serv_sock, (struct sockaddr*)&cInt_adr, &adr_sz);
				event.events = EPOLLIN;
				event.data.fd = cInt_sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, cInt_sock, &event);
				printf("connected client : %d\n", cInt_sock);
			}
			else
			{
				if(readCommand(ep_events[i].data.fd, &code, readBuf) <= 0)
				{
					printf("code : %d, readBuf : %s\n", code, readBuf);
					pthread_mutex_lock(&mutex);

                    if(logout_exitUser(ep_events[i].data.fd) == -1)
                        error_handling("readCommand error");

					pthread_mutex_unlock(&mutex);
				}
				else
				{
					pthread_mutex_lock(&mutex);

					printf("code : %d, readBuf : %s\n", code, readBuf);

					switch(code)
					{
					case REQUEST_USER_INFO:			//유저 정보 요청시
						{
							StructCustomUser * user = selectSql_UserInfo(ep_events[i].data.fd);

							if (user != NULL)
							{
								memcpy(sendBuf, user, sizeof(StructCustomUser));

								if (sendCommand(ep_events[i].data.fd, code, sendBuf, sizeof(StructCustomUser)) <= 0)
								{
                                    if(logout_exitUser(ep_events[i].data.fd) == -1)
                                        error_handling("REQUEST_USER_INFO_1 error");
								}

								free(user);
							}
							else
								error_handling("REQUEST_USER_INFO_2 error!!");
						}
						break;
					case CHATTING_PROCESS:			//채팅시
						{
							StructCustomChatting chattingInfo;
							memcpy(&chattingInfo, readBuf, sizeof(StructCustomChatting));

							//데이터베이스에 저장한다.
							if (insertSql_chatting(chattingInfo.field, chattingInfo.name, chattingInfo.content) == -1)
								error_handling("CHATTING_PROCESS_1 error!!");

							//같은 필드의 다른 유저들에게 채팅메시지를 전송한다.
							userInteraction(ep_events[i].data.fd, code, readBuf, sizeof(StructCustomChatting));
						}
						break;
					case REQUEST_LOGIN:				//로그인 승인시
						{
							int count = selectSql_isUser(readBuf);

							if (count > 0)
							{
								StructCustomUser * fieldUser;
								StructCustomUserList * userList;
								StructCustomUser * structCustomUser;
								char imsiSendBuf[BUF_SIZE];

								if (sendCommand(ep_events[i].data.fd, code, "login okey", strlen("login okey")) <= 0)
								{
                                    if(logout_exitUser(ep_events[i].data.fd) == -1)
                                        error_handling("REQUEST_LOGIN_1 error");
									continue;
								}

								//로그인상태를 바꾼다.
								if (updateSql_UserLogin(ep_events[i].data.fd, readBuf) == -1)
									error_handling("REQUEST_LOGIN_2 error");

								userList = selectSql_fieldUsers(ep_events[i].data.fd);

								if (userList == NULL)
									error_handling("REQUEST_LOGIN_3 error");

								structCustomUser = selectSql_UserInfo(ep_events[i].data.fd);

								if(structCustomUser == NULL)
									error_handling("REQUEST_LOGIN_4 error");

								structCustomUser->action = ACTION_MAP_IN;

								//접속시 해당 맵의 다른 유저들에게 자기정보를 보내준다.
								memcpy(sendBuf, structCustomUser, sizeof(StructCustomUser));

								while ((fieldUser = getStructCustomUserList(userList)) != NULL)
								{
									if(sendCommand(fieldUser->sock, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser)) <= 0)
									{
                                        if(logout_exitUser(fieldUser->sock) == -1)
                                            error_handling("REQUEST_LOGIN_5 error");
										continue;
									}

									//같은맵의 다른 유저 정보를 전해준다.
									fieldUser->action = ACTION_MAP_IN;

									memcpy(imsiSendBuf, fieldUser, sizeof(StructCustomUser));

									if (sendCommand(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, imsiSendBuf, sizeof(StructCustomUser)) <= 0)
									{
                                        if(logout_exitUser(ep_events[i].data.fd) == -1)
                                            error_handling("REQUEST_LOGIN_6 error");
										continue;
									}

									if (fieldUser != NULL)
										free(fieldUser);
								}

								if (userList != NULL)
									free(userList);
								if (structCustomUser != NULL)
									free(structCustomUser);
							}
							else
								if (sendCommand(ep_events[i].data.fd, code, "login fail", strlen("login fail")) <= 0)
								{
                                    if(logout_exitUser(ep_events[i].data.fd) == -1)
                                        error_handling("REQUEST_LOGIN_7 error");
									continue;
								}
						}
						break;
					case USER_MOVE_UPDATE:
						{
							//이동한 유저 정보 가져옴
							StructCustomUser currentUser;

							memcpy(&currentUser, readBuf, sizeof(StructCustomUser));

							//접속시 해당 맵의 다른 유저들에게 자기정보를 보내준다.
							if (currentUser.action == ACTION_MAP_POTAL)
							{
								StructCustomUserList * userList;
								StructCustomUser * fieldUser;
								char imsiSendBuf[BUF_SIZE];

								//맵에서 나갈때 나가기전에 다른 유저들한테 보냄.
								currentUser.action = ACTION_MAP_OUT;
								memcpy(sendBuf, &currentUser, sizeof(StructCustomUser));
								userInteraction(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));

								if(updateUserMove(currentUser) == -1)
									error_handling("USER_MOVE_UPDATE_1 error");

								//맵에서 나가고 나서 다른 맵에 진입할때 다른 유저들한테 보냄.
								currentUser.action = ACTION_MAP_IN;
								memcpy(sendBuf, &currentUser, sizeof(StructCustomUser));
								userList = selectSql_fieldUsers(ep_events[i].data.fd);

								if(userList == NULL)
									error_handling("USER_MOVE_UPDATE_2 error");

								while ((fieldUser = getStructCustomUserList(userList)) != NULL)
								{
									if (sendCommand(fieldUser->sock, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser)) <= 0)
									{
                                        if(logout_exitUser(fieldUser->sock) == -1)
                                            error_handling("USER_MOVE_UPDATE_3 error");
										continue;
									}

									//이동한 맵의 유저들 정보를 알려준다.
									fieldUser->action = ACTION_MAP_IN;
									memcpy(imsiSendBuf, fieldUser, sizeof(StructCustomUser));

									if (sendCommand(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, imsiSendBuf, sizeof(StructCustomUser)) <= 0)
									{
                                        if(logout_exitUser(ep_events[i].data.fd) == -1)
                                            error_handling("USER_MOVE_UPDATE_4 error");
										continue;
									}

									if (fieldUser != NULL)
										free(fieldUser);
								}

								if(userList != NULL)
									free(userList);
							}
							else
							{
								//현재 맵에서 이동할때.
								if(updateUserMove(currentUser) <= 0)
									error_handling("USER_MOVE_UPDATE_5 error");

								memcpy(sendBuf, &currentUser, sizeof(StructCustomUser));

								//다른 유저에게 알림
								userInteraction(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));
							}
						}
						break;
					case OTHER_USER_MAP_MOVE:
						break;
					case REQUEST_JOIN:			//유저 회원가입시
						{
							int result = insertUserInfo(readBuf);

							if (result == -1)
								sendCommand(ep_events[i].data.fd, code, "join disapprove", strlen("join disapprove"));
							else
								sendCommand(ep_events[i].data.fd, code, "join okey", strlen("join okey"));
						}
						break;
					case UPDATE_LOGIN_TIME:
						{
							//로그인 시간을 업데이트한다.
							if (updateSql_UserLogin(ep_events[i].data.fd, readBuf) == -1)
								error_handling("UPDATE_LOGIN_TIME_1 error");
						}
						break;
					//우저가 타일맵 자료 요청시
					case REQUEST_TILED_MAP:
						{
							if(sendFileData(ep_events[i].data.fd, code, readBuf) == -1)
								error_handling("REQUEST_TILED_MAP_1 error");
						}
						break;
					//유저가 이미지 자료 요청시
					case REQUEST_IMAGE:
						{
							if (sendFileData(ep_events[i].data.fd, code, readBuf) == -1)
								error_handling("REQUEST_IMAGE_1 error");
						}
						break;
					//유저가 땅에 떨어진 아이템을 먹을시
					case DELETE_FIELD_ITEM:
						{
							StructCustomObject imsiItemInfo;
							memcpy(&imsiItemInfo, readBuf, sizeof(StructCustomObject));

							//맵의 아이템을 지운다.
							if(deleteMapObject(imsiItemInfo.object_number) == -1)
								error_handling("DELETE_FIELD_ITEM_1 error");

							//맵의 아이템을 인벤토리에 추가한다.
							if(insertInventoryItem(ep_events[i].data.fd, imsiItemInfo) == -1)
								error_handling("DELETE_FIELD_ITEM_2 error");

							//다른 유저에게 알림
							userInteraction(ep_events[i].data.fd, code, readBuf, sizeof(StructCustomObject));
						}
						break;
					//맵정보를 불러올때
					case REQUEST_FIELD_INFO:
						{
							StructCustomObjectList * objectInfo = NULL;
							StructCustomObject * object = NULL;
							int objectCount;
							int bufferPlag;
							char * imsiSendBuf;

							//맵의 정보를 출력
							objectInfo = selectSql_field_info(readBuf);
							objectCount = getObjectCount(objectInfo);

							imsiSendBuf = (char*)malloc(sizeof(int) + sizeof(StructCustomObject) * objectCount);
							memcpy(&imsiSendBuf[0], &objectCount, sizeof(int));
							bufferPlag = 4;

							while ((object = getStructCustomObjectList(objectInfo)) != NULL)
							{
								memcpy(&imsiSendBuf[bufferPlag], object, sizeof(StructCustomObject));
								bufferPlag += sizeof(StructCustomObject);

								if (object != NULL)
									free(object);
							}

							if (sendCommand(ep_events[i].data.fd, code, imsiSendBuf, sizeof(int) + sizeof(StructCustomObject) * objectCount) <= 0)
							{
                                if(logout_exitUser(ep_events[i].data.fd) == -1)
                                    error_handling("REQUEST_FIELD_INFO_1 error");
							}

							free(imsiSendBuf);
							if (objectInfo != NULL)
								free(objectInfo);
						}
						break;
					case REQUEST_INVENTORY_ITEM_INFO:
						{
							StructCustomObjectList * objectInfo = NULL;
							StructCustomObject * object = NULL;
							int objectCount;
							int bufferPlag;
							char * imsiSendBuf;

							//아이템창의 정보를 출력
							objectInfo = selectSql_inventory_info(readBuf);
							objectCount = getObjectCount(objectInfo);

							imsiSendBuf = (char*)malloc(sizeof(int) + sizeof(StructCustomObject) * objectCount);
							memcpy(&imsiSendBuf[0], &objectCount, sizeof(int));
							bufferPlag = 4;

							while ((object = getStructCustomObjectList(objectInfo)) != NULL)
							{
								memcpy(&imsiSendBuf[bufferPlag], object, sizeof(StructCustomObject));
								bufferPlag += sizeof(StructCustomObject);

								if (object != NULL)
									free(object);
							}

							if (sendCommand(ep_events[i].data.fd, code, imsiSendBuf, sizeof(int) + sizeof(StructCustomObject) * objectCount) <= 0)
							{
                                if(logout_exitUser(ep_events[i].data.fd) == -1)
                                    error_handling("REQUEST_INVENTORY_ITEM_INFO_1 error");
							}

							free(imsiSendBuf);
							if (objectInfo != NULL)
								free(objectInfo);
						}
						break;
					case MOVE_INVENTORY_ITEM:
						{
							StructCustomObject imsiItemInfo;
							memcpy(&imsiItemInfo, readBuf, sizeof(StructCustomObject));

							//인벤토리의 아이템 정보를 수정한다.
							if (updateInventoryItem(ep_events[i].data.fd, imsiItemInfo) == -1)
								error_handling("MOVE_INVENTORY_ITEM_1 error");
						}
						break;
					case THROW_ITEM:
						{
							char * field;
							StructCustomObject imsiItemInfo;
							memcpy(&imsiItemInfo, readBuf, sizeof(StructCustomObject));

							//유저가 위치한 필드명을 불러온다.
							field = selectSql_userField_info(ep_events[i].data.fd);

							//맵에 아이템을 추가한다.
							insertSql_mapObject(field, imsiItemInfo);

							//인벤토리창의 아이템을 지운다.
							deleteSql_inventoryItem(imsiItemInfo);

							//다른 유저에게 알림
							userInteraction(ep_events[i].data.fd, code, readBuf, sizeof(StructCustomObject));

							if(field != NULL)
								free(field);
						}
						break;
					case ATTACK_FILED_OBJECT:
						{
							StructCustomObject monsterInfo;
							memcpy(&monsterInfo, readBuf, sizeof(StructCustomObject));

							//몬스터의 에너지를 변경한다.
							if (updateSql_monsterHp(monsterInfo) == -1)
								error_handling("KILL_FILED_MONSTER_1 error");

							//다른 유저에게 알림
							userInteraction(ep_events[i].data.fd, code, readBuf, sizeof(StructCustomObject));
						}
						break;
					default:
						printf("code : %d, content : %s\n", code, readBuf);
						break;
					}

					pthread_mutex_unlock(&mutex);
					memset(readBuf, 0, BUF_SIZE);
					memset(sendBuf, 0, BUF_SIZE);
				}
			}
		}
	}

	pthread_mutex_destroy(&mutex);
	closeMySQL_chatting();
	close(serv_sock);
	close(epfd);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(-1);
}

int sendCommand(int sock, int code, char * message, int size)
{
	int writeLen;
	char * buf;

	if(message == NULL)
		return -1;

	buf = (char*)malloc(size + 9);
	IntToChar(size, &buf[0]);
	IntToChar(code, &buf[4]);
	//strcpy(&buf[8], message);

	writeLen = write(sock, buf, 8);
	writeLen += write(sock, message, size);

	free(buf);

	if(writeLen <= 0)
		return -1;
	else
		return writeLen;
}

int readCommand(int sock, int * code, char * buf)
{
	int len;
	int readLen;

	if(buf == NULL)
		return -1;

	if((readLen = read(sock, buf, 4)) == -1)
		return -1;
	else if(readLen == 0)
		return 0;

	CharToInt(&buf[0], &len);

	if((readLen = read(sock, buf, 4)) == -1)
		return -1;

	CharToInt(&buf[0], code);

	if ((readLen = read(sock, buf, len)) == -1)
		return -1;

	buf[len] = 0;

	return len;
}

//같은맵, 다른 유저와의 상호작용 알고리즘. 특정 유저의 행동을 같은필드, 다른 사람들에게 알림
void userInteraction(int sock, int code, char * message, int size)
{
	int result = 1;
	StructCustomUserList * userList;
	StructCustomUser * fieldUser;

	//현재 맵에 있는 유저 목록 출력
	userList = selectSql_fieldUsers(sock);

	if (userList == NULL)
		error_handling("userInteraction error");

	while ((fieldUser = getStructCustomUserList(userList)) != NULL)
	{
		//현재 맵의 다른 유저들에게 알림
		if (sendCommand(fieldUser->sock, code, message, size) <= 0)
		{
			close(fieldUser->sock);
			printf("closed client : %d\n", fieldUser->sock);
			printf("Other User Send Error!! : user(%d)\n", fieldUser->sock);

			if (updateSql_UserLogout(fieldUser->sock) == -1)
				error_handling("userInteraction error");
		}

		free(fieldUser);
	}
	if(userList != NULL)
		free(userList);
}

void IntToChar(int value, char * result)
{
	result[0] = (value & 0xff000000) >> 24;
	result[1] = (value & 0x00ff0000) >> 16;
	result[2] = (value & 0x0000ff00) >> 8;
	result[3] = (value & 0x000000ff);
}

void CharToInt(char * value, int * result)
{
	*result = (int)(((unsigned char)value[0] << 24) & 0xff000000);
	*result += (int)(((unsigned char)value[1] << 16) & 0x00ff0000);
	*result += (int)(((unsigned char)value[2] << 8) & 0x0000ff00);
	*result += (unsigned char)value[3];
}

int sendFileData(int sock, int code, char * filename)
{
	int fp;
	int size;
	char * fileBuf;
	char cwd[BUF_SIZE];

	strcpy(cwd, CUR_PATH);
	strcat(cwd, filename);

	if ((fp = open(cwd, O_RDONLY)) == -1)
	{
		fprintf(stderr, "File Open error : %s\n", cwd);
		return -1;
	}

	lseek(fp, 0, SEEK_END);							// 파일 포인터를 파일의 끝으로 이동시킴
	size = lseek(fp, 0, SEEK_CUR);					// 파일 포인터의 현재 위치를 얻음
	fileBuf = (char*)malloc(size + 1);
	memset(fileBuf, 0, size + 1);					// 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
	lseek(fp, 0, SEEK_SET);							// 파일 포인터를 파일의 처음으로 이동시킴

	if (read(fp, fileBuf, size) <= 0)
	{
		fprintf(stderr, "File Read error : %s\n", filename);
		return -1;
	}

	if (sendCommand(sock, code, fileBuf, size) <= 0)
	{
        if(logout_exitUser(sock) == -1)
            error_handling("sendFileData error");
		printf("File Send Fail! : %s\n", filename);

		free(fileBuf);
		close(fp);
		return -1;
	}

	free(fileBuf);
	close(fp);
	return 1;
}

int logout_exitUser(int sock)
{
    char sendBuf[BUF_SIZE];
    //종료하는 유저 아이디 불러옴.
    StructCustomUser * exitUser = selectSql_UserInfo(sock);
    
    //로그인한 사용자일시 처리.
    if(exitUser != NULL)
    {
        exitUser->action = ACTION_MAP_OUT;
        
        //로그아웃한 시간을 DB에 반영
        if (updateLogoutDateTime(sock) == -1)
            error_handling("updateLogoutDateTime error");
        
        //종료시 해당 맵의 다른 유저들에게 자기정보를 보내준다.
        memcpy(sendBuf, exitUser, sizeof(StructCustomUser));
        userInteraction(sock, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));
        free(exitUser);
    }
    
    //epoll_ctl(epfd, EPOLL_CTL_DEL, sock, NULL);
    close(sock);
    printf("closed client : %d\n", sock);
    
    //유저 정보를 DB에 업데이트
    if(updateSql_UserLogout(sock) == -1)
        error_handling("updateSql_UserLogout error");
    
    return 1;
}
