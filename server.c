#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "ChattingDB.h"

#define BUF_SIZE 1024

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

	int len = (int)((buf[0] << 24) & 0xff000000) + (int)((buf[1] << 16) & 0x00ff0000) + (int)((buf[2] << 8) & 0x0000ff00) + buf[3];

	readLen = read(sock, buf, 4);

	for(int i=0; i<4; i++)
	{
		printf("%d ", buf[i]);
	}

	if(readLen == -1)
		return -1;

	*code = (int)((buf[0] << 24) & 0xff000000) + (int)((buf[1] << 16) & 0x00ff0000) + (int)((buf[2] << 8) & 0x0000ff00) + buf[3];

	read(sock, buf, len);
	for(int i=0; i<len; i++)
	{
		printf("%d ", buf[i]);
	}
	printf("\n");
	buf[len] = 0;

	return len;
}

int main(int argc, char * argv[])
{
	int serv_sock, cInt_sock;
	char sendBuf[BUF_SIZE];
	char readBuf[BUF_SIZE];
	int str_len, i;
	int code;
	char name[50];
	char content[100];

	struct sockaddr_in serv_adr, cInt_adr;
	socklen_t cInt_adr_sz;

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

	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
		error_handling("bind() error");

	cInt_adr_sz = sizeof(cInt_adr);

	for(i=0; i<5; i++)
	{
		cInt_sock = accept(serv_sock, (struct sockaddr*)&cInt_adr, &cInt_adr_sz);

		if(cInt_sock == -1)
			error_handling("accept() error");
		else
			printf("Connected client %d \n", i + 1);

		while((str_len = readCommand(cInt_sock, &code, readBuf)) != 0)
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

			str_len = sendCommand(cInt_sock, code, readBuf);
			memset(readBuf, 0, BUF_SIZE);
		}

		printf("close sock : %d\n", cInt_sock);

		close(cInt_sock);
	}

	closeMySQL_chatting();
	close(cInt_sock);
	return 0;
}
