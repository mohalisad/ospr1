all: server client
runs:server
	./server --server-broadcast-port 5200 --client-broadcast-port 5300
runc:client
	./client --server-broadcast-port 5200 --client-broadcast-port 5300
server:server.o util.o network.o message.o user.o
	gcc -o server server.o util.o network.o message.o user.o
server.o:server.c util.h network.h message.h user.h
	gcc -c server.c
client:client.o util.o network.o message.o
	gcc -o client client.o util.o network.o message.o
client.o:client.c util.h network.h message.h
	gcc -c client.c
util.o:util.c util.h
	gcc -c util.c
network.o:network.c network.h util.h
	gcc -c network.c
message.o:message.c message.h util.h
	gcc -c message.c
user.o:user.c user.h util.h
	gcc -c user.c
clean:
	rm -rf *.out *.o server client
