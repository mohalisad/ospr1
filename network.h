#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>
#include <sys/time.h>

typedef struct UDPInfo UDPInfo;

struct UDPInfo{
    int sock;
    socklen_t sockaddr_size;
    struct sockaddr_in sockaddr;
};

void     init_fds(fd_set* rfds,int *maxfd,struct timeval *tv,UDPInfo** arr,int length);
UDPInfo* init_listen_UDP(int port);
UDPInfo* init_send_UDP(int port);
UDPInfo* init_receiverip_UDP(char* ip,int port);
UDPInfo* init_broadcast_udp(int port);
char*    receive_UDP(UDPInfo* server,UDPInfo* client,int size);
int      send_UDP(UDPInfo* server,UDPInfo* client,char* message);

#endif
