#include "network.h"
#include "util.h"
#include <time.h>

#define MPORT 5200

int main(int argc, char *argv[]){
    string buf;
    string line;
    UDPInfo* server;
    UDPInfo* client;
    //server = init_send_UDP(MPORT);
    client = init_broadcast_udp(MPORT);
    int t = time(NULL);
    int t2;
    while (TRUE){
        t2 = time(NULL);
        if(t2 - t >1){
            send_UDP(client,client,"Hello World\n");
            t = t2;
        }
        //buf = receive_UDP(server,&client,1024);
        //printstr(STDOUT,buf);
        //println(STDOUT);
        //line = stradd("Got it:",buf);

    }
 }
