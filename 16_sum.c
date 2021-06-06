#include<stdio.h>
#include<math.h>
int main(void)
{
    int length, i;
    double x, temp, sum=0;

    (void)scanf("%d", &length);

    for(i=1; i<length+1; i++)
    {
        (void)scanf("%lf", &x);

        temp=(double)i+1;
        sum+=pow(-1, temp)*x*x*x;
    }

    printf("%lf\n", sum);
    return 0;
}