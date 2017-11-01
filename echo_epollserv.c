#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include "ChattingDB.h"

#define BUF_SIZE 100
#define EPOLL_SIZE 50

#define REQUEST_USER_INFO				1
#define REQUEST_LOGIN					2
#define CHATTING_PROCESS				3
#define USER_MOVE_UPDATE				4

void error_handling(char * message);
int sendCommand(int sock, int code, char * message);
int readCommand(int sock, int * code, char * buf);

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
	int code;
	char name[50];
	char content[100];

	char userMoveInfo[4][BUF_SIZE];
	int len;
	int xpos;
	int ypos;
	char field[100];

	MYSQL_RES   	*sql_result;
	MYSQL_ROW   	sql_row;


	struct epoll_event * ep_events;
	struct epoll_event event;
	int epfd, event_cnt;

	while(openMySQL_chatting() == -1)
	{
		printf("MySQL Connectioning...\n");
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
		event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);

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

					deleteSql_UserInfo(ep_events[i].data.fd);
				}
				else
				{
					switch(code)
					{
					case REQUEST_USER_INFO:			//유저 정보 요청시
						printf("code : %d, content : %s\n", code, readBuf);
						sql_result = selectSql_UserInfo(ep_events[i].data.fd);
						sql_row = mysql_fetch_row(sql_result);

						sprintf(sendBuf, "%s\n%s\n%s\n%s", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);

						str_len = sendCommand(ep_events[i].data.fd, code, sendBuf);

						mysql_free_result(sql_result);
						break;
					case CHATTING_PROCESS:			//채팅시
						printf("code : %d, content : %s\n", code, readBuf);

						char chattingInfo[2][BUF_SIZE];
						len = SeparateString(readBuf, chattingInfo, sizeof(chattingInfo) / BUF_SIZE, '\n');

						strcpy(name, chattingInfo[0]);
						strcpy(content, chattingInfo[1]);

						insertSql_chatting(0, name, content);

						sql_result = selectSql_chatting(22);

						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							str_len = sendCommand(atoi(sql_row[0]), code, readBuf);
						}
						mysql_free_result(sql_result);

						break;
					case REQUEST_LOGIN:				//로그인 승인시
						printf("code : %d, content : %s\n", code, readBuf);
						sql_result = selectSql_isUser(readBuf);
						sql_row = mysql_fetch_row(sql_result);

						int count = atoi(sql_row[0]);

						if (count > 0)
						{
							str_len = sendCommand(ep_events[i].data.fd, code, "login okey");

							char userName[50];
							sprintf(userName, "%s", readBuf);
							User user;
							strcpy(user.name, userName);
							user.sock = cInt_sock;
							user.xpos = 33;
							user.ypos = 77;
							user.field = 22;
							insertSql_UserInfo(user);
						}
						else
							str_len = sendCommand(ep_events[i].data.fd, code, "login fail");

						mysql_free_result(sql_result);
						break;
					case USER_MOVE_UPDATE:
						len = SeparateString(readBuf, userMoveInfo, sizeof(userMoveInfo) / BUF_SIZE, '\n');

						strcpy(name, userMoveInfo[0]);
						xpos = atoi(userMoveInfo[1]);
						ypos = atoi(userMoveInfo[2]);
						strcpy(field, userMoveInfo[3]);
						updateUserMove(name, xpos, ypos, field);

						printf("userName : %s, xpos : %d, ypos : %d, field : %s\n", name, xpos, ypos, field);
						str_len = sendCommand(ep_events[i].data.fd, code, "user move!!");
						break;
					default:
						break;
					}

					memset(readBuf, 0, BUF_SIZE);
				}
			}
		}
	}

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

int sendCommand(int sock, int code, char * message)
{
	if(message == NULL)
		return -1;

	char buf[BUF_SIZE];
	int len = strlen(message);

	IntToChar(len, &buf[0]);
	IntToChar(code, &buf[4]);

	strcpy(&buf[8], message);

	int writeLen = write(sock, buf, len + 8);

	printf("Send Message : ");
	for(int i=0; i<len + 8; i++)
	{
		printf("%d ", buf[i]);
	}
	printf("\n");

	if(writeLen == -1)
		return -1;
	else
		return len;
}

int readCommand(int sock, int * code, char * buf)
{
	int len;

	if(buf == NULL)
		return -1;

	int readLen = read(sock, buf, 4);

	printf("Read Message : ");
	for(int i=0; i<4; i++)
	{
		printf("%d ", buf[i]);
	}

	if(readLen == -1)
		return -1;
	else if(readLen == 0)
		return 0;

	CharToInt(&buf[0], &len);

	readLen = read(sock, buf, 4);

	for(int i=0; i<4; i++)
	{
		printf("%d ", buf[i]);
	}

	if(readLen == -1)
		return -1;

	CharToInt(&buf[0], code);

	read(sock, buf, len);
	for(int i=0; i<len; i++)
	{
		printf("%d ", buf[i]);
	}
	printf("\n");
	buf[len] = 0;

	return len;
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
	*result = (int)((value[0] << 24) & 0xff000000);
	*result += (int)((value[1] << 16) & 0x00ff0000);
	*result += (int)((value[2] << 8) & 0x0000ff00);
	*result += value[3];
}