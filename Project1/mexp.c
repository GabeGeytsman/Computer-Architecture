#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printMatrix(int *matrix[], int size) 
{
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      printf("%d", matrix[i][j]);
      if (j != size - 1) {
        printf(" ");
      }
    }
    if(i != size-1) printf("\n");
  }
}

int main(int argc, char* argv[])
{
    if(argc<2)
    {
        printf("failure");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    int size;
    fscanf(file, "%d\n", &size);

    //printf("size : %d\n", size);

    int **matrix = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) 
    {
        matrix[i] = malloc(size * sizeof(int));
    }
    int **result = malloc(size * sizeof(int*));
    for (int q = 0; q < size; q++) 
    {
        result[q] = malloc(size * sizeof(int));
    }
    for (int j = 0; j < size; j++) 
    {
        for (int k = 0; k < size; k++) 
        {
            fscanf(file, "%d", &(matrix[j][k]));
            result[j][k] = matrix[j][k];
        }
    }
    int power;
    fscanf(file, "%d", &power);
    //printf("Power: %d: ", power);

    if(power==1)
        printMatrix(matrix, size);
    else if(power==0)
    {
        //printf("powre 0 case");
        for(int i = 0; i<size; i++)
        {
            for(int j = 0; j<size; j++)
            {
                if(i == j)
                {
                    result[i][j] = 1;
                }
                else
                {
                    result[i][j] = 0;
                }
                
            }
        }
        printMatrix(result, size);
    }
    else
    {
        int **matrix2 = malloc(size * sizeof(int*));
        for (int i = 0; i < size; i++) 
        {
            matrix2[i] = malloc(size * sizeof(int));
        }
            //printf("we are in the correct case");
        //for every power...
        for(int i = 1; i<power; i++)
        {
            //for every row...
            for(int j = 0; j<size; j++)
            {
                //for every entry in the row...
                for(int k = 0; k<size; k++)
                {
                    int newNum = 0;
                    //for every row x column product...
                    for(int l = 0; l<size; l++)
                    {
                        newNum+=result[j][l]*matrix[l][k];
                    }
                    matrix2[j][k] = newNum;
                }
            }
            for(int i = 0; i<size; i++)
            {
                for(int j = 0; j<size; j++)
                {
                    result[i][j] = matrix2[i][j];
                }
            }
        }
        printMatrix(result, size);
        for (int i = 0; i < size; i++) 
        {
            free(matrix2[i]);
        }
    }
    for (int i = 0; i < size; i++) 
    {
        free(matrix[i]);
    }
    for (int i = 0; i < size; i++) 
    {
        free(result[i]);
    }
}