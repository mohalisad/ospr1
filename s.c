#include "util.h"
#include "network.h"

#define MPORT 5200

int main(int argc, char *argv[]){
   string buf;
   string line;
   UDPInfo* server;
   UDPInfo client;
   server = init_listen_UDP(MPORT);
   while (TRUE){
       buf = receive_UDP(server,&client,1024);
       printstr(STDOUT,buf);
       println(STDOUT);
       line = stradd("Got it:",buf);
       send_UDP(server,&client,line);
   }
 }
