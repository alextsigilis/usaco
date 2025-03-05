/*
ID: alextsi2
TASK: crypt1
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DIGITS 5

bool isvalid (int num, bool* digits)
{
    int d;
    while (num > 0)
    {
        d = num % 10;
        if( ! digits[d] )
            return false;
        num = num / 10;
    }
    return true;
}

int ndigits(int num)
{
    int n = 0;
    while (num > 0)
    {
        num = num / 10;
        n++;
    }
    return n;
}

int is_valid_crypt (int n1, int n2, bool digits[])
{
    if ( ! isvalid(n1, digits) )
        return 0;
    if ( ! isvalid(n2, digits) )
        return 0;

    int d1 = n2 % 10;
    int d2 = (n2 / 10) % 10;

    int prod1 = n1 * d1;
    if ( !isvalid(prod1, digits) || ndigits(prod1)!=3 )
        return 0;

    int prod2 = n1 * d2;
    if ( !isvalid(prod2, digits) || ndigits(prod2)!=3 )
        return 0;

    int sum = prod1 + (10 * prod2);
    if ( !isvalid(sum, digits) || ndigits(sum)!=4 )
        return 0;

    return 1;

}
int main()
{
    FILE *fin, *fout;
    int N;
    bool digits[10] = {false};
    
    // Read input
    //
    fin = fopen("crypt1.in", "r");
    fscanf(fin, "%d", &N);
    for (int i=0; i<N; ++i)
    {
        int tmp;
        fscanf(fin, "%d", &tmp);
        digits[tmp] = true;
    }
        

    // Compute
    //
    int total = 0;
    for (int n1=100; n1<1000; n1++) /* For all 3-digits numbers */
    {
        for (int n2=10; n2<100; n2++) /* For all 2-digit numbers */
        {
            if (is_valid_crypt(n1, n2, digits))
            {
                total++;
            }
        }
    }
    
    // Write output
    //
    fout = fopen("crypt1.out", "w");
    fprintf(fout, "%d\n", total);
    fclose(fout);
    return 0;
}
