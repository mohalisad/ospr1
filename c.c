#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//#include "util.h"

#define MPORT 5200

int main(){
    int sockfd;
    struct sockaddr_in addrport;
    if ((sockfd = socket(PF_INET,SOCK_STREAM,0)) == -1){
        printstr(STDOUT,"socket failed\n");
        return 0;
    }
    printint(STDOUT,sockfd);
    println(STDOUT);
    if(close (sockfd) == -1)
        printstr(STDOUT,"close failed\n");
}
