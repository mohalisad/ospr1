#include <unistd.h>
#include <time.h>
#include "network.h"
#include "message.h"
#include "util.h"

void parse_stdin(UDPInfo* server,UDPInfo* myself,string username);
void parse_message(UDPInfo** server,UDPInfo** myself,string strmsg,string ip,int port,string username);

int main(int argc, char *argv[]){
    int *ports,maxfd,last_heartbeat,t,sr,portm,pointer;
    string ip,heartbeatmsg,receivedmsg,gamemap,username;
    fd_set rfds;
    UDPInfo *server,*myself,*listener, *hblistener, client;
    UDPInfo *arr[10];
    struct timeval tv;
    bool server_alive;
    ports = parse_input(argc,argv);
    printstr(STDOUT,"Please input your ip:\n");
    ip = readstr(STDIN,20);
    printstr(STDOUT,"Please input your port:\n");
    portm = readint(STDIN);
    printstr(STDOUT,"Please input your username:\n");
    username = readstr(STDIN,20);
    printstr(STDOUT,"Please input your gamemap:\n");
    gamemap = readstr(STDIN,20);
    //init client
    pointer = 0;
    listener = init_listen_UDP(portm);
    arr[pointer++] = listener;
    hblistener = init_listen_UDP(ports[0]);
    arr[pointer++] = hblistener;
    init_fds(&rfds,&maxfd,&tv,arr,pointer);
    last_heartbeat = time(NULL);
    server_alive = FALSE;
    while ((sr = select(maxfd + 1,&rfds,NULL,NULL,&tv))!=-1){
        if(sr != 0){
            if(FD_ISSET(STDIN, &rfds)){
                if(server_alive)
                    parse_stdin(server,myself,username);
            }
            if(FD_ISSET(listener->sock, &rfds)){
                receivedmsg = receive_UDP(listener,&client,100);
                parse_message(&server,&myself,receivedmsg,ip,portm,username);
            }
            if(FD_ISSET(hblistener->sock, &rfds)){
                receivedmsg = receive_UDP(hblistener,&client,100);
                last_heartbeat = time(NULL);
                if(!server_alive){
                    parse_message(&server,&myself,receivedmsg,ip,portm,username);
                    pointer--;//remove hb listener
                    close(arr[pointer]->sock);
                }
                server_alive = TRUE;
            }
        }
        t = time(NULL);
        if(t - last_heartbeat>5){//no server
            if(!server_alive){//fully client mode

            }
        }
        init_fds(&rfds,&maxfd,&tv,arr,pointer);
    }
}

void parse_stdin(UDPInfo* server,UDPInfo* myself,string username){
    string line,part1;
    line = readstr(STDIN,50);
    part1 = get_token(line,' ',0);
    if(str_comp(part1,"make_game")){
        if(number_of_tokens(line,' ') < 3){
            if(number_of_tokens(line,' ') == 1){
                send_UDP(myself,server,msg2str(make_game_message(username)));
            }else{
                send_UDP(myself,server,msg2str(make_game_message_with(username,get_token(line,' ',1))));
            }
        }else printstr(STDERR,"input is invalid\n");
    }else printstr(STDERR,"input is invalid\n");
}

void parse_message(UDPInfo** server,UDPInfo** myself,string strmsg,string ip,int port,string username){
    Message *temp;
    temp = str2msg(strmsg);
    printstr(STDOUT,strmsg);
    println(STDOUT);
    switch (temp->type) {
        case HEARTBEAT:
            *myself = init_send_UDP(temp->port);
            *server = init_receiverip_UDP(temp->ip,temp->port);
            send_UDP(*myself,*server,msg2str(make_login_message(ip,port,username)));
            break;
        case LOGIN:

            break;
    }
}
