
#define MPORT 5200

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "util.h"

int main(int argc, char *argv[]){
   int sock, length, n;
   struct sockaddr_in server, from; // IP Addressing(ip, port, type) Stuff
   char buffer[256];
   string line;
   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");
   server.sin_family = AF_INET;
   inet_pton(AF_INET, "192.168.1.10",(struct sockaddr *) &(server.sin_addr));
   server.sin_port = htons(MPORT);
   length = sizeof(struct sockaddr_in);
   line = readstr(STDOUT,256);
   n = sendto(sock,line,strlen_(line) + 1 ,0,(struct sockaddr *)&server,length);
   if (n < 0) error("Sendto");
   n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from,&length);
   if (n < 0) error("recvfrom");
   printstr(STDOUT,"Response:");
   printstr(STDOUT,buffer);
   println(STDOUT);
}
