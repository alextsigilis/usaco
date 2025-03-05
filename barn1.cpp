/*
ID: alextsi2
TASK: barn1
LANG: C++14
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

/*
 * Is the i-th stall occupied by a cow?
 */
bool occupied(const vector<bool>::iterator i)
{
    return *i;
}

vector<int>
calculate_distances(const vector<bool>::iterator first,
                    const vector<bool>::iterator last)
{
    // Precondition: first, last are occupied
    vector<int> distances;
    for(auto start = first; start < last; ++start)
    {
        auto end = start;
        while (!occupied(end))
            ++end;
        if (start < end)
            distances.push_back(end - start);
        start = end;
    }
    return distances;
}


int min_stalls(int max_boards,
               int num_cows,
               vector<int>& distances)
{
    sort(distances.begin(), distances.end());

    int min = num_cows;                    // We need at lead `C` stalls to block all cows.
    int num_boards = distances.size() + 1; // We start by covering each set of contigient occupied stalls
                                           // with 1 board
    int j = 0; 
    while (num_boards > max_boards)
    {
        min += distances[j++];
        num_boards--; 
    }
    return min;
}

int main()
{
    ifstream fin("barn1.in");
	int M, // Maximum number of boards that can be purchased
        S, // Number of stalls
        C; // Number of cows
	fin >> M >> S >> C;
    vector<bool> occ(S, false);
    int first = S, last = 0;
    for (int i=0; i<C; ++i)
    {
        int tmp;
        fin >> tmp;
        occ[tmp-1] = true;
        if (tmp-1 < first)
            first = tmp-1;
        if (tmp-1 > last)
            last = tmp-1;
    }
    fin.close();

    auto distances = calculate_distances(occ.begin() + first,
                                         occ.begin() + last);
    
    ofstream fout("barn1.out");
    fout << min_stalls(M, C, distances) << endl;
    fout.close();

    return 0;

}
