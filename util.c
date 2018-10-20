#include <stdlib.h>
#include <unistd.h>
#include "util.h"

int str2int(char* input){
  int negative = 0;
  int number = 0;
  int i;
  negative = (input[0]=='-');
  for(i = negative?1:0 ; ; i++){
    if(input[i]=='\0' || input[i]=='\n' || input[i]=='\r')
      break;
    if(input[i]>='0'&&input[i]<='9'){
      number=number*10+input[i]-'0';
    }else return 0;
  }
  return negative?-number:number;
}

void int2str(int input,char* output){
  int neg = (input<0);
  int pointer = 0;
  int i;
  input = neg?-input:input;
  while (1) {
    output[pointer++] = input%10 + '0';
    input/=10;
    if(input == 0){
      if(neg)
        output[pointer++] = '-';
      output[pointer--] = '\0';
      break;
    }
  }
  for(i=0;i<(pointer+1)/2;i++){
    swap_in_carray(output,i,pointer-i);
  }
}

void sort_iarray(int* a,int len){
  int i,j;
  for(i=0;i<len;i++)
    for(j=0;j<len-i-1;j++)
      if(a[j]>a[j+1])
        swap_in_iarray(a,j,j+1);
}

void swap_in_iarray(int* arr,int i,int j){
  arr[j] = arr[i] ^ arr[j];
  arr[i] = arr[i] ^ arr[j];
  arr[j] = arr[i] ^ arr[j];
}

void swap_in_carray(char* arr,int i,int j){
  arr[j] = arr[i] ^ arr[j];
  arr[i] = arr[i] ^ arr[j];
  arr[j] = arr[i] ^ arr[j];
}

string new_string(string input){
    return stradd(input,"");
}

string new_empty_string(int length){
    string ret = (string)malloc(length+1 * sizeof(char));
    ret[length] = '\0';
    return ret;
}

bool str_comp(string first,string second){
    int i;
    for(i=0;TRUE;i++){
        if(first[i]=='\0'||second[i]=='\0')break;
        if(first[i]!=second[i])return FALSE;
    }
    if(first[i]==second[i])return TRUE;
    return FALSE;
}

int number_of_tokens(string main,char spiliter){
    int counter=0;
    int i;
    bool check = FALSE;
    for(i=0;TRUE;i++){
        if(main[i]=='\0')break;
        if(main[i]!=spiliter){
            if(!check){
                check=TRUE;
                counter++;
            }
        }else{
            check=FALSE;
        }
    }
    return counter;
}

string get_token(string main,char spiliter,int part_number){
    string ret;
    int counter=-1,length=0;
    int i,j;
    for(i=0;;i++){
        if(main[i]=='\0')break;
        if(main[i]!=spiliter){
            counter++;
            length = strlen_to_char(main+i,spiliter);
            if(counter==part_number)break;
            i+=length;
        }
    }
    ret = new_empty_string(length);
    j = i;
    for(i=0;i<length;i++)
        ret[i]=main[j+i];
    ret[length]='\0';
    return ret;
}

int strlen_(string main){
    return strlen_to_char(main,'\0');
}

int strlen_to_char(string main,char to){
    int i;
    for(i=0;TRUE;i++){
        if(main[i]=='\0'||main[i]==to)break;
    }
    return i;
}

int intstrlen(int input){
    int len;
    string temp = new_empty_string(100);
    int2str(input,temp);
    len = strlen_(temp);
    free(temp);
    return len;
}

string stradd(string first,string second){
    int len1,len2;
    int i;
    string ret;
    len1=strlen_(first);
    len2=strlen_(second);
    ret = new_empty_string(len1+len2);
    for(i=0;i<len1;i++)
        ret[i]=first[i];
    for(i=0;i<len2;i++)
        ret[i+len1]=second[i];
    ret [len1+len2]='\0';
    return ret;
}

void strcopy(string from,string to){
    int i;
    for(i=0;;i++){
        to[i] = from[i];
        if(to[i])break;
    }
}


string readstr(int fd,int size){
    string buf = new_empty_string(size);
    read(fd,buf,size);
    return buf;
}

int readint(int fd){
    int i;
    string buf = readstr(fd,20);
    i = str2int(buf);
    free(buf);
    return i;
}

void printint(int fd,int num){
    string buf = new_empty_string(250);
    int2str(num,buf);
    write(fd,buf,strlen_(buf)+1);
    free(buf);
}

void printstr(int fd,string inp){
    write(fd,inp,strlen_(inp)+1);
}

void println(int fd){
    write(fd,"\n",2);
}

void printspaces(int fd,int count){
    int i;
    for(i=0;i<count;i++)
        write(fd," ",2);
}
