// https://cses.fi/problemset/task/1650

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;

    vector<long long> arr(n + 1, 0);
    vector<long long> prefix(n + 2, 0);

    for (int index = 1; index <= n; index++)
    {
        cin >> arr[index];
    }

    for (int index = 2; index <= n + 1; index++)
    {
        prefix[index] = prefix[index - 1] ^ arr[index - 1];
    }

    int a, b;
    while (q--)
    {
        cin >> a >> b;

        // 1 based indexing; no change to a and b
        cout << (prefix[b + 1] ^ prefix[a]) << "\n";
    }

    return EXIT_SUCCESS;
}