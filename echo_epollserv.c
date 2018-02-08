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

#define CUR_PATH						"/home/gkf9876/server/Resources/"
//#define CUR_PATH						"/home/pi/server/Resources/"

void error_handling(char * message);
int sendCommand(int sock, int code, char * message, int size);
int readCommand(int sock, int * code, char * buf);

//같은맵, 다른 유저와의 상호작용 알고리즘. 특정 유저의 행동을 같은필드, 다른 사람들에게 알림
int userInteraction(int sock, int code, char * message, int size);

int SeparateString(char * str, char(*arr)[BUF_SIZE], int arrLen, char flag);
void IntToChar(int value, char * result);
void CharToInt(char * value, int * result);

int main(int argc, char * argv[])
{
	int serv_sock, cInt_sock;
	struct sockaddr_in serv_adr, cInt_adr;
	socklen_t adr_sz;
	int str_len, i;
	char sendBuf[BUF_SIZE];
	char readBuf[BUF_SIZE];
	char * fileBuf;
	int code;
	char name[50];
	char content[100];
	char cwd[BUF_SIZE];

	char userMoveInfo[20][BUF_SIZE];
	int len;
	int xpos;
	int ypos;
	char field[100];
	int dateCount = 0;
	int fp;
	int size;

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
			//1초마다 DB시간 업데이트
			if (updateDate(1) == -1)
				error_handling("error Database Date!!");
		}

		if(dateCount / 1000 == 0)
		{
			//10초마다 접속한 유저 확인
			sql_result = selectSql_comfirmTrueNowLoginUser();

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				int sock = atoi(sql_row[0]);
				int login = atoi(sql_row[1]);

				if (login == 0)
				{
					close(sock);
					printf("closed client : %d\n", sock);

					//로그아웃한 시간을 DB에 반영
					if (updateLogoutDateTime(sock) == -1)
					{
						return -1;
					}

					//종료하는 유저 아이디 불러옴.
					StructCustomUser * exitUser = selectSql_UserInfo(sock);
					exitUser->action = ACTION_MAP_OUT;

					//종료시 해당 맵의 다른 유저들에게 자기정보를 보내준다.
					memcpy(sendBuf, exitUser, sizeof(StructCustomUser));
					userInteraction(sock, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));

					if(exitUser != NULL)
						free(exitUser);

					updateSql_UserLogout(sock);
				}
			}
			mysql_free_result(sql_result);

			dateCount = 0;
		}

		if(event_cnt == -1)
		{
			puts("epoll_wait() error");
			break;
		}

		for(i=0; i<event_cnt; i++)
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
				str_len = readCommand(ep_events[i].data.fd, &code, readBuf);

				if(str_len == 0)
				{
					epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
					close(ep_events[i].data.fd);
					printf("closed client : %d\n", ep_events[i].data.fd);

					//로그아웃한 시간을 DB에 반영
					if (updateLogoutDateTime(ep_events[i].data.fd) == -1)
					{
						return -1;
					}

					//종료하는 유저 아이디 불러옴.
					StructCustomUser * exitUser = selectSql_UserInfo(ep_events[i].data.fd);
					exitUser->action = ACTION_MAP_OUT;

					//종료시 해당 맵의 다른 유저들에게 자기정보를 보내준다.
					memcpy(sendBuf, exitUser, sizeof(StructCustomUser));
					userInteraction(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));

					updateSql_UserLogout(ep_events[i].data.fd);
				}
				else
				{
					switch(code)
					{
					case REQUEST_USER_INFO:			//유저 정보 요청시
						printf("code : %d, content : %s\n", code, readBuf);

						StructCustomUser * user = selectSql_UserInfo(ep_events[i].data.fd);
						memcpy(sendBuf, user, sizeof(StructCustomUser));
						str_len = sendCommand(ep_events[i].data.fd, code, sendBuf, sizeof(StructCustomUser));

						if(user != NULL)
							free(user);
						break;
					case CHATTING_PROCESS:			//채팅시
						printf("code : %d, content : %s\n", code, readBuf);

						char chattingInfo[3][BUF_SIZE];
						len = SeparateString(readBuf, chattingInfo, sizeof(chattingInfo) / BUF_SIZE, '\n');

						strcpy(name, chattingInfo[0]);
						strcpy(content, chattingInfo[1]);
						strcpy(field, chattingInfo[2]);

						//데이터베이스에 저장한다.
						insertSql_chatting(field, name, content);

						//같은 필드의 다른 유저들에게 채팅메시지를 전송한다.
						userInteraction(ep_events[i].data.fd, code, readBuf, strlen(readBuf));
						break;
					case REQUEST_LOGIN:				//로그인 승인시
						printf("code : %d, content : %s\n", code, readBuf);
						int count = selectSql_isUser(readBuf);

						if (count > 0)
						{
							str_len = sendCommand(ep_events[i].data.fd, code, "login okey", strlen("login okey"));

							//로그인상태를 바꾼다.
							updateSql_UserLogin(ep_events[i].data.fd, readBuf);

							//해당 유저의 정보를 가져온다.
							StructCustomUser * structCustomUser = selectSql_UserInfo(ep_events[i].data.fd);

							printf("NEW User IN!! (name : %s xpos : %d, ypos : %d)\n", structCustomUser->name, structCustomUser->xpos, structCustomUser->ypos);

							//접속시 해당 맵의 다른 유저들에게 자기정보를 보내준다.
							structCustomUser->action = ACTION_MAP_IN;
							memcpy(sendBuf, structCustomUser, sizeof(StructCustomUser));
							StructCustomUserList * userList = selectSql_fieldUsers(ep_events[i].data.fd);
							StructCustomUser * fieldUser;

							char imsiSendBuf[BUF_SIZE];

							while ((fieldUser = getStructCustomUserList(userList)) != NULL)
							{
								str_len = sendCommand(fieldUser->sock, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));

								//같은맵의 다른 유저 정보를 전해준다.
								fieldUser->action = ACTION_MAP_IN;

								memcpy(imsiSendBuf, fieldUser, sizeof(StructCustomUser));
								sendCommand(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, imsiSendBuf, sizeof(StructCustomUser));
								free(fieldUser);
							}
							free(userList);
							if (structCustomUser != NULL)
								free(structCustomUser);
						}
						else
							str_len = sendCommand(ep_events[i].data.fd, code, "login fail", strlen("login fail"));

						break;
					case USER_MOVE_UPDATE:
						{
							//이동한 유저 정보 가져옴
							StructCustomUser regionUser;
							StructCustomUser currentUser;

							len = SeparateString(readBuf, userMoveInfo, sizeof(userMoveInfo) / BUF_SIZE, '\n');
							memcpy(&currentUser, readBuf, sizeof(StructCustomUser));

							//접속시 해당 맵의 다른 유저들에게 자기정보를 보내준다.
							if (currentUser.action == ACTION_MAP_POTAL)
							{
								//맵에서 나갈때 나가기전에 다른 유저들한테 보냄.
								currentUser.action = ACTION_MAP_OUT;
								memcpy(sendBuf, &currentUser, sizeof(StructCustomUser));
								userInteraction(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));
								updateUserMove(currentUser);

								//맵에서 나가고 나서 다른 맵에 진입할때 다른 유저들한테 보냄.
								currentUser.action = ACTION_MAP_IN;
								memcpy(sendBuf, &currentUser, sizeof(StructCustomUser));
								StructCustomUserList * userList = selectSql_fieldUsers(ep_events[i].data.fd);
								StructCustomUser * fieldUser;

								char imsiSendBuf[BUF_SIZE];

								while ((fieldUser = getStructCustomUserList(userList)) != NULL)
								{
									str_len = sendCommand(fieldUser->sock, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));
									printf("userName : %s, xpos : %d, ypos : %d, field : %s\n", currentUser.name, currentUser.xpos, currentUser.ypos, currentUser.field);

									//이동한 맵의 유저들 정보를 알려준다.
									fieldUser->action = ACTION_MAP_IN;
									memcpy(imsiSendBuf, fieldUser, sizeof(StructCustomUser));
									sendCommand(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, imsiSendBuf, sizeof(StructCustomUser));
									free(fieldUser);
								}
								free(userList);
							}
							else
							{
								//현재 맵에서 이동할때.
								updateUserMove(currentUser);
								currentUser.action = ACTION_MAP_MOVE;
								memcpy(sendBuf, &currentUser, sizeof(StructCustomUser));

								//다른 유저에게 알림
								userInteraction(ep_events[i].data.fd, OTHER_USER_MAP_MOVE, sendBuf, sizeof(StructCustomUser));
							}
						}
						break;
					case OTHER_USER_MAP_MOVE:
						break;
					case REQUEST_JOIN:			//유저 회원가입시
						printf("code : %d, content : %s\n", code, readBuf);
						int result = insertUserInfo(readBuf);

						if (result == -1)
						{
							printf("중복된 아이디입니다.\n");
							sendCommand(ep_events[i].data.fd, code, "join disapprove", strlen("join disapprove"));
						}
						else
						{
							printf("생성되었습니다.\n");
							sendCommand(ep_events[i].data.fd, code, "join okey", strlen("join okey"));
						}
						break;
					case UPDATE_LOGIN_TIME:
						{
							printf("code : %d, content : %s\n", code, readBuf);
							//로그인상태를 바꾼다.
							updateSql_UserLogin(ep_events[i].data.fd, readBuf);
						}
						break;
					//우저가 타일맵 자료 요청시
					case REQUEST_TILED_MAP:
						printf("code : %d, content : %s\n", code, readBuf);
						strcpy(cwd, CUR_PATH);
						strcat(cwd, readBuf);

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
							fprintf(stderr, "File Read error : %s\n", readBuf);
							return -1;
						}

						if (sendCommand(ep_events[i].data.fd, code, fileBuf, size) != -1)
							printf("File Send Success! : %s, Size : %d\n", readBuf, size);
						else
							printf("File Send Fail! : %s\n", readBuf);

						free(fileBuf);
						close(fp);
						break;
					//유저가 이미지 자료 요청시
					case REQUEST_IMAGE:
						printf("code : %d, content : %s\n", code, readBuf);
						strcpy(cwd, CUR_PATH);
						strcat(cwd, readBuf);

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
							fprintf(stderr, "File Read error : %s\n", readBuf);
							return -1;
						}

						if (sendCommand(ep_events[i].data.fd, code, fileBuf, size) != -1)
							printf("File Send Success! : %s, Size : %d\n", readBuf, size);
						else
							printf("File Send Fail! : %s\n", readBuf);

						free(fileBuf);
						close(fp);
						break;
					//유저가 땅에 떨어진 아이템을 먹을시
					case DELETE_FIELD_ITEM:
						printf("code : %d, content : %s\n", code, readBuf);
						StructCustomObject * imsiItemInfo = (StructCustomObject*)malloc(sizeof(StructCustomObject));
						memcpy(imsiItemInfo, readBuf, sizeof(StructCustomObject));

						//맵의 아이템을 지운다.
						deleteMapObject(imsiItemInfo->idx);

						//맵의 아이템을 인벤토리에 추가한다.
						insertInventoryItem(ep_events[i].data.fd, *imsiItemInfo);

						free(imsiItemInfo);

						//다른 유저에게 알림
						userInteraction(ep_events[i].data.fd, code, readBuf, sizeof(StructCustomObject));
						break;
					//맵정보를 불러올때
					case REQUEST_FIELD_INFO:
						printf("code : %d, content : %s\n", code, readBuf);
						StructCustomObject objectInfo[100];
						int objectCount = 0;
						char * imsiSendBuf;

						//맵의 정보를 출력
						sql_result = selectSql_field_info(readBuf);

						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							objectInfo[objectCount].idx = atoi(sql_row[0]);
							strcpy(objectInfo[objectCount].name, sql_row[1]);
							strcpy(objectInfo[objectCount].type, sql_row[2]);
							objectInfo[objectCount].xpos = atoi(sql_row[3]);
							objectInfo[objectCount].ypos = atoi(sql_row[4]);
							objectInfo[objectCount].order = atoi(sql_row[5]);
							strcpy(objectInfo[objectCount].fileDir, sql_row[6]);
							objectInfo[objectCount].count = atoi(sql_row[7]);
							objectCount++;
						}
						mysql_free_result(sql_result);

						imsiSendBuf = (char*)malloc(sizeof(int) + sizeof(StructCustomObject) * objectCount);
						memcpy(&imsiSendBuf[0], &objectCount, sizeof(int));
						memcpy(&imsiSendBuf[4], objectInfo, sizeof(StructCustomObject) * objectCount);

						str_len = sendCommand(ep_events[i].data.fd, code, imsiSendBuf, sizeof(int) + sizeof(StructCustomObject) * objectCount);
						if (str_len <= 0)
							printf("Request Field Info Send Error!!\n");

						free(imsiSendBuf);
						break;
					case REQUEST_INVENTORY_ITEM_INFO:
						printf("code : %d, content : %s\n", code, readBuf);
						StructCustomObject itemInfo[100];
						int itemCount = 0;
						char * imsiSendBuf2;

						//인벤토리의 정보를 출력
						sql_result = selectSql_inventory_info(readBuf);

						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							itemInfo[itemCount].idx = atoi(sql_row[0]);
							strcpy(itemInfo[itemCount].name, sql_row[1]);
							strcpy(itemInfo[itemCount].type, sql_row[2]);
							itemInfo[itemCount].xpos = atoi(sql_row[3]);
							itemInfo[itemCount].ypos = atoi(sql_row[4]);
							itemInfo[itemCount].order = atoi(sql_row[5]);
							strcpy(itemInfo[itemCount].fileDir, sql_row[6]);
							itemInfo[itemCount].count = atoi(sql_row[7]);

							printf("name : %s, type : %s, pos(%d, %d)\n", itemInfo[itemCount].name, itemInfo[itemCount].type, itemInfo[itemCount].xpos, itemInfo[itemCount].ypos);
							itemCount++;
						}
						mysql_free_result(sql_result);

						imsiSendBuf2 = (char*)malloc(sizeof(int) + sizeof(StructCustomObject) * itemCount);
						memcpy(&imsiSendBuf2[0], &itemCount, sizeof(int));
						memcpy(&imsiSendBuf2[4], itemInfo, sizeof(StructCustomObject) * itemCount);

						str_len = sendCommand(ep_events[i].data.fd, code, imsiSendBuf2, sizeof(int) + sizeof(StructCustomObject) * itemCount);
						if (str_len <= 0)
							printf("Request Inventory Info Send Error!!\n");

						free(imsiSendBuf2);
						break;
					case MOVE_INVENTORY_ITEM:
						printf("code : %d, content : %s\n", code, readBuf);
						StructCustomObject * imsiItemInfo2 = (StructCustomObject*)malloc(sizeof(StructCustomObject));
						memcpy(imsiItemInfo2, readBuf, sizeof(StructCustomObject));

						//인벤토리의 아이템 정보를 수정한다.
						updateInventoryItem(ep_events[i].data.fd, *imsiItemInfo2);

						free(imsiItemInfo2);
						break;
					case THROW_ITEM:
						printf("code : %d, content : %s\n", code, readBuf);
						StructCustomObject * imsiItemInfo3 = (StructCustomObject*)malloc(sizeof(StructCustomObject));
						memcpy(imsiItemInfo3, readBuf, sizeof(StructCustomObject));

						//유저가 위치한 필드명을 불러온다.
						sql_result = selectSql_userField_info(ep_events[i].data.fd);
						sql_row = mysql_fetch_row(sql_result);

						//맵에 아이템을 추가한다.
						insertSql_mapObject(sql_row[0], *imsiItemInfo3);

						//인벤토리창의 아이템을 지운다.
						deleteSql_inventoryItem(*imsiItemInfo3);

						//다른 유저에게 알림
						userInteraction(ep_events[i].data.fd, code, readBuf, sizeof(StructCustomObject));

						free(imsiItemInfo3);
						break;
					default:
						printf("code : %d, content : %s\n", code, readBuf);
						break;
					}

					memset(readBuf, 0, BUF_SIZE);
					memset(sendBuf, 0, BUF_SIZE);
				}
			}
		}
	}

	closeMySQL_chatting();
	close(serv_sock);
	close(epfd);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
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
int userInteraction(int sock, int code, char * message, int size)
{
	MYSQL_RES   	*sql_result;
	MYSQL_ROW   	sql_row;
	int str_len;
	int result = 1;
	char errorMessage[50];

	//현재 맵에 있는 유저 목록 출력
	StructCustomUserList * userList = selectSql_fieldUsers(sock);
	StructCustomUser * fieldUser;

	while ((fieldUser = getStructCustomUserList(userList)) != NULL)
	{
		//현재 맵의 다른 유저들에게 알림
		str_len = sendCommand(fieldUser->sock, code, message, size);

		if (str_len <= 0)
		{
			printf("Other User Send Error!! : user(%d), Code(%d), Message(%s)\n", fieldUser->sock, code, message);
			result = -1;
		}

		free(fieldUser);
	}
	free(userList);

	return result;
}

int SeparateString(char * str, char(*arr)[BUF_SIZE], int arrLen, char flag)
{
	char imsi[BUF_SIZE];
	char strarr[BUF_SIZE];
	int count = 0;
	int j = 0;

	strcpy(imsi, str);

	for (int i = 0; i < strlen(imsi) + 1; i++)
	{
		if (imsi[i] == flag)
		{
			strarr[j] = 0;
			if (count >= arrLen)
				break;
			else
				strcpy(arr[count++], strarr);
			j = 0;
			continue;
		}
		else if (i == strlen(imsi))
		{
			strarr[j] = 0;
			if (count >= arrLen)
				break;
			else
				strcpy(arr[count++], strarr);
			break;
		}

		strarr[j] = imsi[i];
		j++;
	}

	return count;
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