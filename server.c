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
            printstr(STDOUT,"HB\n");
            send_UDP(broadcast,broadcast,heartbeatmsg);
            t = t2;
        }
        init_fds(&rfds,&maxfd,&tv,arr,pointer);
    }
}

void parse_message(string strmsg,User *start){
    Message *temp;
    User *found,*found2;
    temp = str2msg(strmsg);
    printstr(STDOUT,strmsg);
    println(STDOUT);
    switch (temp->type) {
        case LOGIN:
            add_to_end(start,make_user(temp->ip,temp->port,temp->username));
            break;
        case MAKEGAME:
            found = get_user_by_name(start,temp->username);
            if(found){
                found2 = find_pending(start,temp->username);
                if(found2){
                    make_game(start,found,found2);
                }else {
                    found2 = find_ready_to_play(start);
                    if(found2){
                        make_game(start,found,found2);
                    }else found->ready_to_play = TRUE;
                }
            }
            break;
        case MAKEGAMEW:
            found  = get_user_by_name(start,temp->username);
            found2 = get_user_by_name(start,temp->opponent);
            if(found){
                if(found2?(found2->ready_to_play):FALSE){
                    make_game(start,found,found2);
                }else{
                    found->ready_to_play = TRUE;
                    found->pending = TRUE;
                    found->pend_who = temp->opponent;
                }
            }
            break;
    }
}
