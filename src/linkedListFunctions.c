
#include <stdio.h>
#include <stdlib.h>

struct Node lookUp(char ID);
struct Node getRemove();
struct Node gethead();
struct Node getTail();
void addToTail(int value, char ID, int pos, int timesRunThroughQueue, int isOld);
void changeOld(char ID);
void addTohead(int value);
void removeFromhead();
void removeFromTail();

struct Node
{
    int Data;
    char ID;
    int timesRunThroughQueue;
    int pos;
    int isOld;
    struct Node *nextPtr;
} * tail, *head, Node;

void addToTail(int value, char ID, int pos, int timesRunThroughQueue, int isOld)
{
    struct Node *tempPtr;
    tempPtr = (struct Node *)malloc(sizeof(struct Node));
    tempPtr->Data = value;
    tempPtr->ID = ID;
    tempPtr->pos = pos;
    tempPtr->timesRunThroughQueue = timesRunThroughQueue;
    tempPtr->isOld = isOld;
    if (head == NULL)
    {
        head = tempPtr;
        head->nextPtr = NULL;
        tail = head;
    }
    else
    {
        head->nextPtr = tempPtr;
        head = tempPtr;
        head->nextPtr = NULL;
    }
}

struct Node lookUp(char ID)
{
    struct Node *tempPtr = tail;
    while (tempPtr != NULL)
    {
        if (tempPtr->ID == ID)
        {
            // found it!
            return *tempPtr;
            break;
        }
        tempPtr = tempPtr->nextPtr;
    }
    return *tempPtr->nextPtr;
}

struct Node getRemove()
{
    int min = 999;
    struct Node *oldNode;
    struct Node *tempPtr = tail;
    while (tempPtr != NULL)
    {
        if (tempPtr->isOld < min && tempPtr->isOld != 0 && tempPtr->timesRunThroughQueue >= 1)
        {
            min = tempPtr->isOld;
            oldNode = tempPtr;
        }
        tempPtr = tempPtr->nextPtr;
    }
    return *oldNode;
}

struct Node gethead()
{
    struct Node *currentPtr = tail;
    return *currentPtr;
}

struct Node getTail()
{
    struct Node *currentPtr = head;
    return *currentPtr;
}

void changeOld(char ID)
{
    int max = 0;
    struct Node *ltempPtr = tail;
    while (ltempPtr != NULL)
    {
        if (ltempPtr->isOld > max && ltempPtr->isOld != 0 && ltempPtr->timesRunThroughQueue >= 1)
        {
            max = ltempPtr->isOld;
        }
        ltempPtr = ltempPtr->nextPtr;
    }
    struct Node *tempPtr = tail;
    while (tempPtr != NULL)
    {
        if (tempPtr->ID == ID)
        {
            // found it!
            tempPtr->isOld = tempPtr->isOld + max + 1;
            break;
        }
        tempPtr = tempPtr->nextPtr;
    }
}

void addTohead(int value)
{
    struct Node *currentPtr = tail;
    currentPtr->nextPtr = tail;
    tail = currentPtr;
}

void removeFromhead()
{
    struct Node *currentPtr = tail;
    currentPtr = currentPtr->nextPtr;
    tail = currentPtr;
}

void removeFromTail()
{
    struct Node *currentPtr = tail;
    struct Node *prePtr;
    prePtr = (struct Node *)malloc(sizeof(struct Node));
    while (currentPtr->nextPtr != NULL)
    {
        prePtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }
    prePtr->nextPtr = NULL;
}