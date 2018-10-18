#include <stdlib.h>
#include <fcntl.h>
#include "util.h"

#define BOARD_SIZE 10

#define SPLITER    "║"
#define HITBLOCK   "▒▒"
#define FULLBLOCK  "██"
#define EMPTYBLOCK "  "
#define MISSBLOCK  "«»"
#define HIT   2
#define FULL  1
#define EMPTY 0
#define MISS -1


int **read_board(int fd){
    string line,file,part;
    int **ret;
    int i,j;
    ret = malloc(BOARD_SIZE*sizeof(int*));
    file = readstr(fd,500);
    for(i=0;i<BOARD_SIZE;i++){
        ret[i] = malloc(BOARD_SIZE*sizeof(int));
        line = get_token(file,'\n',i);
        for(j = 0;j<BOARD_SIZE;j++){
            part = get_token(line,' ',j);
            ret[i][j] = str2int(part);
            free(part);
        }
        free(line);
    }
    free (file);
    return ret;
}

void print_num_series(){
    int i;
    printstr(STDOUT,"  ");
    for(i=0;i<BOARD_SIZE;i++){
        printint(STDOUT,i);
        printstr(STDOUT," ");
    }
}

void print_block(int cell){
    printstr(STDOUT,cell==HIT?HITBLOCK:(cell==FULL?FULLBLOCK:(cell==EMPTY?EMPTYBLOCK:MISSBLOCK)));
}

void print_board_row(int* row,int rownumber){
    int i;
    printint(STDOUT,rownumber);
    printstr(STDOUT," ");
    for(i=0;i<BOARD_SIZE;i++){
        print_block(row[i]);
    }
}

void print_game(int **board){
    int i;
    print_num_series();
    printstr(STDOUT,SPLITER);
    print_num_series();
    println(STDOUT);
    for(i=0;i<BOARD_SIZE;i++){
        print_board_row(board[i],i);
        printstr(STDOUT,SPLITER);
        print_board_row(board[i],i);
        println(STDOUT);
    }
}
int main(void){
    int fd;
    int **board;
    fd = open("data",O_RDONLY);
    board = read_board(fd);
    print_game(board);
}
