#include <time.h>
#include "network.h"
#include "message.h"
#include "util.h"

#define PORTN 5412

int main(int argc, char *argv[]){
    //define vars
    int *ports;
    int maxfd;
    int t,t2;
    int selectret;
    string ip,heartbeatmsg;
    struct timeval tv;
    fd_set rfds;
    UDPInfo *broadcast;
    //get ip for heartbeat message
    printstr(STDOUT,"Please input your ip:\n");
    ip = readstr(STDIN,20);
    ports = parse_input(argc,argv);
    heartbeatmsg = msg2str(heartbeat_message(ip,PORTN));
    //init server
    broadcast = init_broadcast_udp(ports[0]);
    init_fds(&rfds,&maxfd,&tv);
    maxfd = MAX(maxfd,broadcast->sock);
    t = time(NULL);
    while ((selectret = select(maxfd + 1,&rfds,NULL,NULL,&tv))!=-1){
        if(selectret != 0){
            if(FD_ISSET(STDIN, &rfds)){
                readstr(STDIN,50);
                printstr(STDOUT,"stdin\n");
            }
        }else printstr(STDOUT,"Loop\n");
        t2 = time(NULL);
        if(t2 - t >1){
            send_UDP(broadcast,broadcast,heartbeatmsg);
            t = t2;
        }
        init_fds(&rfds,&maxfd,&tv);
    }
}
