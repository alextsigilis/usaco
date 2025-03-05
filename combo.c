/*
ID: alextsi2
TASK: combo 
LANG: C
*/
#include <stdio.h>

#define COMB_SIZE 3
#define MAX_DIST  2
#define ALL_COMBS 2*5*5*5

void center (int *p, int N)
{
    int n = *p;
    if (n < N / 2)
        *p = n-1;
    else
        *p = -N + (n-1);
    return;
}

int overlap (int a, int b, int N)
{
    center(&a, N);
    center(&b, N);
    int m  = a<b ? a : b,
        M  = a>b ? a : b,
        ov = (m + MAX_DIST) - (M - MAX_DIST) + 1;
    if (ov > 0)
        return ov;
    else
        return 0;
}

int total_overlab(int a[], int b[], int N)
{
    int product = 1;
    for (int i=0; i<COMB_SIZE; i++)
        product *= overlap(a[i], b[i], N);
    return product;
}

int main ()
{
    FILE *in, *out;
    int N, i, a[COMB_SIZE], b[COMB_SIZE], result;

    // Read Input
    in = fopen("combo.in", "r");
    fscanf(in, "%d", &N);
    for (i=0; i<COMB_SIZE; i++)
        fscanf(in, "%d", a+i);
    for (i=0; i<COMB_SIZE; i++)
        fscanf(in, "%d", b+i);
    fclose(in);

    // Compute
    if ( N <= 2 * MAX_DIST )
        result = N * N * N;
    else
        result = ALL_COMBS - total_overlab(a, b, N);
        
    // Write output
    out = fopen("combo.out", "w");
    fprintf(out, "%d\n", result);
    fclose(out);

    return 0;
}
