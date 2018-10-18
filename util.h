#ifndef UTIL_H
#define UTIL_H
#define TRUE  1
#define FALSE 0

typedef int bool;

#define STDIN  0
#define STDOUT 1
#define STDERR 2
typedef char*  string;

int  str2int(string inp);
void int2str(int input,string output);
void sort_iarray(int* a,int len);
void swap_in_iarray(int* arr,int i,int j);
void swap_in_carray(char* arr,int i,int j);

string new_string(string input);
string new_empty_string(int length);
bool   str_comp(string first,string second);
int    number_of_tokens(string main,char spiliter);
string get_token(string main,char spiliter,int part_number);
int    strlen_(string main);
int    strlen_to_char(string main,char to);
string stradd(string first,string second);
string readstr(int fd,int size);
int    readint(int fd);
void   printint(int fd,int num);
void   printstr(int fd,string inp);
void   println (int fd);
#endif //UTIL_H
