#include "gameprint.h"
#include "util.h"


#define SPLITER    "║"
#define HITBLOCK   "▒▒"
#define FULLBLOCK  "██"
#define EMPTYBLOCK "  "
#define MISSBLOCK  "«»"

void print_num_series(int fd){
    int i;
    printstr(fd,"  ");
    for(i=0;i<BOARD_SIZE;i++){
        printint(fd,i);
        printstr(fd," ");
    }
}

void print_header(int fd){
    printstr(fd,"My Board");
    printspaces(fd,14);
    printstr(fd,SPLITER);
    printstr(fd,"Enemy Board");
    println(fd);
    print_num_series(fd);
    printstr(fd,SPLITER);
    print_num_series(fd);
    println(fd);
}

void print_block(int fd,int cell){
    printstr(fd,cell==HIT?HITBLOCK:(cell==FULL?FULLBLOCK:(cell==EMPTY?EMPTYBLOCK:MISSBLOCK)));
}

void print_board_row(int fd,int* row,int rownumber){
    int i;
    printint(fd,rownumber);
    printstr(fd," ");
    for(i=0;i<BOARD_SIZE;i++){
        print_block(fd,row[i]);
    }
}

void print_board(int fd,int **myboard,int **enemyboard){
    int i;
    for(i=0;i<BOARD_SIZE;i++){
        print_board_row(fd,myboard[i],i);
        printstr(fd,SPLITER);
        print_board_row(fd,enemyboard[i],i);
        println(fd);
    }
}

void print_footer(int fd,int myhit,int enemyhit,int total){
    printstr(fd,"hit:");
    printint(fd,enemyhit);
    printspaces(fd,22-intstrlen(enemyhit)-4);
    printstr(fd,SPLITER);
    printstr(fd,"hit:");
    printint(fd,myhit);
    println(fd);
    printstr(fd,"remaining:");
    printint(fd,total - enemyhit);
    printspaces(fd,22-intstrlen(total - enemyhit)-10);
    printstr(fd,SPLITER);
    printstr(fd,"remaining:");
    printint(fd,total - myhit);
    println(fd);
    printstr(fd,"remaining:");
}

void print_game(int fd,GameStat *game){
    print_header(fd);
    print_board(fd,game->myboard,game->enemyboard);
    print_footer(fd,game->myhit,game->enemyhit,game->total);
    printstr(fd,game->myturn?"It's your turn\n":"It's your opponent turn\n");
}
