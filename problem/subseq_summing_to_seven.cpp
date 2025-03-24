// https://usaco.org/index.php?page=viewproblem2&cpid=595

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> cow(n + 1, 0); // 1 based indexing

    for (int index = 1; index <= n; index++)
    {
        cin >> cow[index];
    }

    vector<long long> prefix(n + 2, 0); // 1 based indexing

    for (int index = 2; index <= n + 1; index++)
    {
        prefix[index] = cow[index - 1] + prefix[index - 1];
    }

    for (int index = 2; index <= n + 1; index++)
    {
        prefix[index] = prefix[index] % 7;
    }

    // if the same remainder comes again in the prefix array, the elements in that
    // subarray have sum that is a multiple of 7

    unordered_map<int, int> remainder_index;
    int maxlen = 0;
    for (int index = 1; index <= n; index++)
    {
        if (remainder_index.count(prefix[index + 1]))
        {
            maxlen = max(maxlen, index + 1 - remainder_index[prefix[index + 1]]);
        }
        else
        {
            remainder_index[prefix[index + 1]] = index + 1;
        }
    }

    cout << maxlen << endl;
}