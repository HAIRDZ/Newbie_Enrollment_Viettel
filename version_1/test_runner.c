#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUF 2000
#define MAX_STR 100

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";

void writeFile(const char *name,const char *data)
{
    FILE *f=fopen(name,"w");
    if(!f){printf("Cannot open %s\n",name);exit(1);}
    fprintf(f,"%s",data);
    fclose(f);
}

void readFile(const char *name,char *buf)
{
    FILE *f=fopen(name,"r");
    if(!f){printf("Cannot read %s\n",name);exit(1);}
    fgets(buf,MAX_BUF,f);
    fclose(f);
}

void generateRandomString(char *out,int len)
{
    int alphabetSize=strlen(alphabet);

    for(int i=0;i<len;i++)
    {
        int r=rand()%alphabetSize;
        out[i]=alphabet[r];
    }

    out[len]='\0';
}

void trimNewline(char *s)
{
    int n=strlen(s);
    if(n>0 && s[n-1]=='\n')
        s[n-1]='\0';
}

int runEncodeDecodeTest()
{
    char input[MAX_STR];
    char decoded[MAX_STR];
    char buffer[MAX_BUF];

    int len=rand()%20+1;

    generateRandomString(input,len);

    writeFile("test_input.txt",input);

    system("./my_morse -e test_input.txt > /dev/null");

    readFile("output.txt",buffer);

    writeFile("test_morse.txt",buffer);

    system("./my_morse -d test_morse.txt > /dev/null");

    readFile("output.txt",decoded);

    trimNewline(decoded);

    if(strcmp(input,decoded)==0)
        return 1;
    else
    {
        printf("\nMismatch detected\n");
        printf("Original : %s\n",input);
        printf("Decoded  : %s\n",decoded);
        return 0;
    }
}

void runInvalidTest()
{
    printf("\nRunning invalid Morse test\n");

    writeFile("invalid.txt","+++ ====+");

    system("./my_morse -d invalid.txt");
}

int main()
{
    srand(time(NULL));

    int pass=0;
    int fail=0;

    printf("==== MORSE TEST RUNNER ====\n");

    for(int i=0;i<20;i++)
    {
        if(runEncodeDecodeTest())
        {
            printf("Test %d: PASS\n",i+1);
            pass++;
        }
        else
        {
            printf("Test %d: FAIL\n",i+1);
            fail++;
        }
    }

    runInvalidTest();

    printf("\n==== TEST SUMMARY ====\n");
    printf("PASS : %d\n",pass);
    printf("FAIL : %d\n",fail);

    return 0;
}
