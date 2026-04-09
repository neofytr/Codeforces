#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> prefix(n + 1);
    prefix[0] = 0;

    unordered_map<int, long long> map;
    map[0] = 0;

    long long maxlen = 0;
    long long val;

    for (int index = 1; index <= n; index++)
    {
        cin >> val;
        prefix[index] = (prefix[index - 1] + val) % 7;
        if (map.count(prefix[index]))
        {
            // current remainder exists already
            maxlen = max(maxlen, index - prefix[index]);
        }
        else
        {
            map[prefix[index]] = index;
        }
    }

    cout << maxlen << endl;
}