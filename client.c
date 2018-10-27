#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "network.h"
#include "message.h"
#include "game.h"
#include "gameprint.h"
#include "util.h"

void parse_stdin(UDPInfo* server,UDPInfo* myself,UDPInfo* opponent,UDPInfo* gameself,string username,GameStat* game,bool game_mode);
bool parse_message(UDPInfo** server,UDPInfo** myself,UDPInfo** opponent,UDPInfo** gameself,GameStat* game,string strmsg,string ip,int port,string username);

int main(int argc, char *argv[]){
    int *ports,maxfd,last_heartbeat,t,sr,portm,pointer,pmstate;
    string ip,heartbeatmsg,receivedmsg,gamemap,username;
    fd_set rfds;
    UDPInfo *server,*myself,*listener, *hblistener, client,*gameself,*opponent;
    UDPInfo *arr[10];
    GameStat *game;
    struct timeval tv;
    bool server_alive,game_mode;
    ports = parse_input(argc,argv);
    printstr(STDOUT,"Please input your ip:\n");
    ip = readstr(STDIN,20);
    printstr(STDOUT,"Please input your port:\n");
    portm = readint(STDIN);
    printstr(STDOUT,"Please input your username:\n");
    username = readstr(STDIN,20);
    printstr(STDOUT,"Please input your gamemap:\n");
    gamemap = readstr(STDIN,20);
    game = new_game(gamemap);
    //init client
    pointer = 0;
    listener = init_listen_UDP(portm);
    arr[pointer++] = listener;
    hblistener = init_listen_UDP(ports[0]);
    arr[pointer++] = hblistener;
    init_fds(&rfds,&maxfd,&tv,arr,pointer);
    last_heartbeat = time(NULL);
    server_alive = FALSE;
    game_mode = FALSE;
    while ((sr = select(maxfd + 1,&rfds,NULL,NULL,&tv))!=-1){
        if(sr != 0){
            if(FD_ISSET(STDIN, &rfds)){
                if(server_alive||game_mode){
                    parse_stdin(server,myself,opponent,gameself,username,game,game_mode);
                }
            }
            if(FD_ISSET(listener->sock, &rfds)){
                receivedmsg = receive_UDP(listener,&client,100);
                if((pmstate = parse_message(&server,&myself,&opponent,&gameself,game,receivedmsg,ip,portm,username)) > 0){
                    game_mode = TRUE;
                    game->myturn = (pmstate==1);
                    print_game(STDOUT,game);
                }
            }
            if(FD_ISSET(hblistener->sock, &rfds)){
                receivedmsg = receive_UDP(hblistener,&client,100);
                last_heartbeat = time(NULL);
                if(!server_alive){
                    parse_message(&server,&myself,&opponent,&gameself,game,receivedmsg,ip,portm,username);
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

void parse_stdin(UDPInfo* server,UDPInfo* myself,UDPInfo* opponent,UDPInfo* gameself,string username,GameStat* game,bool game_mode){
    string line,part1;
    int x,y;
    line = readstr(STDIN,50);
    part1 = get_token(line,' ',0);
    if(game_mode){
        if(game->myturn){
            if(number_of_tokens(line,' ')==2){
                x = str2int(get_token(line,' ',1));
                y = str2int(get_token(line,' ',0));
                if(!check_enemyhit(game,x,y))
                    send_UDP(gameself,opponent,msg2str(make_attack_message(x,y)));
                else printstr(STDERR,"You have attacked that\n");
            }else printstr(STDERR,"Invalid input\n");
        }else printstr(STDERR,"It's not your turn\n");
    }else if(str_comp(part1,"make_game")){
        if(number_of_tokens(line,' ') < 3){
            if(number_of_tokens(line,' ') == 1){
                send_UDP(myself,server,msg2str(make_game_message(username)));
            }else{
                send_UDP(myself,server,msg2str(make_game_message_with(username,get_token(line,' ',1))));
            }
        }else printstr(STDERR,"Invalid input\n");
    }else printstr(STDERR,"Invalid input\n");
}

//return 1 or 2 when game need to start
int parse_message(UDPInfo** server,UDPInfo** myself,UDPInfo** opponent,UDPInfo** gameself,GameStat* game,string strmsg,string ip,int port,string username){
    Message *temp;
    bool hit;
    temp = str2msg(strmsg);
    printstr(STDOUT,strmsg);
    println(STDOUT);
    switch (temp->type) {
        case HEARTBEAT:
            *myself = init_send_UDP(temp->port);
            *server = init_receiverip_UDP(temp->ip,temp->port);
            send_UDP(*myself,*server,msg2str(make_login_message(ip,port,username)));
            break;
        case BEGINGAME:
            *gameself = init_send_UDP(temp->port);
            *opponent = init_receiverip_UDP(temp->ip,temp->port);
            send_UDP(*gameself,*opponent,msg2str(make_intro_message(ip,port)));
            return 1;
        case INTRO:
            *gameself = init_send_UDP(temp->port);
            *opponent = init_receiverip_UDP(temp->ip,temp->port);
            return 2;
        case ATTACK:
            hit = hit_myboard(game,temp->x,temp->y);
            send_UDP(*gameself,*opponent,msg2str(make_hit_message(temp->x,temp->y,hit)));
            print_game(STDOUT,game);
            if(game->enemyhit == game->total){
                printstr(STDOUT,"You lost.\n");
                exit(0);
            }
            break;
        case HITRESULT:
            hit_enemyboard(game,temp->x,temp->y,temp->hit);
            print_game(STDOUT,game);
            if(game->myhit == game->total){
                printstr(STDOUT,"You win.\n");
                exit(0);
            }
            break;
    }
    return FALSE;
}
