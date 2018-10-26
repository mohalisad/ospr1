#ifndef MESSAGE_H
#define MESSAGE_H

#define HEARTBEAT 0
#define LOGIN     1

typedef int MessageType;
typedef struct Message Message;

struct Message{
    MessageType type;
    char* ip;
    char* username;
    int port;
};

char    *msg2str(Message *input);
Message *str2msg(char *input);

Message *make_heartbeat_message(char *ip,int port);
Message *make_login_message(char *ip,int port,char* username);
#endif
