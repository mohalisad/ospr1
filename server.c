#include <time.h>
#include "network.h"
#include "message.h"
#include "util.h"

#define PORTN 5412

void parse_message(string strmsg);

int main(int argc, char *argv[]){
    int *ports,maxfd,t,t2,sr,pointer;
    string ip,heartbeatmsg,receivedmsg;
    fd_set rfds;
    UDPInfo *broadcast, *listener, client;
    UDPInfo *arr[10];
    struct timeval tv;
    ports = parse_input(argc,argv);
    printstr(STDOUT,"Please input your ip:\n");
    ip = readstr(STDIN,20);
    heartbeatmsg = msg2str(make_heartbeat_message(ip,PORTN));
    //init server
    pointer = 0;
    broadcast = init_broadcast_udp(ports[0]);
    listener = init_listen_UDP(PORTN);
    arr[pointer++] = listener;
    init_fds(&rfds,&maxfd,&tv,arr,pointer);
    t = time(NULL);
    while ((sr = select(maxfd + 1,&rfds,NULL,NULL,&tv))!=-1){
        if(sr != 0){
            if(FD_ISSET(STDIN, &rfds));//nothing
            if(FD_ISSET(listener->sock, &rfds)){
                receivedmsg = receive_UDP(listener,&client,100);
                parse_message(receivedmsg);
            }
        }
        t2 = time(NULL);
        if(t2 - t >1){
            send_UDP(broadcast,broadcast,heartbeatmsg);
            t = t2;
        }
        init_fds(&rfds,&maxfd,&tv,arr,pointer);
    }
}

void parse_message(string strmsg){
    Message *temp;
    temp = str2msg(strmsg);
    switch (temp->type) {
        case LOGIN:
            printstr(STDOUT,strmsg);
            println(STDOUT);
            break;
    }
}
