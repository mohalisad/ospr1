#ifndef UTIL_H
#define UTIL_H
#define TRUE  1
#define FALSE 0

typedef int bool;
typedef char*  string;

#define STDIN  0
#define STDOUT 1
#define STDERR 2
#define NULL   0
#define MAX(a,b) a>b?a:b;

void error(string msg);

int    str2int(string inp);
string int2str(int input);
void   sort_iarray(int* a,int len);
void   swap_in_iarray(int* arr,int i,int j);
void   swap_in_carray(char* arr,int i,int j);

string new_string(string input);
string new_empty_string(int length);
bool   str_comp(string first,string second);
int    number_of_tokens(string main,char spiliter);
string get_token(string main,char spiliter,int part_number);
int    strlen_(string main);
int    strlen_to_char(string main,char to);
int    intstrlen(int input);
string stradd(string first,string second);
void   strcopy(string from,string to);
string readstr(int fd,int size);
int    readint(int fd);
void   printint(int fd,int num);
void   printstr(int fd,string inp);
void   println (int fd);
void   printspaces(int fd,int count);

int* parse_input(int argc,char *argv[]);
#endif //UTIL_H
