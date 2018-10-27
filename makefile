all: server client
runs:server
	./server --server-broadcast-port 5200 --client-broadcast-port 5300
runc:client
	./client --server-broadcast-port 5200 --client-broadcast-port 5300
server:server.o util.o network.o message.o user.o
	gcc -o server server.o util.o network.o message.o user.o
client:client.o util.o network.o message.o game.o gameprint.o
	gcc -o client client.o util.o network.o message.o game.o gameprint.o
server.o:server.c util.h network.h message.h user.h
	gcc -c server.c
client.o:client.c util.h network.h message.h game.h gameprint.o
	gcc -c client.c
util.o:util.c util.h
	gcc -c util.c
network.o:network.c network.h util.h
	gcc -c network.c
message.o:message.c message.h util.h
	gcc -c message.c
game.o:game.c game.h util.h
	gcc -c game.c
user.o:user.c user.h util.h network.h
	gcc -c user.c
gameprint.o:gameprint.c gameprint.h util.h
	gcc -c gameprint.c
gameprint.h:game.h
clean:
	rm -rf *.out *.o server client
