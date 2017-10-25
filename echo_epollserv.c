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

void error_handling(char * message);
int sendCommand(int sock, int code, char * message);
int readCommand(int sock, int * code, char * buf);

int main(int argc, char * argv[])
{
	int serv_sock, cInt_sock;
	struct sockaddr_in serv_adr, cInt_adr;
	socklen_t adr_sz;
	int str_len, i;
	//char buf[BUF_SIZE];
	char sendBuf[BUF_SIZE];
	char readBuf[BUF_SIZE];
	int code;
	char name[50];
	char content[100];


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
				}
				else
				{
					switch(code)
					{
					case 1:
						printf("code : %d, content : %s\n", code, readBuf);
						selectSql_chatting(0);
						break;
					case 2:
						printf("code : %d, content : %s\n", code, readBuf);

						strcpy(name, strtok(readBuf, "\n"));
						strcpy(content, strtok(NULL, "\n"));

						insertSql_chatting(0, name, content);
						break;
					default:
						break;
					}

					str_len = sendCommand(ep_events[i].data.fd, code, readBuf);
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

	buf[0] = (len & 0xff000000) >> 24;
	buf[1] = (len & 0x00ff0000) >> 16;
	buf[2] = (len & 0x0000ff00) >> 8;
	buf[3] = (len & 0x000000ff);

	buf[4] = (code & 0xff000000) >> 24;
	buf[5] = (code & 0x00ff0000) >> 16;
	buf[6] = (code & 0x0000ff00) >> 8;
	buf[7] = (code & 0x000000ff);
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

	int len = (int)((buf[0] << 24) & 0xff000000);
	len += (int)((buf[1] << 16) & 0x00ff0000);
	len += (int)((buf[2] << 8) & 0x0000ff00);
	len += buf[3];

	readLen = read(sock, buf, 4);

	for(int i=0; i<4; i++)
	{
		printf("%d ", buf[i]);
	}

	if(readLen == -1)
		return -1;

	*code = (int)((buf[0] << 24) & 0xff000000);
	*code += (int)((buf[1] << 16) & 0x00ff0000);
	*code += (int)((buf[2] << 8) & 0x0000ff00);
	*code += buf[3];

	read(sock, buf, len);
	for(int i=0; i<len; i++)
	{
		printf("%d ", buf[i]);
	}
	printf("\n");
	buf[len] = 0;

	return len;
}
