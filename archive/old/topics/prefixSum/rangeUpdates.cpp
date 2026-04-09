#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, q;
    cin >> n >> q;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    vector<long long> updates(n + 1, 0);
    int l, r, x;
    while (q--)
    {
        cin >> l >> r >> x;
        // convert to zero-based indexing

        updates[l] = x;
        updates[r + 1] = -x;
    }

    // accumulate/propagate all the updates
    for (int index = 1; index <= n; index++)
    {
        updates[index] += updates[index - 1];
    }

    // perform range update
    for (int index = 0; index < n; index++)
    {
        arr[index] += updates[index];
    }

    return EXIT_SUCCESS;
}