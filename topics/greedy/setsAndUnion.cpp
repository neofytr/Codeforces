#include <bits/stdc++.h>
using namespace std;

int popcount(uint64_t x)
{
    // return the number of ones in x
    int count = 0;
    while (x)
    {
        x &= (x - 1);
        count++;
    }

    return count;
}

void solve()
{
    int n;
    cin >> n;

    vector<uint64_t> sets(n, 0);
    int k, temp;

    for (int i = 0; i < n; i++)
    {
        cin >> k;
        while (k--)
        {
            cin >> temp;
            sets[i] |= (1ULL << temp);
        }
    }

    uint64_t totalUnion = 0;
    for (int i = 0; i < n; i++)
    {
        totalUnion |= sets[i];
    }

    // T = union of all sets
    // S is the set we want to find
    // S is the maximal set that is a union of some of the sets S1, ..., Sn but S != T

    // Let S is a set such that it's a union of some of S1, ..., Sn but S != T
    // then, there is some i in T such that i is not in S

    // to find the maximal such S, exhaustively loop through all possible i, calculate
    // the maximal set S that is a union of some of the sets, that doesn't contain i,
    // and then take the maximum of these maximal sets

    // the possible elements are in the range 1 to 50
    int max_count = INT_MIN;
    for (uint64_t i = 1; i <= 50; i++)
    {
        if (totalUnion & (1ULL << i))
        {
            // i is in the total union
            uint64_t un = 0;
            for (int index = 0; index < n; index++)
            {
                if (!((1ULL << i) & sets[index]))
                {
                    un |= sets[index];
                }
            }
            max_count = max(max_count, popcount(un));
        }
    }

    cout << max_count << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}