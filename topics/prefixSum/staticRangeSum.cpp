#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> prefix(n + 1, 0);
    int val;
    for (int index = 1; index <= n; index++)
    {
        cin >> val;
        prefix[index] = prefix[index - 1] + val;
    }

    int a, b;
    while (q--)
    {
        cin >> a >> b;
        a--, b--; // convert to zero-based indexing
        cout << prefix[b + 1] - prefix[a] << endl;
    }
}