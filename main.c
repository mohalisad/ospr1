#include "util.h"

int main(void){
  string a;
  a = readstr(STDIN);
  printint(STDOUT,number_of_tokens(a,' '));
  println(STDOUT);
  printstr(STDOUT,get_token(a,' ',1));
  println(STDOUT);
}
