#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1000

typedef struct {
    char character;
    const char *morse;
} MorseMap;

/* Morse table (. -> + , - -> ===) */

MorseMap morseTable[] = {

{'A',"+==="},{'B',"===+++"},{'C',"===+===+"},{'D',"===++"},{'E',"+"},
{'F',"++===+"},{'G',"======+"},{'H',"++++"},{'I',"++"},{'J',"+========="},
{'K',"===+==="},{'L',"+===++"},{'M',"======"},{'N',"===+"},{'O',"========="},
{'P',"+======+"},{'Q',"======+==="},{'R',"+===+"},{'S',"+++"},{'T',"==="},
{'U',"++==="},{'V',"+++==="},{'W',"+======"},{'X',"===++==="},{'Y',"===+======"},{'Z',"======++"},

/* numbers */

{'1',"+============"},
{'2',"++=========="},
{'3',"+++========"},
{'4',"++++======"},
{'5',"+++++"},
{'6',"===++++"},
{'7',"======+++"},
{'8',"=========++"},
{'9',"============+"},
{'0',"=============="}

};

int tableSize = sizeof(morseTable) / sizeof(MorseMap);

const char* encodeChar(char c)
{
    for(int i = 0; i < tableSize; i++)
    {
        if(morseTable[i].character == c)
            return morseTable[i].morse;
    }

    return NULL;
}

char decodeToken(const char *token)
{
    for(int i = 0; i < tableSize; i++)
    {
        if(strcmp(morseTable[i].morse, token) == 0)
            return morseTable[i].character;
    }

    return '?';
}

void encodeFile(const char *fileName)
{
    FILE *in = fopen(fileName,"r");

    if(!in)
    {
        printf("Cannot open file\n");
        return;
    }

    FILE *out = fopen("output.txt","w");

    int c;
    int printed = 0;

    while((c = fgetc(in)) != EOF)
    {
        if(c == ' ')
        {
            fprintf(out,"   ");

            if(printed < 20)
            {
                if(printed + 3 <= 20)
                {
                    printf("   ");
                    printed += 3;
                }
                else
                {
                    int remain = 20 - printed;
                    fwrite("   ",1,remain,stdout);
                    printed = 20;
                }
            }

            continue;
        }

        c = toupper(c);

        const char *morse = encodeChar(c);

        if(!morse)
            continue;

        fprintf(out,"%s ",morse);

        int len = strlen(morse) + 1;

        if(printed < 20)
        {
            if(printed + len <= 20)
            {
                printf("%s ",morse);
                printed += len;
            }
            else
            {
                int remain = 20 - printed;
                fwrite(morse,1,remain,stdout);
                printed = 20;
            }
        }
    }

    printf("\n");

    fclose(in);
    fclose(out);
}

void decodeFile(const char *fileName)
{
    FILE *in = fopen(fileName,"r");

    if(!in)
    {
        printf("Cannot open file\n");
        return;
    }

    FILE *out = fopen("output.txt","w");

    char buffer[MAX_INPUT];

    if(!fgets(buffer,sizeof(buffer),in))
    {
        fclose(in);
        fclose(out);
        return;
    }

    int printed = 0;
    int i = 0;
    int len = strlen(buffer);

    while(i < len)
    {
        while(i < len && buffer[i] == ' ')
            i++;

        if(i >= len)
            break;

        char token[128];
        int k = 0;

        while(i < len && (buffer[i] == '+' || buffer[i] == '='))
        {
            token[k++] = buffer[i];
            i++;
        }

        token[k] = '\0';

        char c = decodeToken(token);

        if(c == '?')
        {
            printf("Invalid Morse\n");
            fclose(in);
            fclose(out);
            return;
        }

        fprintf(out,"%c",c);

        if(printed < 20)
        {
            printf("%c",c);
            printed++;
        }

        int spaces = 0;

        while(i < len && buffer[i] == ' ')
        {
            spaces++;
            i++;
        }

        if(spaces >= 3)
        {
            fprintf(out," ");

            if(printed < 20)
            {
                printf(" ");
                printed++;
            }
        }
    }

    printf("\n");

    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: my_morse -e|-d <input_file>\n");
        return 1;
    }

    if(strcmp(argv[1],"-e") == 0)
    {
        encodeFile(argv[2]);
    }
    else if(strcmp(argv[1],"-d") == 0)
    {
        decodeFile(argv[2]);
    }
    else
    {
        printf("Invalid option\n");
    }

    return 0;
}
