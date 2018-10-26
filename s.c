#include "network.h"
#include "util.h"

#define MPORT 5200

int main(int argc, char *argv[]){
   string buf;
   string line;
   UDPInfo* server;
   UDPInfo* client;
   server = init_listen_UDP(MPORT);
   client = init_broadcast_udp(MPORT);
   while (TRUE){
       send_UDP(server,client,"Hello World\n");
       //buf = receive_UDP(server,&client,1024);
       //printstr(STDOUT,buf);
       //println(STDOUT);
       //line = stradd("Got it:",buf);

   }
 }
