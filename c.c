
#define MPORT 5200

#include "network.h"
#include "util.h"

int main(int argc, char *argv[]){
   UDPInfo *myself,*to;
   string line;
   myself = init_send_UDP(MPORT);
   to = init_receiverinfo_UDP("192.168.1.10",MPORT);
   line = readstr(STDOUT,256);
   send_UDP(myself,to,line);
   printstr(STDOUT,"Response:");
   line = receive_UDP(myself,to,1024);
   printstr(STDOUT,line);
   println(STDOUT);
}
