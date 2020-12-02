#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct bstnode
{
    int num;
    struct bstnode *left;
    struct bstnode *right;
};

void insert(struct bstnode *node, int i)
{
    if(node->num > i)
    {
        if(node->left==NULL)
        {
            node->left = malloc(sizeof(struct bstnode));
            node->left->num = i;
            node->left->left = NULL;
            node->left->right = NULL;
        }
        else
        {
            insert(node->left, i);
        }
    }
    else if(node->num < i)
    {
        if(node->right==NULL)
        {
            node->right = malloc(sizeof(struct bstnode));
            node->right->num = i;
            node->right->left = NULL;
            node->right->right = NULL;
        }
        else
        {
            insert(node->right, i);
        }
    }
}

void delete(struct bstnode *node, int i)
{
    struct bstnode *current = node;
    struct bstnode *parent = NULL;
    while(current->num!=i)   
    {
        if(current->num>i)
        {
            parent = current;
            current = current->left;
        }
        else if(current->num<i)
        {
            parent = current;
            current = current->right;
        }
    }
    //At this point, current is the node containing the value, and parent is the node containing a pointer to current

    //This is the case where the current node is a leaf node with no children
    if(current->left==NULL && current->right==NULL)
    {
        //printf("The node has no children!");
        if(parent!=NULL)
        {
            if(parent->num>i)
            {
                parent->left = NULL;
            }
            else if(parent->num<i)
            {
                parent->right = NULL;
            }
            struct bstnode *temp = current;
            current = current->left;
            free(temp);
        }
        else
        {
            current = current->left;
        }       
    }
    //This is the case where the current node has one child, which then just takes the place of current
    else if((current->left==NULL && current->right !=NULL) || (current->right==NULL && current->left!=NULL))
    {
        if(parent!=NULL)
        {
            if(parent->num>i)
            {
                if(current->left!=NULL)
                {
                    parent->left=current->left;
                    free(current);
                }
                else
                {
                    parent->left=current->right;
                    free(current);
                }
                
            }
            else
            {
                if(current->left!=NULL)
                {
                    parent->right=current->left;
                    free(current);
                }
                else
                {
                    parent->right=current->right;
                    free(current);
                }
            }
            
        }
        else
        {
            if(current->left!=NULL)
            {
                struct bstnode *temp = current->left;
                current->num = current->left->num;
                current->right = current->left->right;
                current->left = current->left->left;
                free(temp);
            }
            else
            {
                struct bstnode *temp = current->right;
                current->num = current->right->num;
                current->left = current->right->left;
                current->right = current->right->right;
                free(temp);
            }
            
        }
        
    }

    //This is the case where the node to be deleted has 2 children. Must find highest value in left subtree and swap it for current
    else
    {
        struct bstnode *biggest = current->left;
        struct bstnode *biggestparent = current;
        while(biggest->right!=NULL)
        {
            biggestparent = biggest;
            biggest = biggest->right;
        }
        current->num = biggest->num;
        if(biggestparent == current)
        {
            current->left = biggest->left;
        }
        else
        {
            biggestparent->right = biggest->left;
        }
        free(biggest);

    }
}

int search(struct bstnode *node, int i)
{
    if(node == NULL)
    {
        return 0;
    }
    else if(node->num == i)
    {
        //printf("We found the number!\n");
        return 1;
    }
    else if(node->num > i)
    {
        return search(node->left, i);
    }
    else 
    {
        return search(node->right, i);
    }
}

void printNode(struct bstnode *node)
{
    if(node!=NULL)
    {
        printf("(");
        printNode(node->left);
        printf("%d", node->num);
        printNode(node->right);
        printf(")");
    }
}

int main(int argc, char* argv[])
{
    char c;
    int i;

    struct bstnode *node = NULL;

    while(scanf(" %c", &c)!=EOF)
    {
        if(c=='i')
        {
            //printf("we are in the insert case\n");
            scanf("%d", &i);
            //printf("we are planning on inserting the number: %d\n", i);
            if(node == NULL)
            {
                node = malloc(sizeof(struct bstnode));
                node->num = i;
                node->left = NULL;
                node->right = NULL;
                printf("inserted\n");
            }
            else if(search(node, i))
            {
                printf("not inserted\n");
            }
            else
            {
                insert(node, i);
                printf("inserted\n");
            }
            //insert(node, i); 
        }
        else if(c=='d')
        {
            scanf("%d", &i);
            if(search(node, i))
            {
                if(node->left==NULL && node->right==NULL)
                {
                    node = NULL;
                }
                else
                {
                    delete(node, i);
                }                    
                printf("deleted\n");
            }
            else
            {
                printf("absent\n");
            }
            
            
        }
        else if(c=='p')
        {
            if(node!=NULL)
            {
                printNode(node);
            }
            
            printf("\n");
        }
        else if(c=='s')
        {
            scanf("%d", &i);
            if(search(node, i))
            {
                printf("present\n");
            }
            else
            {
                printf("absent\n");
            }
            //search(node, i);
        }
    }
}