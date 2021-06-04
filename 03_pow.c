#include <stdio.h>
#include "math.h"
int main()
{
    double a, b, step = 0;
    int c = 0;
    c = scanf("%lf%lf", &a, &b);
    if(c==2)
        step = pow(a, b) ;
    printf("%lf", step);
    return 0;
}
