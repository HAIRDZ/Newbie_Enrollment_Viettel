#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char c;
    const char *morse;
} Morse;

Morse table[] = {
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

#define TABLE_SIZE (sizeof(table)/sizeof(table[0]))

const char* encodeChar(char c)
{
    c = toupper(c);
    for(size_t i=0;i<TABLE_SIZE;i++)
        if(table[i].c == c)
            return table[i].morse;
    return NULL;
}

char decodeToken(const char *tok)
{
    for(size_t i=0;i<TABLE_SIZE;i++)
        if(strcmp(table[i].morse,tok)==0)
            return table[i].c;
    return '?';
}

void encodeFile(const char *inFile,const char *outFile)
{
    FILE *in=fopen(inFile,"r");
    FILE *out=fopen(outFile,"w");
    if(!in||!out) return;

    int c;
    int printed=0;
    int first=1;

    while((c=fgetc(in))!=EOF)
    {
        if(c=='\n') continue;

        if(c==' ')
        {
            fprintf(out,"|");
            if(printed<20){ printf("|"); printed++; }
            first=1;
            continue;
        }

        const char *m=encodeChar(c);
        if(!m) continue;

        if(!first)
        {
            fprintf(out," ");
            if(printed<20){ printf(" "); printed++; }
        }

        fprintf(out,"%s",m);

        for(int i=0;m[i] && printed<20;i++)
        {
            printf("%c",m[i]);
            printed++;
        }

        first=0;
    }

    printf("\n");

    fclose(in);
    fclose(out);
}

void decodeFile(const char *inFile,const char *outFile)
{
    FILE *in=fopen(inFile,"r");
    FILE *out=fopen(outFile,"w");
    if(!in||!out) return;

    char token[32];
    int idx=0;
    int printed=0;
    int c;

    while((c=fgetc(in))!=EOF)
    {
        if(c=='+'||c=='=')
        {
            token[idx++]=c;
        }
        else
        {
            if(idx>0)
            {
                token[idx]='\0';

                char d=decodeToken(token);
                if(d=='?')
                {
                    printf("Invalid Morse\n");
                    fclose(in);
                    fclose(out);
                    return;
                }

                fprintf(out,"%c",d);
                if(printed<20){ printf("%c",d); printed++; }

                idx=0;
            }

            if(c=='|')
            {
                fprintf(out," ");
                if(printed<20){ printf(" "); printed++; }
            }
        }
    }

    if(idx>0)
    {
        token[idx]='\0';

        char d=decodeToken(token);
        if(d=='?')
        {
            printf("Invalid Morse\n");
            fclose(in);
            fclose(out);
            return;
        }

        fprintf(out,"%c",d);
        if(printed<20) printf("%c",d);
    }

    printf("\n");

    fclose(in);
    fclose(out);
}

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usage:\n");
        printf("./my_morse -e input.txt\n");
        printf("./my_morse -d input.txt\n");
        return 0;
    }

    if(strcmp(argv[1],"-e")==0)
        encodeFile(argv[2],"output.txt");
    else if(strcmp(argv[1],"-d")==0)
        decodeFile(argv[2],"output.txt");
    else
        printf("Invalid option\n");

    return 0;
}
