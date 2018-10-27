#include <stdlib.h>
#include <unistd.h>
#include "message.h"
#include "network.h"
#include "util.h"
#include "user.h"

User* make_empty_user(){
    User* ret;
    ret = malloc(sizeof(User));
    ret->next = NULL;
    ret->ready_to_play = 0;
    ret->pending = 0;
    return ret;
}

User* make_user(char* ip,int port,char* username){
    User* ret;
    ret = make_empty_user();
    ret->ip = ip;
    ret->username = username;
    ret->port = port;
    return ret;
}

void add_to_end(User* start,User* new){
    while(start->next != NULL)
        start = start->next;
    start->next = new;
}

User* get_user_by_name(User* start,char* name){
    start = start->next;
    while(start != NULL){
        if(str_comp(name,start->username)){
            return start;
        }
        start = start->next;
    }
    return NULL;
}

void remove_user_by_name(User* start,char* name){
    while(start->next != NULL){
        if(str_comp(name,start->next->username)){
            start->next = start->next->next;
            break;
        }
        start = start->next;
    }
}

User* find_ready_to_play(User* start){
    start = start->next;
    while(start != NULL){
        if(start->ready_to_play && !(start->pending)){
            return start;
        }
        start = start->next;
    }
    return NULL;
}

User* find_pending(User* start,char* name){
    start = start->next;
    while(start != NULL){
        if(start->pending){
            if(str_comp(start->pend_who,name))
                return start;
        }
        start = start->next;
    }
    return NULL;
}

void make_game(User* first,User* p1,User* p2){
    UDPInfo *myself,*p1client;
    remove_user_by_name(first,p1->username);
    remove_user_by_name(first,p2->username);
    myself = init_send_UDP(p1->port);
    p1client = init_receiverip_UDP(p1->ip,p1->port);
    send_UDP(myself,p1client,msg2str(make_begin_message(p2->ip,p2->port)));
    close(myself->sock);
}
