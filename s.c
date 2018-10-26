#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "util.h"

#define MPORT 5200
#define NPORT 5300

int main(){
    //int s;
    int count;
    int sockfd;
    int addrsize;
    struct sockaddr_in addrport,addrto;
    if ((sockfd = socket(PF_INET,SOCK_STREAM,0)) == -1){
        printstr(STDOUT,"socket failed\n");
        return 0;
    }
    printint(STDOUT,sockfd);
    println(STDOUT);
    addrport.sin_family = AF_INET;
    addrport.sin_port = htons(MPORT);
    addrport.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sockfd, (struct sockaddr *) &addrport, sizeof(addrport)) == -1){
        printstr(STDOUT,"bind failed\n");
    }else{
        /*
        if(listen(sockid, queueLimit) == -1)
            printstr(STDOUT,"listen failed\n");
        clientaddrsize = sizeof(clientaddr);
        s = accept(sockfd,&clientaddr,&clientaddrsize);
        */
        addrto.sin_family = AF_INET;
        addrto.sin_port = htons(MPORT);
        inet_pton(AF_INET, "255.255.255.255", &(addrto.sin_addr));
        sendto(sockfd,"Hello",6,0,(struct sockaddr *) &addrto, sizeof(addrto));
    }
    if(close (sockfd) == -1)
        printstr(STDOUT,"close failed\n");
}
