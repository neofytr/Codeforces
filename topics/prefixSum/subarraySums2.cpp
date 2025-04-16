#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, x;
    cin >> n >> x;

    vector<long long> prefix(n + 1);
    prefix[0] = 0;

    unordered_map<long long, long long> map;
    map[0] = 1;
    long long count = 0;
    long long val;

    for (int index = 1; index <= n; index++)
    {
        cin >> val;
        prefix[index] = prefix[index - 1] + val;
        if (map.count(prefix[index] - x))
        {
            count += map[prefix[index] - x];
        }

        map[prefix[index]]++;
    }

    cout << count << endl;
}