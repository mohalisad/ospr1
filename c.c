#include "network.h"
#include "util.h"

#define MPORT 1600

int main(int argc, char *argv[]){
    // UDPInfo *myself,*to;
    // string line;
    // myself = init_send_UDP(MPORT);
    // to = init_receiverip_UDP("192.168.1.10",MPORT);
    // line = readstr(STDOUT,256);
    // send_UDP(myself,to,line);
    // printstr(STDOUT,"Response:");
    // line = receive_UDP(myself,to,1024);
    // printstr(STDOUT,line);
    // println(STDOUT);
    string buf;
    string line;
    UDPInfo* server;
    UDPInfo client;
    server = init_listen_UDP(MPORT);
    while (TRUE){
        buf = receive_UDP(server,&client,1024);
        printstr(STDOUT,buf);
        line = stradd("Got it:",buf);
        send_UDP(server,&client,line);
    }
}
