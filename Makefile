server : CustomObject.o CustomUser.o ChattingDB.o ManageMap.o dumper.o echo_epollserv.o
	gcc -o server CustomObject.o CustomUser.o ChattingDB.o ManageMap.o dumper.o echo_epollserv.o libtmx.a `xml2-config --libs` -lz -lpthread -lmysqlclient -o server

CustomObject.o : CustomObject.c
	gcc -c -o CustomObject.o CustomObject.c

CustomUser.o : CustomUser.c
	gcc -c -o CustomUser.o CustomUser.c

ChattingDB.o : ChattingDB.c
	gcc -c -o ChattingDB.o ChattingDB.c

ManageMap.o : ManageMap.c
	gcc -c -o ManageMap.o ManageMap.c

dumper.o : dumper.c
	gcc -c -o dumper.o dumper.c

echo_epollserv.o : echo_epollserv.c
	gcc -c -o echo_epollserv.o echo_epollserv.c

clean :
	rm *.o server
