//
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <time.h>
// #include "util.h"
//
// #define MPORT 5200
// #define NPORT 5300
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
//         addrto.sin_family = AF_INET;
//         addrto.sin_port = htons(NPORT);
//         inet_pton(AF_INET, "255.255.255.255", &(addrto.sin_addr));
//         addrsize = sizeof(addrto);
//         t = time(NULL);
//         while (TRUE) {
//             sendto(sockfd,"Hello",6,0,(struct sockaddr *) &addrto, addrsize);
//         }
//     }
//     if(close (sockfd) == -1)
//         printstr(STDOUT,"close failed\n");
// }
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>


void error(char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
   int sock, length, fromlen, n;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[1024];
   if (argc < 2) {
      fprintf(stderr, "ERROR, no port provided\n");
      exit(0);
   }
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(atoi(argv[1]));
   if (bind(sock,(struct sockaddr *)&server,length)<0)
       error("binding");
   fromlen = sizeof(struct sockaddr_in);
   while (1) {
       n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
       if (n < 0) error("recvfrom");
       write(1,"Received a datagram: ",21);
       write(1,buf,n);
       n = sendto(sock,"Got your message\n",17,
                  0,(struct sockaddr *)&from,fromlen);
       if (n  < 0) error("sendto");
   }
 }
