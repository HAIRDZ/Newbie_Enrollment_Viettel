#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char c;
    const char *code;
} Morse;

Morse table[]={
{'A',"+="},{'B',"=+++"},{'C',"=+=+"},{'D',"=++"},
{'E',"+"},{'F',"++=+"},{'G',"==+"},{'H',"++++"},
{'I',"++"},{'J',"+==="},{'K',"=+="},{'L',"+=++"},
{'M',"=="},{'N',"=+"},{'O',"==="},{'P',"+==+"},
{'Q',"==+="},{'R',"+=+"},{'S',"+++"},{'T',"="},
{'U',"++="},{'V',"+++="},{'W',"+=="},{'X',"=++="},
{'Y',"=+=="},{'Z',"==++"},
{'0',"====="},{'1',"+===="},{'2',"++==="},{'3',"+++=="},
{'4',"++++="},{'5',"+++++"},{'6',"=++++"},{'7',"==+++"},
{'8',"===++"},{'9',"====+"}
};

#define N (sizeof(table)/sizeof(table[0]))

const char* encodeChar(char c)
{
    c=toupper(c);

    for(int i=0;i<N;i++)
        if(table[i].c==c)
            return table[i].code;

    return NULL;
}

char decodeToken(const char *tok)
{
    for(int i=0;i<N;i++)
        if(strcmp(table[i].code,tok)==0)
            return table[i].c;

    return '?';
}

void encodeFile(const char *in,const char *out)
{
    FILE *fi=fopen(in,"r");
    FILE *fo=fopen(out,"w");

    if(!fi||!fo) return;

    int c;
    int first=1;

    while((c=fgetc(fi))!=EOF)
    {
        if(c==' ')
        {
            fprintf(fo," / ");
            first=1;
            continue;
        }

        const char *m=encodeChar(c);
        if(!m) continue;

        if(!first)
            fprintf(fo," ");

        fprintf(fo,"%s",m);
        first=0;
    }

    fclose(fi);
    fclose(fo);
}

void decodeFile(const char *in,const char *out)
{
    FILE *fi=fopen(in,"r");
    FILE *fo=fopen(out,"w");

    if(!fi||!fo) return;

    char token[32];

    while(fscanf(fi,"%31s",token)==1)
    {
        if(strcmp(token,"/")==0)
        {
            fprintf(fo," ");
            continue;
        }

        char c=decodeToken(token);

        if(c=='?')
        {
            printf("Invalid Morse\n");
            fclose(fi);
            fclose(fo);
            return;
        }

        fprintf(fo,"%c",c);
    }

    fclose(fi);
    fclose(fo);
}

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usage:\n");
        printf("./myMorse -e input.txt\n");
        printf("./myMorse -d input.txt\n");
        return 0;
    }

    if(strcmp(argv[1],"-e")==0)
        encodeFile(argv[2],"output.txt");
    else
        decodeFile(argv[2],"output.txt");

    return 0;
}
