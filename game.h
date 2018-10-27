#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 10

#define HIT   2
#define FULL  1
#define EMPTY 0
#define MISS -1

typedef int bool;
typedef struct GameStat GameStat;

struct GameStat{
    int** myboard;
    int** enemyboard;
    int   myhit;
    int   enemyhit;
    int   total;
    bool   myturn;
};

GameStat *new_game(char* file);
bool check_enemyhit(GameStat *game,int x,int y);
bool hit_myboard(GameStat *game,int x,int y);
void hit_enemyboard(GameStat *game,int x,int y,bool success);

#endif //GAME_H
