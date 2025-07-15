// https://codeforces.com/problemset/problem/1158/A

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, m;
    cin >> n >> m;

    vector<long long> minimal(n);
    for (long long &val : minimal)
    {
        cin >> val;
    }

    vector<long long> maximal(m);
    for (long long &val : maximal)
    {
        cin >> val;
    }

    sort(minimal.begin(), minimal.end());
    sort(maximal.begin(), maximal.end());

    if (maximal[0] < minimal[n - 1])
    {
        cout << -1 << endl;
        return EXIT_SUCCESS;
    }

    int left = 0;
    int right = n - 1;

    for (int index )
}