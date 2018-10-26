#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>

typedef struct UDPInfo UDPInfo;

struct UDPInfo{
    int sock;
    int sockaddr_size;
    struct sockaddr_in sockaddr;
};

UDPInfo *init_UDP(int port);
int send_UDP(UDPInfo* server,UDPInfo* client,char* message);
char* receive_UDP(UDPInfo* server,UDPInfo* client,int size);
#endif
