#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]){

    if(argc<2)
        return EXIT_FAILURE;
    
    char* in = argv[1];

    int index = 0;
    //printf("%d", strlen(in));
    for(int i = 0; i<strlen(in); i++)
    {
        if(isalpha(in[i])!=0)
        {
            index++;
        }        
    }
    //printf("%d", index);
    char* onlyLetters = malloc(index);
    int index2 = 0;
    
    for(int i = 0; i<strlen(in); i++)
    {
        if(isalpha(in[i]))
        {
            onlyLetters[index2] = tolower(in[i]);
            index2++;
            //printf("%c", onlyLetters[index2-1]);
        }
    }

    int false = 0;
    for(int i = 0; i<index/2; i++)
    {
        if(onlyLetters[i]!=onlyLetters[(index-1)-i])
        {
            false = 1;
            //printf("%c", onlyLetters[i]);
            //printf("%d", strlen(onlyLetters));
            //printf("%c", onlyLetters[(index-1)-i]);
            break;
        }
    }
    if(false==0)
        printf("yes");
    else
        printf("no");

    return EXIT_SUCCESS;
}
