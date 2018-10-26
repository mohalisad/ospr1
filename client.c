#include <time.h>
#include "network.h"
#include "message.h"
#include "util.h"

void parse_message(string strmsg);

int main(int argc, char *argv[]){
    int *ports,maxfd,last_heartbeat,t,sr,portm;
    string ip,heartbeatmsg,receivedmsg,gamemap,username;
    fd_set rfds;
    UDPInfo *broadcast, *listener, *hblistener, client;
    struct timeval tv;
    ports = parse_input(argc,argv);
    printstr(STDOUT,"Please input your ip:\n");
    ip = readstr(STDIN,20);
    printstr(STDOUT,"Please input your port:\n");
    portm = readint(STDIN);
    printstr(STDOUT,"Please input your username:\n");
    username = readstr(STDIN,20);
    printstr(STDOUT,"Please input your gamemap:\n");
    gamemap = readstr(STDIN,20);
    //init client
    init_fds(&rfds,&maxfd,&tv);
    listener = init_listen_UDP(portm);
    FD_SET(listener->sock, &rfds);
    maxfd = MAX(maxfd,listener->sock);
    hblistener = init_listen_UDP(ports[0]);
    FD_SET(hblistener->sock, &rfds);
    maxfd = MAX(maxfd,hblistener->sock);
    while ((sr = select(maxfd + 1,&rfds,NULL,NULL,&tv))!=-1){
        if(sr != 0){
            if(FD_ISSET(STDIN, &rfds)){

            }
            if(FD_ISSET(listener->sock, &rfds)){
                receivedmsg = receive_UDP(listener,&client,100);
                parse_message(receivedmsg);
            }
            if(FD_ISSET(hblistener->sock, &rfds)){
                receivedmsg = receive_UDP(hblistener,&client,100);
                last_heartbeat = time(NULL);
                printstr(STDOUT,"Hearbeat\s");
            }
        }
        t = time(NULL);
        if(t - last_heartbeat>5){//no server

        }
        init_fds(&rfds,&maxfd,&tv);
    }
}

void parse_message(string strmsg){
    Message *temp;
    temp = str2msg(strmsg);
    switch (temp->type) {
        case LOGIN:

            break;
    }
}
