all: server client
runs:server
	./server --server-broadcast-port 1600 --client-broadcast-port 1700
server:server.o util.o network.o message.o
	gcc -o server server.o util.o network.o message.o
server.o:server.c util.h network.h message.h
	gcc -c server.c
client:c.o util.o network.o
	gcc -o client c.o util.o network.o
c.o:c.c util.h
	gcc -c c.c
util.o:util.c util.h
	gcc -c util.c
network.o:network.c network.h util.h
	gcc -c network.c
message.o:message.c message.h util.h
	gcc -c message.c
clean:
	rm -rf *.out *.o server client
