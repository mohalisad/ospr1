#include <stdlib.h>
#include "message.h"
#include "util.h"

char *msg2str(Message *input){
    string ret;
    ret = int2str(input->type);
    switch (input->type) {
        case HEARTBEAT:
            ret = stradd(ret," ");
            ret = stradd(ret,input->ip);
            ret = stradd(ret," ");
            ret = stradd(ret,int2str(input->port));
            return ret;
        case LOGIN:
            ret = stradd(ret," ");
            ret = stradd(ret,input->ip);
            ret = stradd(ret," ");
            ret = stradd(ret,int2str(input->port));
            ret = stradd(ret," ");
            ret = stradd(ret,input->username);
            return ret;
    }
    return 0;
}

Message *str2msg(char *input){
    Message *ret = malloc(sizeof(Message));
    ret->type = str2int(get_token(input,' ',0));
    switch (ret->type) {
        case HEARTBEAT:
            ret->ip = get_token(input,' ',1);
            ret->port = str2int(get_token(input,' ',2));;
            return ret;
        case LOGIN:
            ret->ip = get_token(input,' ',1);
            ret->port = str2int(get_token(input,' ',2));;
            ret->username = get_token(input,' ',3);;
            return ret;
    }
    return 0;
}

Message *make_heartbeat_message(char *ip,int port){
    Message *ret = malloc(sizeof(Message));
    ret->type = HEARTBEAT;
    ret->ip = new_string(ip);
    ret->port = port;
    return ret;
}

Message *make_login_message(char *ip,int port,char* username){
    Message *ret = malloc(sizeof(Message));
    ret->type = LOGIN;
    ret->ip = new_string(ip);
    ret->port = port;
    ret->username = new_string(username);
    return ret;
}
