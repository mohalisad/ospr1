#include "message.h"
#include "util.h"

char *msg2str(Message *input){
    string ret;
    ret = int2str(input->type);
    switch (input->type) {
        case HEARTBEAT:
            ret = stradd(ret," ");
            ret = stradd(ret,ret->ip);
            ret = stradd(ret," ");
            ret = stradd(ret,int2str(ret->port));
            return ret;
    }
}

Message *str2msg(char *input){
    Message *ret;
    ret->type = str2int(get_token(input,' ',0));
    switch (ret->type) {
        case HEARTBEAT:
            ret->ip = get_token(input,' ',1);
            ret->port = str2int(get_token(input,' ',2));;
            return ret;
    }
}

Message *heartbeat_message(char *ip,int port){
    Message *ret;
    ret->type = HEARTBEAT;
    ret->ip = new_string(ip);
    ret->port = port;
}
