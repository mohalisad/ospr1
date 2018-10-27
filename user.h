#ifndef USER_H
#define USER_H

typedef struct User User;

struct User{
    char* ip;
    char* username;
    int   port;
    User* next;
    int   ready_to_play;
    int   pending;
    char* pend_who;
};

User* make_empty_user();
User* make_user(char* ip,int port,char* username);
void  add_to_end(User* start,User* new);
User* get_user_by_name(User* start,char* name);
void  remove_user_by_name(User* start,char* name);
User* find_ready_to_play(User* start);
User* find_pending(User* start,char* name);
void  make_game(User* first,User* p1,User* p2);

#endif
