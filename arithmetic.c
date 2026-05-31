#include <stddef.h>
#include "arithmetic.h"

int calc_add(int a, int b) { return a + b; }
int calc_sub(int a, int b) { return a - b; }
int calc_mul(int a, int b) { return a * b; }

int calc_div(int a, int b, double *result)
{
    if (result == NULL) return 0;
    if (b == 0) return 0;
    *result = (double)a / b;
    return 1;
}
