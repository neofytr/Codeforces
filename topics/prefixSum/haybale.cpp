#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<long long> arr(n + 1, 0); 

    for (int i = 0; i < k; ++i)
    {
        int a, b;
        cin >> a >> b;
        arr[a] += 1;
        if (b + 1 <= n)
            arr[b + 1] -= 1;
    }

    // prefix sum to apply all range updates
    for (int i = 1; i <= n; ++i)
        arr[i] += arr[i - 1];

    sort(arr.begin() + 1, arr.begin() + n + 1); // ignore 0th index

    cout << arr[(n + 1) / 2] << '\n'; // median (1-based indexing)
}
