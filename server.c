#include <time.h>
#include "network.h"
#include "message.h"
#include "user.h"
#include "util.h"

#define PORTN 5412

void parse_message(string strmsg,User *users);

int main(int argc, char *argv[]){
    int *ports,maxfd,t,t2,sr,pointer;
    string ip,heartbeatmsg,receivedmsg;
    fd_set rfds;
    UDPInfo *broadcast, *listener, client;
    UDPInfo *arr[10];
    User *start_user;//dummy
    struct timeval tv;
    ports = parse_input(argc,argv);
    start_user = make_empty_user();
    start_user->next = make_empty_user();
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
            if(FD_ISSET(listener->sock, &rfds)){
                receivedmsg = receive_UDP(listener,&client,100);
                parse_message(receivedmsg,start_user);
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

void parse_message(string strmsg,User *start){
    Message *temp;
    User *found;
    temp = str2msg(strmsg);
    printstr(STDOUT,strmsg);
    println(STDOUT);
    switch (temp->type) {
        case LOGIN:
            add_to_end(start,make_user(temp->ip,temp->port,temp->username));
            break;
        case MAKEGAME:
            printstr(STDOUT,"MG\n");
            found = get_user_by_name(start,temp->username);
            found->ready_to_play = TRUE;
        case MAKEGAMEW:
            printstr(STDOUT,"MGW\n");
            found = get_user_by_name(start,temp->username);
            found->ready_to_play = TRUE;
            found->pending = TRUE;
            found->pend_who = temp->opponent;
            break;
    }
}
