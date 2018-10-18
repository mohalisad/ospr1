#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 10

#define HIT   2
#define FULL  1
#define EMPTY 0
#define MISS -1

struct GameStat{
    int** myboard;
    int** enemyboard;
    int   myhit;
    int   enemyhit;
    int   total;
};

typedef struct GameStat GameStat;

#endif //GAME_H
