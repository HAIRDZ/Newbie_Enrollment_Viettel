#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morseTree.h"

#define MAX 10000000

void printFirst20(const char *file)
{
    FILE *f = fopen(file,"r");
    if(!f)
        return;

    int c;
    int count = 0;

    while((c=fgetc(f))!=EOF && count<20)
    {
        putchar(c);
        count++;
    }

    printf("\n");

    fclose(f);
}

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usage: my_morse -e|-d file\n");
        return 1;
    }

    FILE *in=fopen(argv[2],"r");
    if(!in)
    {
        printf("Cannot open input file\n");
        return 1;
    }

    char *buffer=malloc(MAX);
    if(!buffer)
        return 1;

    size_t len=fread(buffer,1,MAX-1,in);
    buffer[len]='\0';

    fclose(in);

    FILE *out=fopen("output.txt","w");
    if(!out)
        return 1;

    if(strcmp(argv[1],"-e")==0)
        encodeText(buffer,out);
    else if(strcmp(argv[1],"-d")==0)
        decodeText(buffer,out);
    else
    {
        printf("Invalid option\n");
        fclose(out);
        free(buffer);
        return 1;
    }

    fclose(out);
    free(buffer);

    printFirst20("output.txt");

    return 0;
}
