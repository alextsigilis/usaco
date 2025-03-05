/*
ID: alextsi2 
TASK: milk 
LANG: C
*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Farmer {
    int price;
    int amount;
} Farmer;

int cmp(const void* x, const void* y) {
    Farmer a = *(Farmer*)x;
    Farmer b = *(Farmer*)y;
    return a.price - b.price;
}

// Note: farmers array must be sorted by price
int min_cost(int N, int M, Farmer* farmer) {
    int cost = 0,
        j = 0; 
    while(N > 0) {
        if(farmer[j].amount == 0) ++j;
        cost += farmer[j].price;
        farmer[j].amount -= 1;
        N -= 1;
    }
    return cost;
}

void read_input(int* M, int* N, Farmer* farmer){
    FILE *fin = fopen("milk.in", "r");
    int p, a;
    fscanf(fin, "%d %d", N, M);
    for(int i=0; i<(*M); ++i) {
        fscanf(fin, "%d %d", &p, &a);
        farmer[i].price = p;
        farmer[i].amount = a;
    }
    fclose(fin);
}

void write_output(int result) {
    FILE *fout = fopen("milk.out", "w");
    fprintf(fout, "%d\n", result);
    fclose(fout);
}


int main() {
    
    int N, M;
    Farmer farmer[5000];
    read_input(&M, &N, farmer);
    qsort(farmer, M, sizeof(Farmer), cmp);
    int result = min_cost(N, M, farmer);
    printf("Min Cost: %d\n", result);
    write_output(result);
    return 0;
}
