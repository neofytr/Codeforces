#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> mukul(n);
    vector<int> suman(m);

    for (int &val : mukul)
    {
        cin >> val;
    }

    for (int &val : suman)
    {
        cin >> val;
    }

    int l, r;

    while (q--)
    {
        cin >> l >> r;
        l--, r--; // convert to 0-based indexing
    }
}