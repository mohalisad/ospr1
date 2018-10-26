#include "network.h"
#include "message.h"
#include "util.h"

#define PORTN 5412
int main(int argc, char *argv[]){
    int *ports;
    string ip;
    printstr("Please input your ip");
    ip = readstr(STDIN,20);
    ports = parse_input(argc,argv);
    //server
}
