#include <time.h>
#include "network.h"
#include "message.h"
#include "util.h"

void parse_message(string strmsg,string ip,int port,string username);

int main(int argc, char *argv[]){
    int *ports,maxfd,last_heartbeat,t,sr,portm,pointer;
    string ip,heartbeatmsg,receivedmsg,gamemap,username;
    fd_set rfds;
    UDPInfo *broadcast, *listener, *hblistener, client;
    UDPInfo *arr[10];
    struct timeval tv;
    bool server_alive;
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
    pointer = 0;
    listener = init_listen_UDP(portm);
    arr[pointer++] = listener;
    hblistener = init_listen_UDP(ports[0]);
    arr[pointer++] = hblistener;
    init_fds(&rfds,&maxfd,&tv,arr,pointer);
    last_heartbeat = time(NULL);
    server_alive = FALSE;
    while ((sr = select(maxfd + 1,&rfds,NULL,NULL,&tv))!=-1){
        if(sr != 0){
            if(FD_ISSET(STDIN, &rfds)){

            }
            if(FD_ISSET(listener->sock, &rfds)){
                receivedmsg = receive_UDP(listener,&client,100);
                parse_message(receivedmsg,ip,portm,username);
            }
            if(FD_ISSET(hblistener->sock, &rfds)){
                receivedmsg = receive_UDP(hblistener,&client,100);
                last_heartbeat = time(NULL);
                if(!server_alive){
                    parse_message(receivedmsg,ip,portm,username);
                }
                server_alive = TRUE;
            }
        }
        t = time(NULL);
        if(t - last_heartbeat>5){//no server
            if(!server_alive){

            }
        }
        init_fds(&rfds,&maxfd,&tv,arr,pointer);
    }
}

void parse_message(string strmsg,string ip,int port,string username){
    Message *temp;
    UDPInfo *server,*myself;
    temp = str2msg(strmsg);
    switch (temp->type) {
        case HEARTBEAT:
            myself = init_send_UDP(temp->port);
            server = init_receiverip_UDP(temp->ip,temp->port);
            send_UDP(myself,server,msg2str(make_login_message(ip,port,username)));
            break;
        case LOGIN:

            break;
    }
}
