#ifndef USER_H
#define USER_H

typedef struct User User;

struct User{
    char* ip;
    char* username;
    int   port;
    User* next;
};

User* make_empty_user();
User* make_user(char* ip,int port,char* username);
void add_to_end(User* start,User* new);
User* get_user_by_name(User* start,char* name);
void remove_user_by_name(User* start,char* name);

#endif
