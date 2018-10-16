#include <stdlib.h>
#include <stdio.h>
#include "StrLib.h"

//sakht string jadid dar hafeze
String NewString(String Input){
    return StrAdder(Input,"");
}
//khuruji dadan stringi ke hame char hayash \0 ast
String NewStringChar0(int NumberOfChars){
    int i;
    String ReturnValue=NewString("");
    for(i=0;i<NumberOfChars;i++){
        ReturnValue=StrAdder(ReturnValue,"a");
        ReturnValue[i]='\0';
    }
    return ReturnValue;
}
//moghayese do string va dadan khuruji yek baraye yeki boodan anha va sefr baraye yeki naboodan
bool StrComp(String First,String Second){
    int i;
    for(i=0;TRUE;i++){
        if(First[i]=='\0'||Second[i]=='\0')break;
        if(First[i]!=Second[i])return FALSE;
    }
    if(First[i]==Second[i])return TRUE;
    return FALSE;
}
//khorji dadan tedad kalamat yek string
int NumberOfTheWords(String MainString,char Spiliter){
    int Counter=0;
    int i;
    bool Check = FALSE;
    for(i=0;TRUE;i++){
        if(MainString[i]=='\0')break;
        if(MainString[i]!=Spiliter){
            if(!Check){
                Check=TRUE;
                Counter++;
            }
        }else{
            Check=FALSE;
        }
    }
    return Counter;
}
//khuruji dadan tool string to yek char moshakhas
int StrLengthToSpecialChar(String MainString,char ToWhat){
    int Counter;
    for(Counter=0;TRUE;Counter++){
        if(MainString[Counter]=='\0'||MainString[Counter]==ToWhat)break;
    }
    return Counter;
}
//khuruji dadan kalame i ba shomare moshakhas
String GetPart(String MainString,char Spiliter,int PartNumber){
    String ReturnPart;
    int Counter=0,Length=0;
    int i,j;
    for(i=0;;i++){
        if(MainString[i]=='\0')break;
        if(MainString[i]!=Spiliter){
            Counter++;
            Length=StrLengthToSpecialChar(MainString+i,Spiliter);
            if(Counter==PartNumber)break;
            i+=Length;
        }
    }
    ReturnPart=(String)malloc(Length+1);
    j=i;
    for(i=0;i<Length;i++)
        ReturnPart[i]=MainString[j+i];
    ReturnPart[Length]='\0';
    return ReturnPart;
}
//jam do string
String StrAdder(String Input1,String Input2){
    int Length1,Length2;
    String ReturnString;
    int i=0;
    Length1=StrLengthToSpecialChar(Input1,'\0');
    Length2=StrLengthToSpecialChar(Input2,'\0');
    ReturnString=malloc(Length1+Length2+1);
    for(i=0;i<Length1;i++)
        ReturnString[i]=Input1[i];
    for(i=0;i<Length2;i++)
        ReturnString[i+Length1]=Input2[i];
    ReturnString [Length1+Length2]='\0';
    return ReturnString;
}
//khuroji dadan khat vared shode tavasot karbar
String ReadLine(){
    String NextChar=NewStringChar0(2);
    String ReturnValue,Temp;
    ReturnValue=NewString("");
    while(TRUE){
        NextChar[0]=getchar();
        if(NextChar[0]!='\n'){
        Temp=StrAdder(ReturnValue,NextChar);
        free(ReturnValue);
        ReturnValue=Temp;
        }else break;
    }
    free(NextChar);
    return ReturnValue;
}
//Tabdil string be int(Bi alamat)
int ToInt(String Input){
    int ReturnValue=0;
    int i;
    for(i=0;;i++){
        if(Input[i]=='\0')break;
        if(!(Input[i]>='0'&&Input[i]<='9'))return -1;
        ReturnValue=ReturnValue*10+Input[i]-48;
    }
    return ReturnValue;
}
//Tabdil int be string
String ParseInt(int Input){
    int i,Length,ValOfInput;
    String ReturnValue;
    ValOfInput=Input;
    for(i=0;ValOfInput!=0;i++)
        ValOfInput=ValOfInput/10;
    Length=i;
    ValOfInput=Input;
    ReturnValue=malloc((Length+1)*sizeof(char));
    for(i=0;i<Length;i++){
        ReturnValue[Length-1-i]=ValOfInput%10+48;
        ValOfInput=ValOfInput/10;
    }
    ReturnValue[Length]='\0';
    return ReturnValue;
}
