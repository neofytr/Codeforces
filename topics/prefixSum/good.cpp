#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    string str;
    cin >> str;

    long long sum = 0;
    long long value;
    long long key;
    long long count = 0;
    unordered_map<long long, long long> map;
    map[0] = 1;

    for (int index = 1; index <= n; index++)
    {
        value = str[index - 1] - '0';
        sum += value;
        key = sum - index;
        if (map.count(key))
        {
            count += map[key];
        }

        map[key]++;
    }

    cout << count << endl;
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