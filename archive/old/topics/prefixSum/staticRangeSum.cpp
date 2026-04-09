// https://cses.fi/problemset/task/1646

#include <bits/stdc++.h>
using namespace std;

int main()
{
    size_t n, q;
    cin >> n >> q;

    vector<size_t> prefix(n + 1, 0);
    size_t val;
    for (size_t index = 1; index <= n; index++)
    {
        cin >> val;
        prefix[index] = prefix[index - 1] + val;
    }

    size_t a, b;
    while (q--)
    {
        cin >> a >> b;
        a--, b--; // convert to zero-based indexing
        cout << prefix[b + 1] - prefix[a] << endl;
    }
}