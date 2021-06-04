#include <stdio.h>

int main()
{
    double a, b, sum = 0;
    int c = 0;
    c = scanf("%lf%lf", &a, &b);
    if(c==2)
        sum = a + b ;
    printf("%lf", sum);
    return 0;
}