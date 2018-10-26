all: server client
server:s.o util.o network.o
	gcc -o server s.o util.o network.o
s.o:s.c util.h network.h
	gcc -c s.c
client:c.o util.o
	gcc -o client c.o util.o
c.o:c.c util.h
	gcc -c c.c
util.o:util.c util.h
	gcc -c util.c
network.o:network.c network.h util.h
	gcc -c network.c
clean:
	rm -rf *.out *.o server client
