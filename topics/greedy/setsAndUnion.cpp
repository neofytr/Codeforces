#include <bits/stdc++.h>
using namespace std;

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

    vector<uint64_t> maximal;
    for (int i = 0; i < n; i++)
    {
        bool isSubset = false;
        for (int j = 0; j < n; j++)
        {
            if (i != j && (sets[i] | sets[j]) == sets[j])
            {
                isSubset = true;
                break;
            }
        }
        if (!isSubset)
        {
            maximal.push_back(sets[i]);
        }
    }

    int maxSize = 0;

    for (int exclude = 0; exclude < maximal.size(); exclude++)
    {
        uint64_t currentUnion = 0;
        for (int i = 0; i < maximal.size(); i++)
        {
            if (i != exclude)
            {
                currentUnion |= maximal[i];
            }
        }

        if (currentUnion != totalUnion)
        {
            maxSize = max(maxSize, __builtin_popcountll(currentUnion));
        }
    }

    maxSize = max(maxSize, 0);

    cout << maxSize << endl;
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