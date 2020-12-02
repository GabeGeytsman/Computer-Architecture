#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct gate
{
    int operation;
    int* invars;
    int* outvars;
    int muxnum;
    int* multi;
    struct gate *nextGate;
};

void printGate(struct gate *in)
{
    while(in!=NULL)
    {
        printf("Gate Operation: %d\n", in->operation);
        if(in->operation == 7)
        {
            for(int i = 0; i<3; i++)
            {
                printf("Input number %d: %d\n", i, in->invars[i]);
            }
            for(int i = 0; i<8; i++)
            {
                printf("Mux number %d: %d\n", i, in->multi[i]);
            }
            for(int i = 0; i<1; i++)
            {
                printf("Output number %d: %d\n", i, in->outvars[i]);
            }
        }
        else if(in->operation == 8)
        {
            for(int i = 0; i<3; i++)
            {
                printf("Input number %d: %d\n", i, in->invars[i]);
            }
            for(int i = 0; i<8; i++)
            {
                printf("Dec output number %d: %d\n", i, in->outvars[i]);
            }
        }
        else
        {
            for(int i = 0; i<2; i++)
            {
                printf("Input number %d: %d\n", i, in->invars[i]);
            }
            for(int i = 0; i<1; i++)
            {
                printf("Output number %d: %d\n", i, in->outvars[i]);
            }
        }
        
        in = in->nextGate;
    }
}

void testGate(struct gate *in, int* varVals, char** varNums);

//TIME TO MAKE OUR GATES:

int* andGate(int* varVals, int var1, int var2, int varout)
{
    if(varVals[var1]==1 && varVals[var2]==1)
    {
        varVals[varout] = 1;
    }
    else
    {
        varVals[varout] = 0;
    }  
    return varVals;
}
int* orGate(int* varVals, int var1, int var2, int varout)
{
    if(varVals[var1]==1 || varVals[var2]==1)
    {
        varVals[varout] = 1;
    }
    else
    {
        varVals[varout] = 0;
    }  
    return varVals;
}
int* nandGate(int* varVals, int var1, int var2, int varout)
{
    if(varVals[var1]==1 && varVals[var2]==1)
    {
        varVals[varout] = 0;
    }
    else
    {
        varVals[varout] = 1;
    }  
    return varVals;
}
int* norGate(int* varVals, int var1, int var2, int varout)
{
    if(varVals[var1]==1 || varVals[var2]==1)
    {
        varVals[varout] = 0;
    }
    else
    {
        varVals[varout] = 1;
    }  
    return varVals;
}
int* xorGate(int* varVals, int var1, int var2, int varout)
{
    if((varVals[var1]==1 && varVals[var2]==0) || (varVals[var1]==0 && varVals[var2]==1))
    {
        varVals[varout] = 1;
    }
    else
    {
        varVals[varout] = 0;
    }  
    return varVals;
}
int* notGate(int* varVals, int var1, int varout)
{
    if(varVals[var1]==1)
    {
        varVals[varout] = 0;
    }
    else
    {
        varVals[varout] = 1;
    }  
    return varVals;
}
int* passGate(int* varVals, int var1, int varout)
{
    if(varVals[var1]==1)
    {
        varVals[varout] = 1;
    }
    else
    {
        varVals[varout] = 0;
    }  
    return varVals;
}
int* muxGate(int* varVals, int* invars, int* multi, int muxnum, int varout)
{
    int base = 1;
    int s = 0;
    for(int i = muxnum-1; i>=0; i--)
    {
        if(varVals[invars[i]]==1)
        {
            s+=base;
        }
        base*=2; 
    }
    varVals[varout] = varVals[multi[s]];
    return varVals;
}
int* decGate(int* varVals, int* invars, int* outvars, int muxnum)
{
    int base = 1;
    int s = 0;
    for(int i = muxnum-1; i>=0; i--)
    {
        if(varVals[invars[i]]==1)
        {
            s+=base;
        }
        base*=2; 
    }
    //printf("base: %d", base);
    for(int i = 0; i<base; i++)
    {
        if(outvars[i]!=-1)
        {
            if(i==s)
            {
                //printf("correct case");
                varVals[outvars[i]] = 1;
                //printf("The value of variable %d is %d", outvars[i], varVals[outvars[i]]);
            }
            else
            {
                varVals[outvars[i]] = 0;
            }
        }
    }
    return varVals;
}

void testTableRow();
void printTableRow(int* currentTableRow, int*varVals, int numInputs, int numOutputs)
{
    for(int i = 0; i<numInputs; i++)
    {
        printf("%d ", varVals[i+2]);
    }
    printf("| ");
    for(int i = 0; i<numOutputs; i++)
    {
        printf("%d", varVals[i+2+numInputs]);
        if(i!=numOutputs-1)
        {
            printf(" ");
        }
    }
}
int* nextTableRow(int* currentTableRow, int numInputs)
{
    int carry = 0;
    for(int i = numInputs-1; i>=0; i--)
    {
        if(i == numInputs-1)
        {
            if(currentTableRow[i] == 0)
            {
                currentTableRow[i] = 1;
                return currentTableRow;
            }
            else if(currentTableRow[i]==1)
            {
                currentTableRow[i] = 0;
                carry = 1;
            }
        }
        else
        {
            if(currentTableRow[i]==0)
            {
                currentTableRow[i] = 1;
                return currentTableRow;
            }
            else
            {
                currentTableRow[i] = 0;
                carry = 1;
            }
            
        }
        
    }
    return currentTableRow;
}
void gateIterator(struct gate* gateList, char** varNums, int* varVals, int numInputs, int numOutputs, int numGates)
{
    struct gate* currentGate;
    if(gateList==NULL)
        printf("BROBLEM");
    else
    {
        //printf("ALSO");
        currentGate = gateList;
        //currentGate = currentGate->nextGate;
        //printf("%d", currentGate->muxnum);
    }
    
    
    int* currentTableRow = malloc(numInputs*sizeof(int));
    for(int i = 0; i<numInputs; i++)
    {
        currentTableRow[i] = 0;
    }
    int pow = 1;
    for(int i = 0; i<numInputs; i++)
    {
        pow = pow*2;
    }
    int boolean = 0;

    for(int i = 0; i<pow; i++)
    {
        
            
        if(boolean != 0)
        {
            printf("\n");
        }
        else
        {
            boolean = 1;
        }
        
        //set truth table
        /*for(int i = 2; i<100; i++)
        {
            varVals[i] = 0;
        }*/
        for(int i = 0; i<numInputs; i++)
        {
            varVals[i+2] = currentTableRow[i];
        }
        while(currentGate!=NULL)
        {
            //printf("%d", currentGate->operation);
            //currentGate = currentGate->nextGate;
            //This is the part where we determine what gate it is and perform the operation

            if(currentGate->operation==1)
            {
                //printf("\nvarVals at 2 is: %d, varVals at 3 is: %d, varVals at 5 is: %d", varVals[2], varVals[3], varVals[5]);
                varVals = andGate(varVals, currentGate->invars[0], currentGate->invars[1], currentGate->outvars[0]);
                //printf("\nNOW, varVals at 2 is: %d, varVals at 3 is: %d, varVals at 5 is: %d", varVals[2], varVals[3], varVals[5]);
            }
            else if(currentGate->operation==2)
            {
                varVals = orGate(varVals, currentGate->invars[0], currentGate->invars[1], currentGate->outvars[0]);
            }
            else if(currentGate->operation==4)
            {
                varVals = norGate(varVals, currentGate->invars[0], currentGate->invars[1], currentGate->outvars[0]);
            }
            else if(currentGate->operation==5)
            {
                varVals = nandGate(varVals, currentGate->invars[0], currentGate->invars[1], currentGate->outvars[0]);
            }
            else if(currentGate->operation==6)
            {
                varVals = xorGate(varVals, currentGate->invars[0], currentGate->invars[1], currentGate->outvars[0]);
            }
            else if(currentGate->operation==3)
            {
                varVals = notGate(varVals, currentGate->invars[0], currentGate->outvars[0]);
            }
            else if(currentGate->operation==9)
            {
                varVals = passGate(varVals, currentGate->invars[0], currentGate->outvars[0]);
            }
            else if(currentGate->operation==7)
            {
                varVals = muxGate(varVals, currentGate->invars, currentGate->multi, currentGate->muxnum, currentGate->outvars[0]);
            }
            else if(currentGate->operation==8)
            {
                varVals = decGate(varVals, currentGate->invars, currentGate->outvars, currentGate->muxnum);
            }
            //Move to next gate
            
            //if(index!=1)
                currentGate = currentGate->nextGate;
        }
        //currentGate = currentGate->nextGate;
        //print row, increment truth table
        printTableRow(currentTableRow, varVals, numInputs, numOutputs);
        currentTableRow = nextTableRow(currentTableRow, numInputs);
        for(int i = 0; i<numInputs; i++)
        {
            varVals[i+2] = currentTableRow[i];
        }
        currentGate = gateList;
    }  
}

int main(int argc, char* argv[])
{
    //printf("HELLOOOOOO");
    FILE *inn = fopen(argv[1], "r");
    if (inn==NULL)
        return EXIT_FAILURE;
    
    int varIndex = 2;
    char** varNums = malloc(100*sizeof(char*));
    for(int i = 0; i<100; i++)
    {
        varNums[i] = malloc(16*sizeof(char));
        strcpy(varNums[i], "max-curve");
    }
    int* varVals = (int*)malloc(100*sizeof(int));
    varVals[0] = 0;
    varVals[1] = 1;
    strcpy(varNums[0], "0");
    strcpy(varNums[1], "1");


    int numOfInputs;
    fscanf(inn, "INPUT %d", &numOfInputs);
    char test[16];
    for(int i = 0; i<numOfInputs; i++)
    {
        fscanf(inn, "%s", test);
        strcpy(varNums[varIndex], test);
        varIndex++;
    }
    int numOfOutputs;
    fscanf(inn, " OUTPUT %d", &numOfOutputs);
    for(int i = 0; i<numOfOutputs; i++)
    {
        fscanf(inn, "%s", test);
        strcpy(varNums[varIndex], test);
        varIndex++;
    }

    //loop to create all your gates
    //Each gate will have a number value:
    //AND   =   1
    //OR    =   2
    //NOT   =   3
    //NOR   =   4
    //NAND  =   5
    //XOR   =   6
    //MUX   =   7
    //DEC   =   8
    //PASS  =   9

    struct gate* gateNode;
    struct gate* gateList;

    char currentGate[12];
    int first = 0;
    int numGates = 0;
    while(fscanf(inn, " %s", currentGate)!=EOF)
    {
        numGates++;
        //printf("IN THE LOOP IN THE LOOP IN THE OOP");
        if(first==0)
        {
            first = 1;
            gateNode = malloc(sizeof(struct gate));
            gateNode->nextGate=NULL;
            gateList = gateNode;
            //printf("%d", gateList->operation);
        }
        else
        {
            gateNode->nextGate = malloc(sizeof(struct gate));
            gateNode = gateNode->nextGate;
            gateNode->nextGate=NULL;
        }
        
        if(strcmp(currentGate, "AND")==0)
        {
            gateNode->operation = 1;
            char var1[16];
            char var2[16];
            fscanf(inn, "%s %s", var1, var2);
            gateNode->invars = malloc(2*sizeof(int));
            gateNode->outvars = malloc(sizeof(int));

            //First input variable:
            if(strcmp(var1, "1")==0)
            {
                gateNode->invars[0] = 1;
            }
            else if(strcmp(var1, "0")==0)
            {
                gateNode->invars[0] = 0;
            }
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var1)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[0]= index-1;
            }
            //printf("%d", gateNode->invars[0]);

            //second input variable:
            if(strcmp(var2, "1")==0)
            {
                gateNode->invars[1] = 1;
            }
            else if(strcmp(var2, "0")==0)
            {
                gateNode->invars[1] = 0;
            }           
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var2)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[1]= index-1;
            }
            //printf("%d", gateNode->invars[1]);

            //output variable
            char varOut[16];
            fscanf(inn, "%s", varOut);
            char comp[16];
            strcpy(comp, varNums[0]);
            int index = 0;
            while(strcmp(comp, varOut)!=0 && index<100)
            {
                strcpy(comp, varNums[index]);
                index++;
            }
            //this is the case where the output variable does not exist yet
            if(index == 100)
            {
                strcpy(varNums[varIndex], varOut);
                gateNode->outvars[0] = varIndex;
                varIndex++;
            }
            else
            {
                 gateNode->outvars[0] = index-1;
            }
            //printf("%d", gateNode->outvars[0]);
        }
        else if(strcmp(currentGate, "OR")==0)
        {
            gateNode->operation = 2;
            char var1[16];
            char var2[16];
            fscanf(inn, "%s %s", var1, var2);
            gateNode->invars = malloc(2*sizeof(int));
            gateNode->outvars = malloc(sizeof(int));

            //First input variable:
            if(strcmp(var1, "1")==0)
            {
                gateNode->invars[0] = 1;
            }
            else if(strcmp(var1, "0")==0)
            {
                gateNode->invars[0] = 0;
            }
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var1)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[0]= index-1;
            }
            //printf("%d", gateNode->invars[0]);

            //second input variable:
            if(strcmp(var2, "1")==0)
            {
                gateNode->invars[1] = 1;
            }
            else if(strcmp(var2, "0")==0)
            {
                gateNode->invars[1] = 0;
            }           
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var2)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[1]= index-1;
            }
            //printf("%d", gateNode->invars[1]);

            //output variable
            char varOut[16];
            fscanf(inn, "%s", varOut);
            char comp[16];
            strcpy(comp, varNums[0]);
            int index = 0;
            while(strcmp(comp, varOut)!=0 && index<100)
            {
                strcpy(comp, varNums[index]);
                index++;
            }
            //this is the case where the output variable does not exist yet
            if(index == 100)
            {
                strcpy(varNums[varIndex], varOut);
                gateNode->outvars[0] = varIndex;
                varIndex++;
            }
            else
            {
                 gateNode->outvars[0] = index-1;
            }
            //printf("%d", gateNode->outvars[0]);
        }
        else if(strcmp(currentGate, "XOR")==0)
        {
            gateNode->operation = 6;
            char var1[16];
            char var2[16];
            fscanf(inn, "%s %s", var1, var2);
            gateNode->invars = malloc(2*sizeof(int));
            gateNode->outvars = malloc(sizeof(int));

            //First input variable:
            if(strcmp(var1, "1")==0)
            {
                gateNode->invars[0] = 1;
            }
            else if(strcmp(var1, "0")==0)
            {
                gateNode->invars[0] = 0;
            }
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var1)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[0]= index-1;
            }
            //printf("%d", gateNode->invars[0]);

            //second input variable:
            if(strcmp(var2, "1")==0)
            {
                gateNode->invars[1] = 1;
            }
            else if(strcmp(var2, "0")==0)
            {
                gateNode->invars[1] = 0;
            }           
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var2)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[1]= index-1;
            }
            //printf("%d", gateNode->invars[1]);

            //output variable
            char varOut[16];
            fscanf(inn, "%s", varOut);
            char comp[16];
            strcpy(comp, varNums[0]);
            int index = 0;
            while(strcmp(comp, varOut)!=0 && index<100)
            {
                strcpy(comp, varNums[index]);
                index++;
            }
            //this is the case where the output variable does not exist yet
            if(index == 100)
            {
                strcpy(varNums[varIndex], varOut);
                gateNode->outvars[0] = varIndex;
                varIndex++;
            }
            else
            {
                 gateNode->outvars[0] = index-1;
            }
            //printf("%d", gateNode->outvars[0]);
        }
        else if(strcmp(currentGate, "NOR")==0)
        {
            gateNode->operation = 4;
            char var1[16];
            char var2[16];
            fscanf(inn, "%s %s", var1, var2);
            gateNode->invars = malloc(2*sizeof(int));
            gateNode->outvars = malloc(sizeof(int));

            //First input variable:
            if(strcmp(var1, "1")==0)
            {
                gateNode->invars[0] = 1;
            }
            else if(strcmp(var1, "0")==0)
            {
                gateNode->invars[0] = 0;
            }
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var1)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[0]= index-1;
            }
            //printf("%d", gateNode->invars[0]);

            //second input variable:
            if(strcmp(var2, "1")==0)
            {
                gateNode->invars[1] = 1;
            }
            else if(strcmp(var2, "0")==0)
            {
                gateNode->invars[1] = 0;
            }           
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var2)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[1]= index-1;
            }
            //printf("%d", gateNode->invars[1]);

            //output variable
            char varOut[16];
            fscanf(inn, "%s", varOut);
            char comp[16];
            strcpy(comp, varNums[0]);
            int index = 0;
            while(strcmp(comp, varOut)!=0 && index<100)
            {
                strcpy(comp, varNums[index]);
                index++;
            }
            //this is the case where the output variable does not exist yet
            if(index == 100)
            {
                strcpy(varNums[varIndex], varOut);
                gateNode->outvars[0] = varIndex;
                varIndex++;
            }
            else
            {
                 gateNode->outvars[0] = index-1;
            }
            //printf("%d", gateNode->outvars[0]);
        }
        if(strcmp(currentGate, "NAND")==0)
        {
            gateNode->operation = 5;
            char var1[16];
            char var2[16];
            fscanf(inn, "%s %s", var1, var2);
            gateNode->invars = malloc(2*sizeof(int));
            gateNode->outvars = malloc(sizeof(int));

            //First input variable:
            if(strcmp(var1, "1")==0)
            {
                gateNode->invars[0] = 1;
            }
            else if(strcmp(var1, "0")==0)
            {
                gateNode->invars[0] = 0;
            }
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var1)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[0]= index-1;
            }
            //printf("%d", gateNode->invars[0]);

            //second input variable:
            if(strcmp(var2, "1")==0)
            {
                gateNode->invars[1] = 1;
            }
            else if(strcmp(var2, "0")==0)
            {
                gateNode->invars[1] = 0;
            }           
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var2)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[1]= index-1;
            }
            //printf("%d", gateNode->invars[1]);

            //output variable
            char varOut[16];
            fscanf(inn, "%s", varOut);
            char comp[16];
            strcpy(comp, varNums[0]);
            int index = 0;
            while(strcmp(comp, varOut)!=0 && index<100)
            {
                strcpy(comp, varNums[index]);
                index++;
            }
            //this is the case where the output variable does not exist yet
            if(index == 100)
            {
                strcpy(varNums[varIndex], varOut);
                gateNode->outvars[0] = varIndex;
                varIndex++;
            }
            else
            {
                 gateNode->outvars[0] = index-1;
            }
            //printf("%d", gateNode->outvars[0]);
        }
        if(strcmp(currentGate, "NOT")==0)
        {
            gateNode->operation = 3;
            char var1[16];
            fscanf(inn, "%s", var1);
            gateNode->invars = malloc(sizeof(int));
            gateNode->outvars = malloc(sizeof(int));

            //First input variable:
            if(strcmp(var1, "1")==0)
            {
                gateNode->invars[0] = 1;
            }
            else if(strcmp(var1, "0")==0)
            {
                gateNode->invars[0] = 0;
            }
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var1)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[0]= index-1;
            }
            //printf("%d", gateNode->invars[0]);

            //output variable
            char varOut[16];
            fscanf(inn, "%s", varOut);
            char comp[16];
            strcpy(comp, varNums[0]);
            int index = 0;
            while(strcmp(comp, varOut)!=0 && index<100)
            {
                strcpy(comp, varNums[index]);
                index++;
            }
            //this is the case where the output variable does not exist yet
            if(index == 100)
            {
                strcpy(varNums[varIndex], varOut);
                gateNode->outvars[0] = varIndex;
                varIndex++;
            }
            else
            {
                 gateNode->outvars[0] = index-1;
            }
            //printf("%d", gateNode->outvars[0]);
        }
        if(strcmp(currentGate, "PASS")==0)
        {
            gateNode->operation = 9;
            char var1[16];
            fscanf(inn, "%s", var1);
            gateNode->invars = malloc(sizeof(int));
            gateNode->outvars = malloc(sizeof(int));

            //First input variable:
            if(strcmp(var1, "1")==0)
            {
                gateNode->invars[0] = 1;
            }
            else if(strcmp(var1, "0")==0)
            {
                gateNode->invars[0] = 0;
            }
            else
            {
                char comp[16];
                strcpy(comp, varNums[0]);
                int index = 0;
                while(strcmp(comp, var1)!=0 && index<100)
                {
                    strcpy(comp, varNums[index]);
                    index++;
                }
                gateNode->invars[0]= index-1;
            }
            //printf("%d", gateNode->invars[0]);

            //output variable
            char varOut[16];
            fscanf(inn, "%s", varOut);
            char comp[16];
            strcpy(comp, varNums[0]);
            int index = 0;
            while(strcmp(comp, varOut)!=0 && index<100)
            {
                strcpy(comp, varNums[index]);
                index++;
            }
            //this is the case where the output variable does not exist yet
            if(index == 100)
            {
                strcpy(varNums[varIndex], varOut);
                gateNode->outvars[0] = varIndex;
                varIndex++;
            }
            else
            {
                 gateNode->outvars[0] = index-1;
            }
            //printf("%d", gateNode->outvars[0]);
        }
        if(strcmp(currentGate, "MULTIPLEXER")==0)
        {
            gateNode->operation = 7;
            /*char var1[16];
            fscanf(inn, "%s", var1);*/
            int num;
            fscanf(inn, "%d", &num);
            gateNode->muxnum = num;
            gateNode->invars = malloc(num*sizeof(int));

            int pow = 1;
            for(int i = 0; i<num; i++)
            {
                pow = pow*2;
            }
            gateNode->multi = malloc(pow*sizeof(int));
            gateNode->outvars = malloc(sizeof(int));

            for(int i = 0; i<pow; i++)
            {
                char varmux[16];
                fscanf(inn, "%s", varmux);

                //First input variable:
                if(strcmp(varmux, "1")==0)
                {
                    gateNode->multi[i] = 1;
                }
                else if(strcmp(varmux, "0")==0)
                {
                    gateNode->multi[i] = 0;
                }
                else
                {
                    char comp[16];
                    strcpy(comp, varNums[0]);
                    int index = 0;
                    while(strcmp(comp, varmux)!=0 && index<100)
                    {
                        strcpy(comp, varNums[index]);
                        index++;
                    }
                    gateNode->multi[i]= index-1;
                }
            }
            for(int i = 0; i<num; i++)
            {
                char varmux[16];
                fscanf(inn, "%s", varmux);

                //First input variable:
                if(strcmp(varmux, "1")==0)
                {
                    gateNode->invars[i] = 1;
                }
                else if(strcmp(varmux, "0")==0)
                {
                    gateNode->invars[i] = 0;
                }
                else
                {
                    char comp[16];
                    strcpy(comp, varNums[0]);
                    int index = 0;
                    while(strcmp(comp, varmux)!=0 && index<100)
                    {
                        strcpy(comp, varNums[index]);
                        index++;
                    }
                    gateNode->invars[i]= index-1;
                }
            }
            char varOut[16];
            fscanf(inn, "%s", varOut);
            char comp[16];
            strcpy(comp, varNums[0]);
            int index = 0;
            while(strcmp(comp, varOut)!=0 && index<100)
            {
                strcpy(comp, varNums[index]);
                index++;
            }
            //this is the case where the output variable does not exist yet
            if(index == 100)
            {
                strcpy(varNums[varIndex], varOut);
                gateNode->outvars[0] = varIndex;
                varIndex++;
            }
            else
            {
                 gateNode->outvars[0] = index-1;
            }
        }
        if(strcmp(currentGate, "DECODER")==0)
        {
            gateNode->operation = 8;
            /*char var1[16];
            fscanf(inn, "%s", var1);*/
            int num;
            fscanf(inn, "%d", &num);
            gateNode->muxnum = num;
            gateNode->invars = malloc(num*sizeof(int));

            int pow = 1;
            for(int i = 0; i<num; i++)
            {
                pow = pow*2;
            }
            gateNode->outvars = malloc(pow*sizeof(int));

            for(int i = 0; i<num; i++)
            {
                char varmux[16];
                fscanf(inn, "%s", varmux);

                //First input variable:
                if(strcmp(varmux, "1")==0)
                {
                    gateNode->invars[i] = 1;
                }
                else if(strcmp(varmux, "0")==0)
                {
                    gateNode->invars[i] = 0;
                }
                else
                {
                    char comp[16];
                    strcpy(comp, varNums[0]);
                    int index = 0;
                    while(strcmp(comp, varmux)!=0 && index<100)
                    {
                        strcpy(comp, varNums[index]);
                        index++;
                    }
                    gateNode->invars[i]= index-1;
                }
            }
            for(int i = 0; i<pow; i++)
            {
                char varOut[16];
                fscanf(inn, "%s", varOut);
                if(strcmp(varOut, "_") == 0)
                {
                    gateNode->outvars[i] = -1;
                }
                else
                {
                    char comp[16];
                    strcpy(comp, varNums[0]);
                    int index = 0;
                    while(strcmp(comp, varOut)!=0 && index<100)
                    {
                        strcpy(comp, varNums[index]);
                        index++;
                    }
                    //this is the case where the output variable does not exist yet
                    if(index == 100)
                    {
                        strcpy(varNums[varIndex], varOut);
                        gateNode->outvars[i] = varIndex;
                        varIndex++;
                    }
                    else
                    {
                        gateNode->outvars[i] = index-1;
                    }
                }
            }
        }        
    }
    //printf("SCANNED INPUT SUCCESSFULLY!");
    //printf("%d", gateList->operation);
    //printGate(gateList);
    //printf("Gate 1 is operation: %d Gate 2 is operation: %d", gateList->operation, gateList->nextGate->operation);
    //testGate(gateList, varVals, varNums);
    gateIterator(gateList, varNums, varVals, numOfInputs, numOfOutputs, numGates);
    //printGate(gateList);
    /*varVals[2] = 0;
    varVals[3] = 1;
    varVals[4] = 0;
    testGate(gateList, varVals, varNums);*/
    //testTableRow();
    return 0;

}



/*void testTableRow()
{
    int* currentTableRow = malloc(4*sizeof(int));
    for(int i = 0; i<4; i++)
    {
        currentTableRow[i] = 0;
    }
    for(int i = 0; i<16; i++)
    {
        for(int i = 0; i<4; i++)
        {
            printf("%d ", currentTableRow[i]);
        }
        printf("\n");
        currentTableRow = nextTableRow(currentTableRow, 4);
    }
}*/



void testGate(struct gate *in, int* varVals, char** varNums)
{
    for(int i = 0; i<7; i++)
    {
        printf("The value of variable %s prior to gate is: %d\n", varNums[i], varVals[i]);
    }
    
    varVals = andGate(varVals, in->invars[0], in->invars[1], in->outvars[0]);
    for(int i = 0; i<7; i++)
    {
        printf("The value of variable %s post gate is: %d\n", varNums[i], varVals[i]);
    }
    
}

