#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct listNode
{
    int num;
    struct listNode *next; 
};
void printListNode(struct listNode *front)
{
    struct listNode* current = front;
    while(current!=NULL)
    {
        printf(" %d", current->num);
        current = current->next; 
    }
    printf("\n");
}
struct listNode* add(int *length, struct listNode *front, int i)
{
    //printf("\nwe are here");
    if(front==NULL)
    {
        //printf("\nFirst case null\n");
        //length++;
        front = malloc(sizeof(struct listNode));
        front->num = i;
        front->next = NULL;
        (*length)++;
        printf("%d :", *length);
        printListNode(front);
        return front;
    }
    else if(front->num>i)
    {
        //printf("\nSecond case val smallest\n");
        struct listNode *node = malloc(sizeof(struct listNode));
        node->num = i;
        node->next = front;
        front = node;
        (*length)++;
        printf("%d :", *length);
        printListNode(front);
        return front;
    }
    else
    {
        //printf("\nFourth case loop");
        //printf("\nThe first value in front is: %d\n", front->num);
        struct listNode* current = front;
        struct listNode* current2 = front;
        while(current2->num!=i)
        {
            //printf("stuck");
            current2 = current2->next;
            if(current2 == NULL)
                break;
        }
        if(current2!=NULL)
        {
            printf("%d :", *length);
            printListNode(front);
            return front;
        }
        while(current->next!=NULL && current->next->num<i)
        {
            current = current->next;
        }
        struct listNode *node = malloc(sizeof(struct listNode));
        node->num = i;
        node->next = current->next;
        current->next = node;
        (*length)++;
        printf("%d :", *length);
        printListNode(front);
        return front;
    }    
}
struct listNode* delete(int *length, struct listNode *front, int i)
{
    if(front==NULL)
    {
        printf("0 :\n");
        return NULL;
    }
    //printf("We are in the delete method\n");
    if(front->num == i)
    {
        //printf("we are in the front case\n");
        (*length)--;
        struct listNode* temp = front;
        front = front->next;
        free(temp);
        
        if(front!=NULL)
        {
            printf("%d :", *length);
            printListNode(front);
            return front;
        }
        else
        {
            printf("%d :\n", *length);
            return NULL;
        }
           
    }
    else
    {
        struct listNode* current = front->next;
        struct listNode* prev = front;
        while(current!=NULL && current->num!=i)
        {
            prev = current;
            current = current->next;
        }
        if(current!=NULL)
        {
            prev->next = current->next;
            free(current);
            (*length)--;
        }
        printf("%d :", *length);
        printListNode(front);
        return front;
    }
    
}


int main(int argc, char* argv[])
{
    char c;
    int i;

    struct listNode *front =NULL;
    int length = 0;
    
    while(scanf("%c %d", &c, &i)!=EOF)
    {
        if(c=='i')
        {        
            //printf("we are adding");
            front = add(&length, front, i);
        }
        else if(c=='d')
        {
            front = delete(&length, front, i);
        }
    }
    return EXIT_SUCCESS;

}

