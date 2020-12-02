#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void printMatrix(double *matrix[], int row, int col) 
{
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%lf", matrix[i][j]);
      if (j != col - 1) {
        printf(" ");
      }
    }
    if(i != row-1) printf("\n");
  }
}

double** multiply(double *matrix1[], int row1, int col1, double *matrix2[], int row2, int col2)
{
    //matrix1 is an m x n matrix, matrix2 is n x k matrix, so the product will be an m x k matrix
    double** result = (double**)malloc(row1*sizeof(double*));
    for(int i = 0; i<row1; i++)
    {
        result[i] = (double*)malloc(col2*sizeof(double));
    }

    //for every row
    for(int j = 0; j<row1; j++)
    {
        //for every entry in the row...
        for(int k = 0; k<col2; k++)
        {
            double newNum = 0;
            //for every row x column product...
            for(int l = 0; l<row2; l++)
            {
                newNum+=matrix1[j][l]*matrix2[l][k];
            }
            result[j][k] = newNum;
        }
    }
    return result;
}

double** invert(double *matrix[], int size)
{
    double **original = (double**)malloc(size*sizeof(double*));
    double **identity = (double**)malloc(size*sizeof(double*));

    for(int i = 0; i<size; i++)
    {
        original[i] = (double*)malloc(size*sizeof(double));
        identity[i] = (double*)malloc(size*sizeof(double));
    }
    for(int i = 0; i<size; i++)
    {
        for(int j = 0; j<size; j++)
        {
            if(i==j)
                identity[i][j] = 1;
            else
            {
                identity[i][j] = 0.0;
            }
            original[i][j] = matrix[i][j];
            
        }
    }
    //this is where the fun begins...

    for(int i = 0; i< size; i++)
    {
        double f = original[i][i];
        //dividing row i of M and N by f
        for(int j = 0; j<size; j++)
        {
            original[i][j] = original[i][j]/f;
            identity[i][j] = identity[i][j]/f;
        }
        
        for(int j = i+1; j<size; j++)
        {
            double d = original[j][i];
            for(int k = 0; k<size; k++)
            {
                original[j][k] = original[j][k] - (original[i][k] * d);
                identity[j][k] = identity[j][k] - (identity[i][k] * d);
            }

        }
    }

    for(int i = size-1; i>=0; i--)
    {
        for(int j = i-1; j>=0; j--)
        {
            double ff = original[j][i];
            for(int k = 0; k<size; k++)
            {
                original[j][k] = original[j][k] - (original[i][k] * ff);
                identity[j][k] = identity[j][k] - (identity[i][k] * ff);
            }
        }
    }
    
    return identity;
}

double** transpose(double *matrix[], int row, int col)
{
    double **result = malloc(col*sizeof(double*));
    for(int i = 0; i<col; i++)
    {
        result[i] = (double*)malloc(row*sizeof(double));
    }
    for(int i = 0; i<row; i++)
    {
        for(int j = 0; j<col; j++)
        {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    FILE *train = fopen(argv[1], "r");
    char useless[100];

    fscanf(train, "%s", useless);
    int attributes;
    fscanf(train, "%d", &attributes);
    int houses;
    fscanf(train, "%d", &houses);
    
    double **matrix = malloc(houses * sizeof(double*));
    for (int i = 0; i < houses; i++) 
    {
        matrix[i] = malloc((attributes+1) * sizeof(double));
    }
    double **prices = malloc(houses * sizeof(double));
    for(int i = 0; i< houses; i++)
    {
        prices[i] = malloc(sizeof(double));
    }
    for(int i = 0; i < houses; i++)
    {
        matrix[i][0] = 1;
        for(int j = 1; j<= attributes+1; j++)
        {
            if(j==attributes+1)
            {
                fscanf(train, "%lf", &(prices[i][0]));
            }
            else
            {
                fscanf(train, "%lf", &(matrix[i][j]));
            }
        }
    }

    fclose(train);

    double **m1 = transpose(matrix, houses, attributes+1);
    double **m2 = multiply(m1, attributes+1, houses, matrix, houses, attributes+1);
    double **m3 = invert(m2, attributes+1);
    /*printMatrix(m3, attributes+1, attributes+1);
    printf("\n\n");*/
    //printMatrix(m3, attributes+1, attributes+1);
    double **m4 = multiply(m3, attributes+1, attributes+1, m1, attributes+1, houses);
    double **w = multiply(m4, attributes+1, houses, prices, houses, 1);

    /*free(m1);
    free(m2);
    free(m3);
    free(m4);*/


    FILE *data = fopen(argv[2], "r");
    char useful[100];
    fscanf(data, "%s", useful);
    int atts;    
    fscanf(data, "%d", &atts);         
    int numHouses;
    fscanf(data, "%d", &numHouses);


    double **dataMatrix = malloc(numHouses * sizeof(double));
    for(int i = 0; i<numHouses; i++)
    {
        dataMatrix[i] = malloc((atts+1)*sizeof(double));
    }
    for(int i = 0; i < numHouses; i++)
    {
        dataMatrix[i][0] = 1;
        for(int j = 1; j<= atts; j++)
        {
            fscanf(data, "%lf", &(dataMatrix[i][j]));
        }
    }
    fclose(data);
   
    double **solution = multiply(dataMatrix, numHouses, atts+1, w, attributes+1, 1);

    for(int i = 0; i<numHouses; i++)
    {
        printf("%.0f", solution[i][0]);
        if(i!=numHouses-1)
            printf("\n");
    }
    /*free(w);
    free(solution);*/

    free(m1);
    free(m2);
    free(m3);
    free(m4);
    free(prices);
    free(w);
    free(matrix);
    free(dataMatrix);
    free(solution);

    exit(0);

    //printMatrix(solution, numHouses, 1);
}