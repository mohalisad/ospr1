#ifndef GAME_H
#define GAME_H
#define TRUE  1
#define FALSE 0

struct gamestat{
    int** myboard;
    int** enemyboard;
    int myhit;
    int enemyhit;
    int totalpoint;
};

#endif //GAME_H
