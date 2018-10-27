#include <stdlib.h>
#include "message.h"
#include "util.h"

char *msg2str(Message *input){
    string ret;
    ret = int2str(input->type);
    ret = stradd(ret," ");
    switch (input->type) {
        case CHEARTBEAT:
        case INTRO:
        case BEGINGAME:
        case HEARTBEAT:
            ret = stradd(ret,input->ip);
            ret = stradd(ret," ");
            ret = stradd(ret,int2str(input->port));
            return ret;
        case LOGIN:
            ret = stradd(ret,input->ip);
            ret = stradd(ret," ");
            ret = stradd(ret,int2str(input->port));
            ret = stradd(ret," ");
            ret = stradd(ret,input->username);
            return ret;
        case MAKEGAME:
            ret = stradd(ret,input->username);
            return ret;
        case MAKEGAMEW:
            ret = stradd(ret,input->username);
            ret = stradd(ret," ");
            ret = stradd(ret,input->opponent);
            return ret;
        case ATTACK:
            ret = stradd(ret,int2str(input->x));
            ret = stradd(ret," ");
            ret = stradd(ret,int2str(input->y));
            return ret;
        case HITRESULT:
            ret = stradd(ret,int2str(input->x));
            ret = stradd(ret," ");
            ret = stradd(ret,int2str(input->y));
            ret = stradd(ret," ");
            ret = stradd(ret,int2str(input->hit));
            return ret;
    }
    return NULL;
}

Message *str2msg(char *input){
    Message *ret = malloc(sizeof(Message));
    ret->type    = str2int(get_token(input,' ',0));
    switch (ret->type) {
        case CHEARTBEAT:
        case INTRO:
        case BEGINGAME:
        case HEARTBEAT:
            ret->ip   = get_token(input,' ',1);
            ret->port = str2int(get_token(input,' ',2));
            return ret;
        case LOGIN:
            ret->ip       = get_token(input,' ',1);
            ret->port     = str2int(get_token(input,' ',2));
            ret->username = get_token(input,' ',3);
            return ret;
        case MAKEGAME:
            ret->username = get_token(input,' ',1);
            return ret;
        case MAKEGAMEW:
            ret->username = get_token(input,' ',1);
            ret->opponent = get_token(input,' ',2);
            return ret;
        case ATTACK:
            ret->x = str2int(get_token(input,' ',1));
            ret->y = str2int(get_token(input,' ',2));
            return ret;
        case HITRESULT:
            ret->x = str2int(get_token(input,' ',1));
            ret->y = str2int(get_token(input,' ',2));
            ret->hit = str2int(get_token(input,' ',3));
            return ret;
    }
    return NULL;
}

Message *make_heartbeat_message(char *ip,int port){
    Message *ret = malloc(sizeof(Message));
    ret->type    = HEARTBEAT;
    ret->ip      = new_string(ip);
    ret->port    = port;
    return ret;
}
Message *make_cheartbeat_message(char *ip,int port){
    Message *ret = malloc(sizeof(Message));
    ret->type    = CHEARTBEAT;
    ret->ip      = new_string(ip);
    ret->port    = port;
    return ret;
}
Message *make_login_message(char *ip,int port,char* username){
    Message *ret  = malloc(sizeof(Message));
    ret->type     = LOGIN;
    ret->ip       = new_string(ip);
    ret->port     = port;
    ret->username = new_string(username);
    return ret;
}

Message *make_game_message(char* username){
    Message *ret  = malloc(sizeof(Message));
    ret->type     = MAKEGAME;
    ret->username = new_string(username);
    return ret;
}

Message *make_game_message_with(char* username,char* opponent){
    Message *ret  = malloc(sizeof(Message));
    ret->type     = MAKEGAMEW;
    ret->username = new_string(username);
    ret->opponent = new_string(opponent);
    return ret;
}

Message *make_begin_message(char* ip,int port){
    Message *ret = malloc(sizeof(Message));
    ret->type = BEGINGAME;
    ret->ip   = new_string(ip);
    ret->port = port;
    return ret;
}

Message *make_intro_message(char* ip,int port){
    Message *ret = malloc(sizeof(Message));
    ret->type = INTRO;
    ret->ip   = new_string(ip);
    ret->port = port;
    return ret;
}

Message *make_attack_message(int x,int y){
    Message *ret = malloc(sizeof(Message));
    ret->type = ATTACK;
    ret->x = x;
    ret->y = y;
    return ret;
}

Message *make_hit_message(int x,int y,int hit){
    Message *ret = malloc(sizeof(Message));
    ret->type = HITRESULT;
    ret->x = x;
    ret->y = y;
    ret->hit = hit;
    return ret;
}
