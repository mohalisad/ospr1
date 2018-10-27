#include <stdlib.h>
#include "util.h"
#include "user.h"

User* make_empty_user(){
    User* ret;
    ret = malloc(sizeof(User));
    ret->next = NULL;
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
        }
        start = start->next;
    }
}
