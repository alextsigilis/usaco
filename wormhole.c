/*
ID: alextsin2
LANG: C
TASK: wormhole
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_N 12
#define UNPAIRED -1

typedef int wh;

wh partner[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void pair (wh i, wh j)
{
	partner[i] = j;
	partner[j] = i;
}

void unpair (wh i, wh j)
{
	partner[i] = UNPAIRED;
	partner[j] = UNPAIRED;
}

wh* order (wh x[], wh y[], size_t N)
{
	wh *next = (wh*) malloc((N+1) * sizeof(wh));
	assert(next != NULL);
	for (int i=0; i<N; i++)
	{
		wh k = UNPAIRED;
		int xmin = INT_MAX;
		for (wh j=0; j<N; j++)
		{
			if ((x[i] < x[j]) && (x[j] < xmin) && (y[j] == y[i]))
			{
				xmin = x[j];
				k = j;
			}
		}
		next[i] = k;
	}
	return next;
}

bool cycle_from (wh start, wh next[], size_t N)
{
	wh w = start;
	for (int i=0; i<N; i++)
	{
		w = next[partner[w]];
		if (w == -1)
		{
			return false;
		}
	}
	return true;
}

int cycle (wh next[], size_t N)
{
	for (wh start=0; start<N; start++)
		if (cycle_from(start, next, N))
		{
			printf("\n\n");
			return 1;
		}
	return 0;
}

// TODO: Make it iterative.
int count_cycles(wh next[], size_t N)
{
	wh i = 0;
	while ((partner[i] > -1) && (i < N))
	{ i++; }

	if (i == N)
	{
		return cycle(next, N);
	}
	
	int count = 0;
	for (wh j=i+1; j<N; j++)
	{
		if (partner[j] == -1)
		{
			pair(i, j);
			count += count_cycles(next, N);
			unpair(i, j);
		}
	}
	return count;
}

int main ()
{
	/*
	 * Variables
	*/
	size_t N;
	int x[MAX_N], y[MAX_N];

	/*
	 * Read file
	 */
	FILE *in = fopen("wormhole.in", "r");
	fscanf(in, "%d", &N);
	for (int i=0; i<N; i++)
	{
		fscanf(in, "%d %d", &x[i], &y[i]);
		printf("%d %d\n", x[i], y[i]);
	}
	fclose(in);

	/*
	 * Calculate
	 */
	wh *next = order(x, y, N);
	int res = count_cycles(next, N);

	/*
	 * Write file
	 */
	printf("Answer = %d\n\n", res);
	FILE *out = fopen("wormhole.out", "w");
	fprintf(out, "%d\n", res);
	fclose(out);

	return 0;
}

