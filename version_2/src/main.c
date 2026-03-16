#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morseTree.h"

#define MAX 10000000

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

    size_t len=fread(buffer,1,MAX-1,in);
    buffer[len]='\0';

    fclose(in);

    FILE *out=fopen("output.txt","w");

    if(strcmp(argv[1],"-e")==0)
        encodeText(buffer,out);
    else if(strcmp(argv[1],"-d")==0)
        decodeText(buffer,out);
    else
        printf("Invalid option\n");

    fclose(out);
    free(buffer);

    return 0;
}
