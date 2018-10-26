#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "network.h"
#include "util.h"

UDPInfo *init_listen_UDP(int port){
    UDPInfo* ret = malloc(sizeof(UDPInfo));
    ret->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (ret->sock < 0) error("Opening socket");
    ret->sockaddr.sin_family = AF_INET;
    ret->sockaddr.sin_addr.s_addr = INADDR_ANY;
    ret->sockaddr.sin_port = htons(port);
    ret->sockaddr_size = sizeof(ret->sockaddr);
    if (bind(ret->sock,(struct sockaddr *)&(ret->sockaddr),ret->sockaddr_size)<0)
        error("binding");
    return ret;
}

UDPInfo *init_send_UDP(int port){
    UDPInfo* ret = malloc(sizeof(UDPInfo));
    ret->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (ret->sock < 0) error("socket");
    return ret;
}

UDPInfo *init_receiverip_UDP(char* ip,int port){
    UDPInfo* ret = malloc(sizeof(UDPInfo));
    ret->sockaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip,(struct sockaddr *) &(ret->sockaddr.sin_addr));
    ret->sockaddr.sin_port = htons(port);
    ret->sockaddr_size = sizeof(ret->sockaddr);
    return ret;
}

UDPInfo *init_broadcast_udp(int port){
    int be = 1;
    UDPInfo* ret = malloc(sizeof(UDPInfo));
    ret->sock = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(ret->sock, SOL_SOCKET, SO_BROADCAST, &be, sizeof(be));
    if (ret->sock < 0) error("Opening socket");
    ret->sockaddr.sin_family = AF_INET;
    ret->sockaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    ret->sockaddr.sin_port = htons(port);
    ret->sockaddr_size = sizeof(ret->sockaddr);
    if (bind(ret->sock,(struct sockaddr *)&(ret->sockaddr),ret->sockaddr_size)<0)
        error("binding");
    return ret;
}

char* receive_UDP(UDPInfo* server,UDPInfo* client,int size){
    int n;
    string ret = new_empty_string(size);
    n = recvfrom(server->sock,ret,size,0,(struct sockaddr *)&(client->sockaddr),&(client->sockaddr_size));
    if (n < 0) error("recvfrom");
    return ret;
}

int send_UDP(UDPInfo* server,UDPInfo* client,char* message){
    int ret = sendto(server->sock,message,strlen_(message) + 1,0,(struct sockaddr *)&(client->sockaddr),client->sockaddr_size);
    if (ret  < 0) error("sendto");
    return ret;
}
