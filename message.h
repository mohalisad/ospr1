#ifndef MESSAGE_H
#define MESSAGE_H

#define HEARTBEAT = 1

typedef int MessageType;
typedef struct Message Message;

struct Message{
    MessageType type;
};

#endif
