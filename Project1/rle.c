#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]){

    if(argc<2)
        return EXIT_FAILURE;
        
    
    char* in = argv[1];
    if(strlen(in)<=0)
            return EXIT_SUCCESS;

    int boolean = 0;
    for(int i = 0; i<strlen(in); i++)
    {
        if(isdigit(in[i]))
        {
            printf("error");
            boolean = 1;
            break;
        }
    }
    if(boolean==0)
    {
        char* out = malloc(strlen(in)+1);
        int indexOut = 0;
        int indexIn = 0;

        while(indexIn<strlen(in))
        {
            int count = 1;
            while(indexIn+1<strlen(in) && in[indexIn]==in[indexIn+1])
            {
                count++;
                indexIn++;
            }
            //printf("\n%d", indexOut);
            //printf("\n%c%d", in[indexIn], count);
            indexOut += sprintf(indexOut + out, "%c%d", in[indexIn], count);
            //printf("\n%d", indexOut);
            indexIn++;
            count = 1;
        }
        if(indexOut<=indexIn)
        {
            if(strlen(out)!=1 && strlen(out)!=0)
                printf("%s", out);
        }
        else
        {
            printf("%s", in);
        }
    }
    return EXIT_SUCCESS;
}