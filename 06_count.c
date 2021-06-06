#include<stdio.h>

int main(void)
{
    int length, i, count=0;
    double x;
    (void)scanf("%d", &length);
    for(i=0; i<length; i++)
    {
        (void)scanf("%lf", &x);
        if(x>0)
            count++;
    }
    printf("%d\n", count);
    return 0;
}