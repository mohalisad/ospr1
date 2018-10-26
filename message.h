#ifndef MESSAGE_H
#define MESSAGE_H

#define HEARTBEAT 1

typedef int MessageType;
typedef struct Message Message;

struct Message{
    MessageType type;
    char* ip;
    int port;
};

char    *msg2str(Message *input);
Message *str2msg(char *input);

Message *heartbeat_message(char *ip,int port);
#endif
