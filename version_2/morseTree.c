#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "morseTree.h"

typedef struct{
    char c;
    const char *code;
}Morse;

static Morse table[]={
{'A',".-"}, {'B',"-..."}, {'C',"-.-."}, {'D',"-.."}, {'E',"."},
{'F',"..-."}, {'G',"--."}, {'H',"...."}, {'I',".."}, {'J',".---"},
{'K',"-.-"}, {'L',".-.."}, {'M',"--"}, {'N',"-."}, {'O',"---"},
{'P',".--."}, {'Q',"--.-"}, {'R',".-."}, {'S',"..."}, {'T',"-"},
{'U',"..-"}, {'V',"...-"}, {'W',".--"}, {'X',"-..-"}, {'Y',"-.--"},
{'Z',"--.."},

{'0',"-----"}, {'1',".----"}, {'2',"..---"}, {'3',"...--"},
{'4',"....-"}, {'5',"....."}, {'6',"-...."}, {'7',"--..."},
{'8',"---.."}, {'9',"----."}
};

#define TABLE_SIZE (sizeof(table)/sizeof(table[0]))

static const char* getCode(char c){
    for(size_t i=0;i<TABLE_SIZE;i++)
        if(table[i].c==c)
            return table[i].code;
    return NULL;
}

static char getChar(const char *code){
    for(size_t i=0;i<TABLE_SIZE;i++)
        if(strcmp(table[i].code,code)==0)
            return table[i].c;
    return 0;
}

void encodeText(const char *input,FILE *out){
    for(int i=0;input[i];i++){
        char c=toupper(input[i]);

        if(c==' '){
            fputc(' ',out);
            fputc(' ',out);
            fputc(' ',out);
            continue;
        }

        const char *code=getCode(c);
        if(!code) continue;

        for(int j=0;code[j];j++){
            if(code[j]=='.')
                fputc('+',out);
            else{
                fputc('=',out);
                fputc('=',out);
                fputc('=',out);
            }
        }

        if(input[i+1] && input[i+1]!=' ')
            fputc(' ',out);
    }
}

void decodeText(const char *input,FILE *out){
    char token[32];
    int t=0;

    for(int i=0;input[i];){
        if(input[i]=='+'){
            token[t++]='.';
            i++;
        }
        else if(input[i]=='='){
            if(strncmp(&input[i],"===",3)!=0){
                fprintf(out,"Invalid Morse");
                return;
            }
            token[t++]='-';
            i+=3;
        }
        else if(input[i]==' '){
            int space=0;

            while(input[i]==' '){
                space++;
                i++;
            }

            if(t>0){
                token[t]='\0';
                char c=getChar(token);

                if(!c){
                    fprintf(out,"Invalid Morse");
                    return;
                }

                fputc(c,out);
                t=0;
            }

            if(space>=3)
                fputc(' ',out);
        }
        else{
            fprintf(out,"Invalid Morse");
            return;
        }
    }

    if(t>0){
        token[t]='\0';
        char c=getChar(token);
        if(c) fputc(c,out);
    }
}
