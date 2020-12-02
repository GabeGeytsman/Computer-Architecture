#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    if(argc<2)
        return EXIT_FAILURE;

    int numVal = atoi(argv[1]);
    
    int i;

    for(i = 0; i<numVal/1000; i++)
    {
        printf("M");
    }
    numVal = numVal%1000;
    switch (numVal/100)
    {
        case 1:
            printf("C");
            break;
        case 2:
            printf("CC");
            break;
        case 3:
            printf("CCC");
            break;
        case 4:
            printf("CD");
            break;
        case 5:
            printf("D");
            break;
        case 6:
            printf("DC");
            break;
        case 7:
            printf("DCC");
            break;
        case 8:
            printf("DCCC");
            break;
        case 9:
            printf("CM");
    }
    numVal = numVal%100;
    switch (numVal/10)
    {
        case 1:
            printf("X");
            break;
        case 2:
            printf("XX");
            break;
        case 3:
            printf("XXX");
            break;
        case 4:
            printf("XL");
            break;
        case 5:
            printf("L");
            break;
        case 6:
            printf("LX");
            break;
        case 7:
            printf("LXX");
            break;
        case 8:
            printf("LXXX");
            break;
        case 9:
            printf("XC");
    }
    numVal = numVal%10;
    switch (numVal)
    {
        case 1:
            printf("I");
            break;
        case 2:
            printf("II");
            break;
        case 3:
            printf("III");
            break;
        case 4:
            printf("IV");
            break;
        case 5:
            printf("V");
            break;
        case 6:
            printf("VI");
            break;
        case 7:
            printf("VII");
            break;
        case 8:
            printf("VIII");
            break;
        case 9:
            printf("IX");
    }
    return EXIT_SUCCESS;
}