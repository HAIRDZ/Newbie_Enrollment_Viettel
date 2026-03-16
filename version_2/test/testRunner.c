#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 4096
#define RANDOM_TESTS 30

void trim(char *s){
    int len=strlen(s);
    while(len>0 && (s[len-1]=='\n' || s[len-1]=='\r'))
        s[--len]='\0';
}

void runEncode(const char *input,char *output){
    FILE *f=fopen("tmp_input.txt","w");
    fprintf(f,"%s",input);
    fclose(f);

    system("./my_morse -e tmp_input.txt");

    f=fopen("output.txt","r");

    if(fgets(output,MAX,f)==NULL)
        output[0]='\0';

    fclose(f);
    trim(output);
}

void runDecode(const char *input,char *output){
    FILE *f=fopen("tmp_input.txt","w");
    fprintf(f,"%s",input);
    fclose(f);

    system("./my_morse -d tmp_input.txt");

    f=fopen("output.txt","r");

    if(fgets(output,MAX,f)==NULL)
        output[0]='\0';

    fclose(f);
    trim(output);
}

void runTest(const char *input,int id,int *pass,int *fail){
    char encoded[MAX];
    char decoded[MAX];

    runEncode(input,encoded);
    runDecode(encoded,decoded);

    printf("Test %d\n",id);
    printf("Input   : '%s'\n",input);
    printf("Encoded : %s\n",encoded);
    printf("Decoded : '%s'\n",decoded);

    if(strcmp(input,decoded)==0){
        printf("Result  : PASS\n\n");
        (*pass)++;
    }else{
        printf("Result  : FAIL\n\n");
        (*fail)++;
    }
}

void randomString(char *s,int len){
    const char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    int size=strlen(alphabet);

    char prev='A';

    for(int i=0;i<len;i++){
        char c=alphabet[rand()%size];

        if(prev==' ' && c==' ')
            c='A';

        if(i==len-1 && c==' ')
            c='A';

        s[i]=c;
        prev=c;
    }

    s[len]='\0';
}

int main(){
    srand(time(NULL));

    int pass=0;
    int fail=0;
    int id=1;

    printf("==== MORSE DEBUG TEST RUNNER ====\n\n");

    const char *cases[]={
        "HELLO",
        " HELLO",
        "HELLO",
        "HELLO WORLD",
        "A B C",
        "TEST",
        "SOS",
        "A",
        "HELLO MORSE",
        "TEST 123",
        "CODE123",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "0123456789"
    };

    int count=sizeof(cases)/sizeof(cases[0]);

    for(int i=0;i<count;i++)
        runTest(cases[i],id++,&pass,&fail);

    printf("==== RANDOM TESTS ====\n\n");

    char input[MAX];

    for(int i=0;i<RANDOM_TESTS;i++){
        int len=rand()%30+1;
        randomString(input,len);
        runTest(input,id++,&pass,&fail);
    }

    printf("==== TEST SUMMARY ====\n");
    printf("PASS : %d\n",pass);
    printf("FAIL : %d\n",fail);

    return 0;
}
