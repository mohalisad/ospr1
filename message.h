#ifndef MESSAGE_H
#define MESSAGE_H

#define HEARTBEAT 0
#define LOGIN     1
#define MAKEGAME  2
#define MAKEGAMEW 3
#define BEGINGAME 4

typedef int MessageType;
typedef struct Message Message;

struct Message{
    MessageType type;
    char* ip;
    char* username;
    char* opponent;
    int   port;
};

char    *msg2str(Message *input);
Message *str2msg(char *input);

Message *make_heartbeat_message(char *ip,int port);
Message *make_login_message(char *ip,int port,char* username);
Message *make_game_message(char* username);
Message *make_game_message_with(char* username,char* opponent);
Message *make_begin_message(char* ip,int port);
#endif
