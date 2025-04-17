#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> arr(n + 1); // 1-based indexing
    // arr[r] stores the indexes where number r appears in the sequence

    for (int index = 1; index <= 2 * n; index++)
    {
        int val;
        cin >> val; // val is in the range 1 to n
        arr[val].push_back(index);
    }

    long long answer = 0;

    // Check all pairs (a, b) where a < b
    for (int a = 1; a <= n; a++)
    {
        // Skip if a's are already adjacent
        if (abs(arr[a][0] - arr[a][1]) == 1)
            continue;

        int a1 = arr[a][0], a2 = arr[a][1];
        if (a1 > a2)
            swap(a1, a2); // Ensure a1 < a2

        for (int b = a + 1; b <= n; b++)
        {
            // Skip if b's are already adjacent
            if (abs(arr[b][0] - arr[b][1]) == 1)
                continue;

            int b1 = arr[b][0], b2 = arr[b][1];
            if (b1 > b2)
                swap(b1, b2); // Ensure b1 < b2

            // Check if they are interleaved in a way that allows swapping
            // Either one b is between the a's and one is outside, or vice versa

            // Check if one b is between a's and one b is outside
            bool case1 = (a1 < b1 && b1 < a2 && (b2 < a1 || b2 > a2));
            bool case2 = (a1 < b2 && b2 < a2 && (b1 < a1 || b1 > a2));

            // Check if one a is between b's and one a is outside
            bool case3 = (b1 < a1 && a1 < b2 && (a2 < b1 || a2 > b2));
            bool case4 = (b1 < a2 && a2 < b2 && (a1 < b1 || a1 > b2));

            if (case1 || case2 || case3 || case4)
                answer++;
        }
    }

    cout << answer << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}