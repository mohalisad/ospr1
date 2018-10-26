// #include <sys/types.h>
// #include <sys/socket.h>
// #include <time.h>
// #include "util.h"
//
#define MPORT 5200
// #define NPORT 5300
//
// char tt[1000];
//
// int main(){
//     //int s;
//     int count;
//     int sockfd;
//     int addrsize;
//     int t;
//     struct sockaddr_in addrport,addrto;
//     if ((sockfd = socket(PF_INET,SOCK_DGRAM,0)) == -1){
//         printstr(STDOUT,"socket failed\n");
//         return 0;
//     }
//     printint(STDOUT,sockfd);
//     println(STDOUT);
//     addrport.sin_family = AF_INET;
//     addrport.sin_port = htons(MPORT);
//     addrport.sin_addr.s_addr = htonl(INADDR_ANY);
//     if(bind(sockfd, (struct sockaddr *) &addrport, sizeof(addrport)) == -1){
//         printstr(STDOUT,"bind failed\n");
//     }else{
//         /*
//         if(listen(sockid, queueLimit) == -1)
//             printstr(STDOUT,"listen failed\n");
//         clientaddrsize = sizeof(clientaddr);
//         s = accept(sockfd,&clientaddr,&clientaddrsize);
//         */
//         while (true) {
//             recvfrom(sockfd,tt,1000,0,(struct sockaddr *) &addrto, sizeof(addrto));
//             printstr(STDOUT,tt);
//         }
//
//     }
//     if(close (sockfd) == -1)
//         printstr(STDOUT,"close failed\n");
// }
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
