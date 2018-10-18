#include <stdlib.h>
#include <fcntl.h>
#include "util.h"
#include "game.h"
#include "gameprint.h"

int **read_board(int file,int *counter){
    string line,lines,part;
    int **ret;
    int i,j;
    *counter = 0;
    ret = malloc(BOARD_SIZE*sizeof(int*));
    lines = readstr(file,500);
    for(i=0;i<BOARD_SIZE;i++){
        ret[i] = malloc(BOARD_SIZE*sizeof(int));
        line = get_token(lines,'\n',i);
        for(j = 0;j<BOARD_SIZE;j++){
            part = get_token(line,' ',j);
            if ((ret[i][j] = str2int(part)))
                (*counter)++;
            free(part);
        }
        free(line);
    }
    free (lines);
    return ret;
}

int **empty_board(void){
    int **ret;
    int i,j;
    ret = malloc(BOARD_SIZE*sizeof(int*));
    for(i=0;i<BOARD_SIZE;i++){
        ret[i] = malloc(BOARD_SIZE*sizeof(int));
        for(j = 0;j<BOARD_SIZE;j++)
            ret[i][j] = 0;
    }
    return ret;
}

GameStat *new_game(int file){
    GameStat *game;
    game = malloc(sizeof(GameStat));
    game->myboard = read_board(file,&(game->total));
    game->enemyboard = empty_board();
    game->myhit = 0;
    game->enemyhit = 0;
    return game;
}

bool check_enemyhit(GameStat *game,int x,int y){
    return game->enemyboard[x][y]!=0;
}

bool hit_myboard(GameStat *game,int x,int y){
    if(game->myboard[x][y]!=HIT && game->myboard[x][y]!=MISS){
        if(game->myboard[x][y]==FULL){
            game->myboard[x][y] = HIT;
            game->enemyhit++;
            return TRUE;
        }else{
            game->myboard[x][y] = MISS;
        }
    }
    return FALSE;
}

void hit_enemyboard(GameStat *game,int x,int y,bool success){
    game->enemyboard[x][y] = success?HIT:MISS;
    if(success)
        game->myhit++;
}

int main(void){
    int file;
    GameStat *game;
    file = open("data",O_RDONLY);
    game = new_game(file);
    hit_myboard(game,1,5);
    hit_myboard(game,1,5);
    hit_myboard(game,0,5);
    hit_myboard(game,1,4);
    hit_enemyboard(game,7,7,1);
    hit_enemyboard(game,6,6,0);
    print_game(STDOUT,game);
}
