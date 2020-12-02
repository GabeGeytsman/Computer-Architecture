
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
            printf("%s", out);
        }
        else
        {
            printf("%s", in);
        }
    }
    return EXIT_SUCCESS;
}