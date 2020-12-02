#include <stdio.h>



struct pt {int x; int y;};

int main()
{
    struct pt p = {1,2}, q = {3,4};

    q=p;
    p.x = 10;

    printf("p = %d, %d\n", p.x, p.y);
    printf("q = %d, %d\n", q.x, q.y);
    return 0;

}