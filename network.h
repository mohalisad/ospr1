#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>

typedef struct UDPInfo UDPInfo;

struct UDPInfo{
    int sock;
    int sockaddr_size;
    struct sockaddr_in sockaddr;
};

UDPInfo *init_listen_UDP(int port);
UDPInfo *init_send_UDP(int port);
UDPInfo *init_receiverip_UDP(char* ip,int port);
char* receive_UDP(UDPInfo* server,UDPInfo* client,int size);
int send_UDP(UDPInfo* server,UDPInfo* client,char* message);

#endif
