/*******************************
Kevin Pirabaharan
kpirabah@mail.uoguelph.ca
This program emulates a memory management
*******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListFunctions.c"

int const memSize = 128;
void bestFit(int *processSize, char *ID, int theSize);
void worstFit(int *processSize, char *ID, int theSize);
void nextFit(int *processSize, char *ID, int theSize);
void firstFit(int *processSize, char *ID, int theSize);
void addNext(char *visualMem, int numProcesses, char *ID);
void searchMemory(char *visualMem, struct Node cNode);
int checkNumArray(int numProc);
int checkMem(char *procA);
int countHoles(char *procA);
int countProcesses(char *procA);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("UNSUCCESSFUL EXECUTION\n");
        printf("Arguments should be 'Program inputFile'\n");
        printf("Program requires 2 arguements, you inputted %d!\n", argc);

        if (argc > 2)
        {
            argc = argc - 2;
            printf("You have %d too many arguments, get rid of them\n", argc);
            return 1;
        }
        else
        {
            printf("You are missing the inputFile in your argument(s), please add it.\n");
            return 1;
        }
    }

    FILE *processFile;
    processFile = fopen(argv[1], "r");
    int processSize[256];
    char ID[256];
    int size, theSize, keepGoing = 1, i = 0;
    char processID;

    while (keepGoing == 1)
    {
        if (fscanf(processFile, "%s %d", &processID, &size) != EOF)
        {
            processSize[i] = size;
            ID[i] = processID;
            i++;
        }
        else
        {
            theSize = i;
            keepGoing = 0;
        }
    }
    //Call all sortting methods for memory management.
    printf("\nFirst Fit Results: \n");
    firstFit(processSize, ID, theSize);
    fclose(processFile);
    return 0;
}

void firstFit(int *processSize, char *ID, int theSize)
{
    int numProcesses = 1;
    char visualMem[memSize];
    for (int i = 0; i < theSize; i++)
    {
        //No Space Found and therefore remove oldest process to Tail of queue
        addToTail(processSize[i], ID[i], 0, 0, 0);
        numProcesses++;
    }
    //Insert Processes
    for (int i = 0; i < memSize; i++)
    {
        visualMem[i] = '-';
    }
    addNext(visualMem, numProcesses, ID);
}

void addNext(char *visualMem, int numProcesses, char *ID)
{
    //Variables for Log
    double static overallCount, totalMem, totalLoads, totalOverallCount, totalHoles;
    int static old;
    int keepGoing = 1, done = 0;
    while (keepGoing == 1)
    {
        int numProMem, holes;
        double memusage, overall;
        holes = countHoles(visualMem);
        numProMem = countProcesses(visualMem);
        memusage = checkMem(visualMem);
        memusage = (memusage / memSize) * 100;
        totalMem = totalMem + memusage;
        overall = (totalMem / overallCount);
        printf("%c loaded, #processes = %d, #holes = %d, %%memusage = %.2lf, cumulative %%mem = %.2lf \n", ID[numProcesses], numProMem, holes, memusage, overall);
        overallCount++;
        totalHoles = totalHoles + holes;
        totalOverallCount = totalOverallCount + (totalMem / overallCount);
        totalLoads = totalLoads + numProMem;
        if ((done = checkNumArray(numProcesses)) != 0)
        {
            keepGoing = 0;
        }
        //Add proccess to memory
        else
        {
            int offset, freeMem = 0;
            for (int k = 1; k <= 2; k++)
            {
                if (k == 1)
                {
                    for (int i = 0; i < 128; i++)
                    {
                        if (visualMem[i] == '-')
                        {
                            offset = i;
                            break;
                        }
                    }
                }
                if (k == 2)
                {
                    for (int i = 0; i < 128; i++)
                    {
                        if (visualMem[i] == '-')
                        {
                            freeMem++;
                        }
                        if (visualMem[i] != '-')
                        {
                            break;
                        }
                    }
                }
            }
            struct Node node;
            node = gethead();
            //If free memory is too small, remove oldest memory
            if (node.Data + offset > 128)
            {
                {
                    searchMemory(visualMem, node);
                }
                if (freeMem < node.Data)
                {
                    searchMemory(visualMem, node);
                }
                //If memory has enough space, add it to the end of the previous element
            }
            else
            {
                for (int j = offset; j < (node.Data + offset); j++)
                {
                    visualMem[j] = node.ID;
                }
                removeFromhead();
                if (node.timesRunThroughQueue < 3)
                {
                    addToTail(node.Data, node.ID, offset, (node.timesRunThroughQueue + 1), (old + 1));
                }
                old++;
            }
        }
    }
    //This is the final result
    printf("\nTotal loads =%.0lf, average #processes = %.2lf average #holes = %.2lf, cumulative %%mem =%.2lf \n\n", (totalLoads),
           (totalLoads / overallCount), (totalHoles / overallCount), (totalOverallCount / overallCount));
}

int checkNumArray(int numProc)
{
    int timesRunThroughQueue = 1;
    struct Node *tempPtr = tail;
    while (tempPtr != NULL)
    {
        if (tempPtr->timesRunThroughQueue == 3)
        {
            timesRunThroughQueue = timesRunThroughQueue + 1;
        }
        tempPtr = tempPtr->nextPtr;
    }
    if (timesRunThroughQueue == numProc)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkMem(char *procA)
{
    int numPro = 0;
    for (int i = 0; i < 128; i++)
    {
        if (procA[i] != '-')
        {
            numPro++;
        }
    }
    return numPro;
}

int countHoles(char *procA)
{
    int endFound = 0, numHoles = 1;
    for (int i = 0; i < 128; i++)
    {
        if (procA[i] == '-')
        {
            for (int j = i; j < 128; j++)
            {
                if (procA[j] != '-' && procA[j + 1] != '-')
                {
                    endFound++;
                }
            }
            if (endFound == 1)
            {
                numHoles++;
            }
        }
    }
    if (numHoles > 4)
    {
        numHoles = 2;
    }
    return numHoles;
}

int countProcesses(char *procA)
{
    int numPro = 0;
    struct Node *tempPtr = tail;
    while (tempPtr != NULL)
    {
        for (int i = 0; i < 128; i++)
        {
            if (tempPtr->ID == procA[i] && procA[i] != procA[i + 1])
            {
                numPro++;
            }
        }

        tempPtr = tempPtr->nextPtr;
    }

    return numPro;
}

void searchMemory(char *visualMem, struct Node cNode)
{
    int freeSpace = 0;
    struct Node node;
    struct Node nRemove;
    struct Node nNode;

    //Find Oldest
    node = gethead();
    nRemove = getRemove();

    //Remove oldest
    for (int i = nRemove.pos; i < (nRemove.Data + nRemove.pos); i++)
    {
        visualMem[i] = '-';
    }
    nNode = lookUp(nRemove.ID);
    changeOld(nNode.ID);

    //Check free memory again
    for (int i = 0; i < 128; i++)
    {
        if (visualMem[i] == '-')
        {
            freeSpace++;
            //Find the holes
        }
        else if (visualMem[i] != '-')
        {
            break;
        }
    }
    //Recursivly call itself untill there is enough free memory
    if (freeSpace < node.Data)
    {
        searchMemory(visualMem, node);
    }
}
